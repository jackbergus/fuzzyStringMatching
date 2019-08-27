//
// Created by giacomo on 26/08/19.
//

#include <unordered_map>
#include "../../third_party/varsorter/external_merge_sort/ExternalULongKeyComparator.h"
#include "../../third_party/varsorter/src/KeyValueStore.h"

#ifdef  _GLIBCXX_PARALLEL
#undef  _GLIBCXX_PARALLEL
#endif

#include "../../fromJava/LinkedHashMultimap.h"
#include "FuzzyMatchSerializer.h"
#include "FuzzyMatchSerializerSEC.h"



FuzzyMatchSerializerSEC::FuzzyMatchSerializerSEC(std::string path) :
    mainDir{path},

    objectMultipleStirngs_index{path+"/lsvm_index.bin"},
    objectMultipleStirngs_values{path+"/lsvm_values.bin"},
    objectMultipleStirngs{path+"/lsvm_index.bin", path+"/lsvm_values.bin"},

    gramToObject_index{path+"/gramToObject_index.bin"},
    gramToObject_values{path+"/gramToObject_valuesTmp.bin"},
    gramToObject{path+"/gramToObject_index.bin", path+"/gramToObject_valuesTmp.bin"},

    objectGramSize_index{path+"/objectGramSize_index.bin"},
    objectGramSize_values{path+"/objectGramSize_valuesTmp.bin"},
    objectGramSize{path+"/objectGramSize_index.bin", path+"/objectGramSize_valuesTmp.bin"},

    termObject_index{path+"/termObject_index.bin"},
    termObject_values{path+"/termObject_valuesTmp.bin"},
    termObject{path+"/termObject_index.bin", path+"/termObject_valuesTmp.bin"},

    twogramAndStringMultiplicity_index{path+"/twogramAndStringMultiplicity_index.bin"},
    twogramAndStringMultiplicity_value{path+"/twogramAndStringMultiplicity_valuesTmp.bin"},
    twogramAndStringMultiplicity{path+"/twogramAndStringMultiplicity_index.bin", path+"/twogramAndStringMultiplicity_valuesTmp.bin"}

    {

}

void FuzzyMatchSerializerSEC::addGramsToMap(std::string &string, LONG_NUMERIC id,
                                            std::vector<std::string> &associatedOtherStrings) {
    LONG_NUMERIC i = 0;

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
        LONG_NUMERIC size = sizeof(struct slhm) + sizeof(char) * (strlen + 1);
        void *lsvmMem = twogramAndStringMultiplicity_malloc.domalloc(size);
        ((struct sttgshm *) lsvmMem)->hash = stringhashing(string);
        ((struct sttgshm *) lsvmMem)->strlen = strlen;
        ((struct sttgshm *) lsvmMem)->number = begin->second;
        std::wstring x = this->converter.from_bytes(begin->first.c_str());
        size_t xs = x.length();
        ((struct sttgshm *) lsvmMem)->twograms[0] = (xs == 0) ? '\0' : x[0];
        ((struct sttgshm *) lsvmMem)->twograms[1] = (xs == 1) ? '\0' : x[1];
        strncpy((char *) (((struct sttgshm *) lsvmMem)->string), (char *) string.c_str(), sizeof(char) * strlen);
        twogramAndStringMultiplicity.insert(twogramAndStringMultiplicity_malloc.malloced_iovec);

        //
        serializeToSLHM(begin->first, id, gramToObject);
    }


}

void FuzzyMatchSerializerSEC::serializeToSLHM(const std::string &string, LONG_NUMERIC id,
                                              KeyValueStore<slhmComparator> &serializer) {
    LONG_NUMERIC strlen = string.length();
    LONG_NUMERIC size = sizeof(struct slhm) + sizeof(char) * (strlen + 1);
    void *lsvmMem = slhm_malloc.domalloc(size);
    ((struct slhm *) lsvmMem)->hash = stringhashing(string);
    ((struct slhm *) lsvmMem)->strlen = strlen;
    ((struct slhm *) lsvmMem)->number = id;
    strncpy((char *) (((struct slhm *) lsvmMem)->string), (char *) string.c_str(), sizeof(char) * strlen);
}

void FuzzyMatchSerializerSEC::serializeToObjectMultimap(const std::string &string, LONG_NUMERIC id) {
    LONG_NUMERIC size = sizeof(LONG_NUMERIC) + (string.length() + 1)*(sizeof(char)) + sizeof(char);
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

        std::string pix{mainDir+"/objectMultipleStirngs.csv_vector.bin"};
        std::string val{mainDir+"/objectMultipleStirngs.csv_values.bin"};
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
                    offset += serializeOMSVector(lhm, values);
                    lhm.clear();
                }

                first = false;
                prevNumber = currentKey;
            }

            lhm.emplace_back(currentString);
        }

        fwrite(&prevNumber, sizeof(LONG_NUMERIC), 1, primaryIndex);
        fwrite(&offset, sizeof(LONG_NUMERIC), 1, primaryIndex);
        serializeOMSVector(lhm, values);

        fclose(primaryIndex);
        fclose(values);
        unlink(objectGramSize_index.c_str());
        unlink(objectGramSize_values.c_str());
    }

    {
        slhmSerializeInOldFormat(ptr, mainDir+"/termToObjects.csv_vector.bin", mainDir+"/termToObjects.csv_values.bin", termObject, termObject_index, termObject_values);
    }

    {
        slhmSerializeInOldFormat(ptr, mainDir+"/objectGramSize.csv_vector.bin", mainDir+"/objectGramSize.csv_values.bin", objectGramSize, objectGramSize_index, objectGramSize_values);
    }

    {
        slhmSerializeInOldFormat(ptr, mainDir+"/gramToObjects.csv_vector.bin", mainDir+"/gramToObjects.csv_values.bin", gramToObject, gramToObject_index, gramToObject_values);
    }

    {
        twogramAndStringMultiplicity.c.close();
        external_merge_sort<sttgshmComparator> gasm_ems;
        gasm_ems.run(twogramAndStringMultiplicity_value, twogramAndStringMultiplicity_index, 3);

        std::string hashingFile = mainDir+"/twogramAndStringToMultiplicity.csv_vector.bin";
        std::string valuesFile = mainDir+"/twogramAndStringToMultiplicity.csv_values.bin";
        FILE *hashing = fopen(hashingFile.c_str(), "w");
        FILE *values = fopen(valuesFile.c_str(), "w");


        LONG_NUMERIC offset = 0;
        bool first = true;
        LONG_NUMERIC prevNumber =0;

        LinkedHashMultimap<std::string, std::pair<std::string, LONG_NUMERIC>> lhm;

        for (virtual_sorter::iterator it = termObject.begin(); it != termObject.end(); it++) {
            struct sttgshm *curr = (struct sttgshm *) it->iov_base;
            LONG_NUMERIC bucket = curr->hash;

            if (first)
                prevNumber = bucket;

            if (first || (prevNumber != bucket)) {
                fwrite(&bucket, sizeof(LONG_NUMERIC), 1, hashing);
                fwrite(&offset, sizeof(LONG_NUMERIC), 1, hashing);

                if (!first) {
                    offset += serializeTGASM(lhm, values);
                    lhm.clear();
                }

                prevNumber = bucket;
                first = false;
            }

            std::string str{curr->string, curr->strlen};
            LONG_NUMERIC ngramLen = curr->twograms[1] == '\0' ? 1 : 2;
            std::wstring ws{(wchar_t*)&curr->twograms, ngramLen};
            std::string ngram{ws.begin(), ws.end()};
            lhm.put(str, std::make_pair(ngram, curr->number));
        }

        offset += serializeTGASM(lhm, values);
        lhm.clear();

        fclose(hashing);
        fclose(values);
        unlink(twogramAndStringMultiplicity_index.c_str());
        unlink(twogramAndStringMultiplicity_value.c_str());
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
                offset += serializeTermObjectMap(lhm, values);
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
    serializeTermObjectMap(lhm, values);

    fclose(hashing);
    fclose(values);
    unlink(oldIndex.c_str());
    unlink(oldValues.c_str());
}

LONG_NUMERIC FuzzyMatchSerializerSEC::serializeTermObjectMap(LinkedHashMultimap<std::string, LONG_NUMERIC> &map,
                                                             FILE *values) {
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

LONG_NUMERIC FuzzyMatchSerializerSEC::serializeOMSVector(std::vector<std::string> &valuesVector, FILE *values) {
    // -- serializing the size of the properties vector
    LONG_NUMERIC n = valuesVector.size();
    LONG_NUMERIC buffSize = (n+1)*(sizeof(LONG_NUMERIC));

    fwrite(&n, sizeof(buffSize), 1, values);
    for (LONG_NUMERIC i = 0; i<n; i++) {
        std::string& x = valuesVector[i];
        fwrite(&buffSize, sizeof(buffSize), 1, values);
        buffSize += (x.size()+1);
    }

    for (LONG_NUMERIC i = 0; i<n; i++) {
        std::string& x = valuesVector[i];
        fwrite(x.c_str(), x.size()+1, 1, values);
    }
    return buffSize;
}

LONG_NUMERIC
FuzzyMatchSerializerSEC::serializeTGASM(LinkedHashMultimap<std::string, std::pair<std::string, LONG_NUMERIC>> &multimap,
                                        FILE *values) {

    LONG_NUMERIC nElement = multimap.data.size();

    // B. Sorting
    // Sorting the array by string elements, so that the strings may be searched in log time within the bucket
    // --> done in secondary memory: std::sort(element->overflowList.begin(), element->overflowList.end(), ltk2);
    // Then, sorting each key inside by the two gram element, so even the subkeys can be searched in logn time
    // --> done in secondary memory!
    // for (LONG_NUMERIC i = 0; i<nElement; i++) {
    //    std::sort(element->overflowList[i].second.begin(), element->overflowList[i].second.end(), ltk3);
    //}

    // Each element in the block is composed as so:
    // 1) number of strings associated to longs.
    //    the values are stored after the number of the elements...
    LONG_NUMERIC offsetsInBucketForKey = sizeof(LONG_NUMERIC);
    fwrite(&nElement, sizeof(LONG_NUMERIC), 1, values);

    // 2) offset of each string associated to long (see 3)
    ///   .., after the nElement offsets
    offsetsInBucketForKey += (sizeof(LONG_NUMERIC)*(nElement));

    // Then I serialize the values. Before doing that, I must evaluate which are the actual offsets that I have to use
    for (std::string& first : multimap.data) {
        // For each pair, I write the current offset for the keyMultivalue association
        fwrite(&offsetsInBucketForKey, sizeof(LONG_NUMERIC), 1, values);
        // size of vector     // actual vector size                                                    // stirng (key) associated to the vector
        offsetsInBucketForKey += (sizeof(LONG_NUMERIC)*2+(sizeof(LONG_NUMERIC)+sizeof(wchar_t)*2)*(multimap.map[first].size())+first.size()+1);
    }

    // 3) for each string, we have the size of the block associated to it
    //    such size is offsetToString + vecSize + [vector] + stirng.size+1
    for (std::string& first : multimap.data) {
        LONG_NUMERIC stirngSize = first.size()+1;

        // 1) string length
        fwrite(&stirngSize, sizeof(LONG_NUMERIC), 1, values);
        // 2) string
        fwrite(first.c_str(), stirngSize, 1, values);

        // 3) vector size after string_length+sizeof(LONG_NUMERIC)
        std::vector<std::pair<std::string, LONG_NUMERIC>> &second = multimap.map[first];
        LONG_NUMERIC size = second.size();
        fwrite(&size, sizeof(LONG_NUMERIC), 1, values);

        for (int i = 0; i<second.size(); i++) {
            // writing the two-grams ...
            std::wstring wide = this->converter.from_bytes(second[i].first.c_str());
            fwrite(((const wchar_t*)wide.c_str()), sizeof(wchar_t)*2, 1, values);
            // ... alongside the associated longs
            fwrite(&second[i].second, sizeof(LONG_NUMERIC), 1, values);
        }
    }
    return offsetsInBucketForKey;
}

bool ExternalULongKeyComparator2::greaterThan(void *leftM, size_t leftS, void *rightM, size_t rightS) {
    return ((uint_fast64_t*)(leftM)) > ((uint_fast64_t*)(rightM));
}
