//
// Created by giacomo on 26/08/19.
//

#ifndef INCONSISTENCY_FUZZYMATCHSERIALIZERSEC_H
#define INCONSISTENCY_FUZZYMATCHSERIALIZERSEC_H

#include <string>
#include <vector>

#include <serializers/commons/structure.h>
#include "../../third_party/varsorter/external_merge_sort/ExternalULongKeyComparator.h"
#include "../../third_party/varsorter/src/KeyValueStore.h"
#include "../../utils/stringuitls.h"
#include "../../fromJava/LinkedHashMultimap.h"

class ExternalULongKeyComparator2 : public QuicksortLessComparator {
public:
    bool greaterThan(void *leftM, size_t leftS, void *rightM, size_t rightS) override;
};

struct slhm {
    LONG_NUMERIC hash;
    LONG_NUMERIC number;
    LONG_NUMERIC strlen;
    //char      string[];    --> Struct hack do not work on C++
};

/**
 * Struct hacks do not work in C++. Therefore, simply point at the end of the structure of choice.
 */
#define struct_hack(T, ptr)     ((char*)(((char*)(ptr)) + sizeof(T)))
#define slhm_hack(ptr)          struct_hack(struct slhm, ptr)
#define sttgshm_hack(ptr)       struct_hack(struct sttgshm, ptr)

class slhmComparator : public QuicksortLessComparator {
public:
    bool greaterThan(void *leftM, size_t leftS, void *rightM, size_t rightS) override {
        struct slhm *left = (struct slhm*)leftM, *right = (struct slhm*)rightM;
        return (left->hash < right->hash) ||
                ((left->hash == right->hash) && (strnmcmp(slhm_hack(left), left->strlen, slhm_hack(right), right->strlen) > 0));
    }
};

struct sttgshm {
    LONG_NUMERIC hash;
    LONG_NUMERIC number;
    LONG_NUMERIC strlen;
    wchar_t      twograms[2];
    //char      string[];
};

class sttgshmComparator : public QuicksortLessComparator {
public:
    bool greaterThan(void *leftM, size_t leftS, void *rightM, size_t rightS) override {
        struct sttgshm *left = (struct sttgshm*)leftM, *right = (struct sttgshm*)rightM;
        int cmp = strnmcmp(sttgshm_hack(left), left->strlen, sttgshm_hack(right), right->strlen);
        return (left->hash < right->hash) ||
               ((left->hash == right->hash) && (cmp > 0)) ||
                ((left->hash == right->hash) && (cmp == 0) && (left->twograms[0] > right->twograms[0] || (left->twograms[0] == right->twograms[0] && (!left->twograms[0]) && left->twograms[1] > right->twograms[1])));
    }
};

#include <locale>
#include <codecvt>

class FuzzyMatchSerializerSEC {
    std::string mainDir;

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::hash<std::string> stringhashing;

    smart_malloc oms_malloc;
    KeyValueStore<ExternalULongKeyComparator2> objectMultipleStirngs;
    std::string objectMultipleStirngs_index, objectMultipleStirngs_values;

    smart_malloc slhm_malloc;
    KeyValueStore<slhmComparator> gramToObject, objectGramSize, termObject;
    std::string gramToObject_index, gramToObject_values;
    std::string objectGramSize_index, objectGramSize_values;
    std::string termObject_index, termObject_values;
    
    smart_malloc twogramAndStringMultiplicity_malloc;
    KeyValueStore<sttgshmComparator> twogramAndStringMultiplicity;
    std::string twogramAndStringMultiplicity_index, twogramAndStringMultiplicity_value;

public:
    FuzzyMatchSerializerSEC(std::string path);
public:
    /**
     * This method creates all the indices in primary memory
     *
     * @param string                        Preferred string associated to the object
     * @param id                            Object id (eg. an offset)
     * @param associatedOtherStrings        Other secondary strings associated to the preferred object
     */
    void addGramsToMap(std::string &string, LONG_NUMERIC id,
                       std::vector<std::string> &associatedOtherStrings);

    /**
     * This method serializes the indices as several secondary memory files.
     * If it is a file, it will try to delete the file first.
     * If the current path does not exists, it will try to create the folder (mkdirs)
     *
     * @param path
     */
    void serialize();

private:
    void serializeToObjectMultimap(const std::string &string, LONG_NUMERIC id);
    void serializeToSLHM(const std::string &string, LONG_NUMERIC id, KeyValueStore<slhmComparator> &serializer);
    LONG_NUMERIC serializeTermObjectMap(LinkedHashMultimap<std::string, LONG_NUMERIC> &map, FILE *values);
    void slhmSerializeInOldFormat(void_virtual_sorter *ptr, const std::string hashingFile, const std::string valuesFile, KeyValueStore<slhmComparator> &c, std::string &oldIndex, std::string &oldValues);
    LONG_NUMERIC serializeOMSVector(std::vector<std::string> &valuesVector, FILE *values);
    LONG_NUMERIC serializeTGASM(LinkedHashMultimap<std::string, std::pair<std::string, LONG_NUMERIC>> &multimap, FILE *pFile);
};


#endif //INCONSISTENCY_FUZZYMATCHSERIALIZERSEC_H
