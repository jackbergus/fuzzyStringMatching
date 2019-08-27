//
// Created by giacomo on 26/08/19.
//

#include <unordered_map>
#include "FuzzyMatchSerializerSEC.h"
#include "../../third_party/varsorter/external_merge_sort/ExternalULongKeyComparator.h"
#include "../../third_party/varsorter/src/KeyValueStore.h"
#include "FuzzyMatchSerializer.h"
#include "../../fromJava/LinkedHashMultimap.h"



FuzzyMatchSerializerSEC::FuzzyMatchSerializerSEC(std::string path) :
    mainDir{path},

    objectMultipleStirngs_index{path+"/lsvm_index.bin"},
    objectMultipleStirngs_values{path+"/lsvm_values.bin"},
    objectMultipleStirngs{objectMultipleStirngs_index, objectMultipleStirngs_values},

    gramToObject_index{path+"/gramToObject_index.bin"},
    gramToObject_values{path+"/gramToObject_valuesTmp.bin"},
    gramToObject{gramToObject_index, gramToObject_values},

    objectGramSize_index{path+"/objectGramSize_index.bin"},
    objectGramSize_values{path+"/objectGramSize_valuesTmp.bin"},
    objectGramSize{objectGramSize_index, objectGramSize_values},

    termObject_index{path+"/termObject_index.bin"},
    termObject_values{path+"/termObject_valuesTmp.bin"},
    termObject{termObject_index, termObject_values},

    twogramAndStringMultiplicity_index{path+"/twogramAndStringMultiplicity_index.bin"},
    twogramAndStringMultiplicity_value{path+"/twogramAndStringMultiplicity_valuesTmp.bin"},
    twogramAndStringMultiplicity{twogramAndStringMultiplicity_index, twogramAndStringMultiplicity_value}

    {

}

void FuzzyMatchSerializerSEC::addGramsToMap(std::string &string, LONG_NUMERIC id,
                                            std::vector<std::string> &associatedOtherStrings) {


    // Associating the main term to the id
    serializeToSLHM(string, id, termObject);

    // Serializing all the possible associatedOtherStrings strings, string included.
    serializeToObjectMultimap(string, id);
    for (std::string& associated: associatedOtherStrings) {
        serializeToObjectMultimap(associated, id);
    }

    std::unordered_map<std::string, LONG_NUMERIC> cp;
    std::vector<LONG_NUMERIC> vec;
    compareStringHashmap2(string, cp, vec);
    LONG_NUMERIC sum = 0;
    for (LONG_NUMERIC& j : vec) {
        sum += j;
    }
    serializeToSLHM(string, sum, objectGramSize);

    for (std::unordered_map<std::string, LONG_NUMERIC>::iterator begin = cp.begin(), end = cp.end(); begin!=end; begin++) {
        //
        LONG_NUMERIC strlen = string.length();
        LONG_NUMERIC size = sizeof(struct slhm) + sizeof(wchar_t) * strlen;
        void *lsvmMem = twogramAndStringMultiplicity_malloc.domalloc(size);
        ((struct sttgshm *) lsvmMem)->hash = stringhashing(string);
        ((struct sttgshm *) lsvmMem)->strlen = strlen;
        ((struct sttgshm *) lsvmMem)->size = begin->second;
        std::wstring x = this->converter.from_bytes(begin->first.c_str());
        size_t xs = x.length();
        ((struct sttgshm *) lsvmMem)->twograms[0] = (xs == 0) ? '\0' : x[0];
        ((struct sttgshm *) lsvmMem)->twograms[1] = (xs == 1) ? '\0' : x[1];
        strncpy((char *) (((struct sttgshm *) lsvmMem)->string), (char *) string.c_str(), sizeof(wchar_t) * strlen);
        twogramAndStringMultiplicity.insert(twogramAndStringMultiplicity_malloc.malloced_iovec);

        //
        serializeToSLHM(begin->first, id, gramToObject);
    }


}

void FuzzyMatchSerializerSEC::serializeToSLHM(const std::string &string, LONG_NUMERIC id,
                                              KeyValueStore<slhmComparator> &serializer) {
    LONG_NUMERIC strlen = string.length();
    LONG_NUMERIC size = sizeof(struct slhm) + sizeof(wchar_t) * strlen;
    void *lsvmMem = slhm_malloc.domalloc(size);
    ((struct slhm *) lsvmMem)->hash = stringhashing(string);
    ((struct slhm *) lsvmMem)->strlen = strlen;
    ((struct slhm *) lsvmMem)->number = id;
    strncpy((char *) (((struct slhm *) lsvmMem)->string), (char *) string.c_str(), sizeof(wchar_t) * strlen);
}

void FuzzyMatchSerializerSEC::serializeToObjectMultimap(const std::string &string, LONG_NUMERIC id) {
    LONG_NUMERIC size = sizeof(LONG_NUMERIC) + string.length() + sizeof(char);
    oms_malloc.domalloc(size);
    void* lsvmMem = oms_malloc.domalloc(size);
    *((LONG_NUMERIC *) lsvmMem) = id;
    *(((char *) lsvmMem) + (size - sizeof(char))) = '\0'; // zero terminated string
    memcpy(((char *) lsvmMem) + sizeof(LONG_NUMERIC), (void *) string.c_str(), string.length());
    objectMultipleStirngs.insert(oms_malloc.malloced_iovec);
}

void FuzzyMatchSerializerSEC::serialize() {

    // Each block could be run in parallel
    void_virtual_sorter* ptr = new void_virtual_sorter();

    {
        objectMultipleStirngs.c.close();
        external_merge_sort<ExternalULongKeyComparator2> lsvm_ems;
        lsvm_ems.run(objectMultipleStirngs_values, objectMultipleStirngs_index, 3);
        // sorting finished


        std::vector<std::string> lhm;

        std::string pix{mainDir+"/objectMultipleStirngs_index.bin"};
        std::string val{mainDir+"/objectMultipleStirngs_values.bin"};
        FILE *primaryIndex = fopen(pix.c_str(), "w");
        FILE *values = fopen(val.c_str(), "w");

        char init = ' ';

        // Initial header: position zero is set to nothing.
        // For this data structure the zero is just a
        fwrite(&init, sizeof(char), 1, values);
        LONG_NUMERIC offset = 1;
        bool first = true;
        LONG_NUMERIC prevNumber =0;

        for (virtual_sorter::iterator it = termObject.begin(); it != termObject.end(); it++) {
            // It already contains the key/value, or the single value (as you serialized the data)
            LONG_NUMERIC currentKey = *((LONG_NUMERIC*)it->iov_len);
            std::string currentString{((char*)it->iov_base)+sizeof(LONG_NUMERIC), it->iov_len- sizeof(LONG_NUMERIC) - sizeof(char)};

            if (first)
                prevNumber = currentKey;

            if (first || (prevNumber != currentKey)) {
                // Writing the key and the offset for the current element
                fwrite(&prevNumber, sizeof(LONG_NUMERIC), 1, primaryIndex);
                fwrite(&offset, sizeof(LONG_NUMERIC), 1, primaryIndex);

                if (!first) {
                    offset += serializeOMS(lhm, values);
                    lhm.clear();
                }

                first = false;
                prevNumber = currentKey;
            }

            lhm.emplace_back(currentString);
        }

        fwrite(&prevNumber, sizeof(LONG_NUMERIC), 1, primaryIndex);
        fwrite(&offset, sizeof(LONG_NUMERIC), 1, primaryIndex);
        serializeOMS(lhm, values);

        fclose(primaryIndex);
        fclose(values);
        unlink(objectGramSize_index.c_str());
        unlink(objectGramSize_values.c_str());
    }

    {
        slhmSerializeInOldFormat(ptr, mainDir+"/termObject_hashing.bin", mainDir+"/termObject_values.bin", termObject, termObject_index, termObject_values);
    }

    {
        slhmSerializeInOldFormat(ptr, mainDir+"/objectGramSize_hashing.bin", mainDir+"/objectGramSize_values.bin", objectGramSize, objectGramSize_index, objectGramSize_values);
    }

    {
        slhmSerializeInOldFormat(ptr, mainDir+"/gramToObject_hashing.bin", mainDir+"/gramToObject_values.bin", gramToObject, gramToObject_index, gramToObject_values);
    }

    {
        twogramAndStringMultiplicity.c.close();
        external_merge_sort<sttgshmComparator> gasm_ems;
        gasm_ems.run(twogramAndStringMultiplicity_value, twogramAndStringMultiplicity_index, 3);
        // TODO: implement
    }

    // join all the threads
    delete ptr;

}

void FuzzyMatchSerializerSEC::slhmSerializeInOldFormat(void_virtual_sorter *ptr, const std::string hashingFile,
                                                       const std::string valuesFile, KeyValueStore<slhmComparator> &c,
                                                       std::string &oldIndex, std::string &oldValues) {
    c.c.close();
    external_merge_sort<slhmComparator> to_ems;
    to_ems.run(oldValues, oldIndex, 3);

    // Now, re-serializing in the old format

    FILE *hashing = fopen(hashingFile.c_str(), "w");
    FILE *values = fopen(valuesFile.c_str(), "w");
    c.sorter = ptr;
    bool first = true;
    LONG_NUMERIC offset = 0, prevBucket = 0;
    LinkedHashMultimap<std::string, LONG_NUMERIC> lhm;
    for (virtual_sorter::iterator it = termObject.begin(); it != termObject.end(); it++) {
        // It already contains the key/value, or the single value (as you serialized the data)
        struct slhm *curr = (struct slhm *) it->iov_base;
        LONG_NUMERIC bucket = curr->hash;
        if (first)
            prevBucket = bucket;

        if (first || (prevBucket != bucket)) {
            // A, Write Hashing for this bucket
            fwrite(&prevBucket, sizeof(LONG_NUMERIC), 1, hashing);
            fwrite(&offset, sizeof(LONG_NUMERIC), 1, hashing);

            if (!first) {
                offset += serializeTermObject(lhm, values);
                lhm.clear();
            }

            prevBucket = bucket;
            first = false;
        }
        std::string str{curr->string, curr->strlen};
        lhm.put(str, curr->number);

    }

    fwrite(&prevBucket, sizeof(LONG_NUMERIC), 1, hashing);
    fwrite(&offset, sizeof(LONG_NUMERIC), 1, hashing);
    serializeTermObject(lhm, values);

    fclose(hashing);
    fclose(values);
    unlink(oldIndex.c_str());
    unlink(oldValues.c_str());
}

LONG_NUMERIC FuzzyMatchSerializerSEC::serializeTermObject(LinkedHashMultimap<std::string, LONG_NUMERIC> &map, FILE *values) {
    LONG_NUMERIC nElement = map.data.size();

    // Each element in the block is composed as so:
    // 1) number of strings associated to longs.
    //    the values are stored after the number of the elements...
    LONG_NUMERIC offsetsInBucketForKey = sizeof(LONG_NUMERIC);
    fwrite(&nElement, sizeof(LONG_NUMERIC), 1, values);

    // 2) offset of each string associated to long (see 3)
    ///   .., after the nElement offsets
    offsetsInBucketForKey += (sizeof(LONG_NUMERIC)*(nElement));

    // Then I serialize the values. Before doing that, I must evaluate which are the actual offsets that I have to use
    for (std::string& first : map.data) {
        // For each pair, I write the current offset for the keyMultivalue association
        fwrite(&offsetsInBucketForKey, sizeof(LONG_NUMERIC), 1, values);
        offsetsInBucketForKey += (sizeof(LONG_NUMERIC)*(map.map[first].size()+2)+first.size()+1);
    }

    // 3) for each string, we have the size of the block associated to it
    //    such size is offsetToString + vecSize + [vector] + stirng.size+1
    for (std::string& first : map.data) {
        LONG_NUMERIC stirngSize = first.size()+1;

        // 1) string length
        fwrite(&stirngSize, sizeof(LONG_NUMERIC), 1, values);
        // 2) string
        fwrite(first.c_str(), stirngSize, 1, values);

        // 3) vector size after string_length+sizeof(LONG_NUMERIC)
        auto ptr = map.map.find(first);
        LONG_NUMERIC size = ptr->second.size();
        fwrite(&size, sizeof(LONG_NUMERIC), 1, values);

        // 4) vector
        // Writing the longs
        for (int i = 0; i<ptr->second.size(); i++)
            fwrite(&ptr->second[i], sizeof(LONG_NUMERIC), 1, values);

    }

    return offsetsInBucketForKey;
}

LONG_NUMERIC FuzzyMatchSerializerSEC::serializeOMS(std::vector<std::string> &multimap, FILE *values) {
    // -- serializing the size of the properties vector
    LONG_NUMERIC n = multimap.size();
    LONG_NUMERIC buffSize = (n+1)*(sizeof(LONG_NUMERIC));

    fwrite(&n, sizeof(buffSize), 1, values);
    for (LONG_NUMERIC i = 0; i<n; i++) {
        std::string& x = multimap[i];
        fwrite(&buffSize, sizeof(buffSize), 1, values);
        buffSize += (x.size()+1);
    }

    for (LONG_NUMERIC i = 0; i<n; i++) {
        std::string& x = multimap[i];
        fwrite(x.c_str(), x.size()+1, 1, values);
    }
    return buffSize;
}

bool ExternalULongKeyComparator2::greaterThan(void *leftM, size_t leftS, void *rightM, size_t rightS) {
    return ((uint_fast64_t*)(leftM)) > ((uint_fast64_t*)(rightM));
}
