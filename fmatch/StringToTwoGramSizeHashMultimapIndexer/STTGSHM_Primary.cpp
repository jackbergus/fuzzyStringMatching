//
// Created by giacomo on 25/09/18.
//

#include "STTGSHM_Primary.h"
#include <iostream>

less_than_stringKey<std::vector<std::pair<std::string, LONG_NUMERIC>>> ltk2{};
less_than_stringKey<LONG_NUMERIC>                                ltk3{};

StringToTwoGramSizeHashMultimapIndexer::StringToTwoGramSizeHashMultimapIndexer() : ordered_multimap{&compareUL_Int} {}

void StringToTwoGramSizeHashMultimapIndexer::store(std::string &elem, std::string &twogram, LONG_NUMERIC value) {
    if (elem == "surface-to-air missile") {
        std::cerr << "element " << std::to_string(hfunc(elem)) << std::endl;
    }
    Node<LONG_NUMERIC, std::pair<std::string, std::vector<std::pair<std::string, LONG_NUMERIC>>>> *hashKey = ordered_multimap.insertKey(hfunc(elem));
    if (hashKey->getSize() != 0) {
        for (std::pair<std::string, std::vector<std::pair<std::string, LONG_NUMERIC>>> &x : hashKey->overflowList) {
            if (x.first == elem) {
                x.second.emplace_back(twogram, value);
                return;
            }
        }
    }
    std::vector<std::pair<std::string, LONG_NUMERIC>> element;
    element.emplace_back(twogram, value);
    hashKey->add(elem, element);
}

void StringToTwoGramSizeHashMultimapIndexer::serialize(FILE *hashing, FILE *values) {
    RBTree<LONG_NUMERIC, std::pair<std::string, std::vector<std::pair<std::string, LONG_NUMERIC>>>>::rbiterator it = ordered_multimap.iterator();
    LONG_NUMERIC offset = 0;
    while (it.hasNext()) {
        Node<LONG_NUMERIC, std::pair<std::string, std::vector<std::pair<std::string, LONG_NUMERIC>>>> *element = it.disposeWhileIterating();
        // A, Write Hashing for this bucket
        LONG_NUMERIC bucket = it.getCurrentK();
        fwrite(&bucket, sizeof(LONG_NUMERIC), 1, hashing);
        fwrite(&offset, sizeof(LONG_NUMERIC), 1, hashing);
        if (bucket == 429959643958480452L){
            fflush(hashing);
            std::cerr << "test " << std::endl;
        }
        LONG_NUMERIC nElement = element->overflowList.size();

        // B. Sorting
        // Sorting the array by string elements, so that the strings may be searched in log time within the bucket
        std::sort(element->overflowList.begin(), element->overflowList.end(), ltk2);
        // Then, sorting each key inside by the two gram element, so even the subkeys can be searched in logn time
        for (LONG_NUMERIC i = 0; i<nElement; i++) {
            std::sort(element->overflowList[i].second.begin(), element->overflowList[i].second.end(), ltk3);
        }

        // Each element in the block is composed as so:
        // 1) number of strings associated to longs.
        //    the values are stored after the number of the elements...
        LONG_NUMERIC offsetsInBucketForKey = sizeof(LONG_NUMERIC);
        fwrite(&nElement, sizeof(LONG_NUMERIC), 1, values);

        // 2) offset of each string associated to long (see 3)
        ///   .., after the nElement offsets
        offsetsInBucketForKey += (sizeof(LONG_NUMERIC)*(nElement));

        // Then I serialize the values. Before doing that, I must evaluate which are the actual offsets that I have to use
        for (std::pair<std::string, std::vector<std::pair<std::string, LONG_NUMERIC>>>& keyValueAssociation : element->overflowList) {
            // For each pair, I write the current offset for the keyMultivalue association
            fwrite(&offsetsInBucketForKey, sizeof(LONG_NUMERIC), 1, values);
                                      // size of vector     // actual vector size                                                    // stirng (key) associated to the vector
            offsetsInBucketForKey += (sizeof(LONG_NUMERIC)*2+(sizeof(LONG_NUMERIC)+sizeof(wchar_t)*2)*(keyValueAssociation.second.size())+keyValueAssociation.first.size()+1);
        }

        // 3) for each string, we have the size of the block associated to it
        //    such size is offsetToString + vecSize + [vector] + stirng.size+1
        for (std::pair<std::string, std::vector<std::pair<std::string, LONG_NUMERIC>>>& keyValueAssociation : element->overflowList) {
            LONG_NUMERIC stirngSize = keyValueAssociation.first.size()+1;

            // 1) string length
            fwrite(&stirngSize, sizeof(LONG_NUMERIC), 1, values);
            // 2) string
            fwrite(keyValueAssociation.first.c_str(), stirngSize, 1, values);

            // 3) vector size after string_length+sizeof(LONG_NUMERIC)
            LONG_NUMERIC size = keyValueAssociation.second.size();
            fwrite(&size, sizeof(LONG_NUMERIC), 1, values);

            for (int i = 0; i<keyValueAssociation.second.size(); i++) {
                // writing the two-grams ...
                std::wstring wide = this->converter.from_bytes(keyValueAssociation.second[i].first.c_str());
                fwrite(((const wchar_t*)wide.c_str()), sizeof(wchar_t)*2, 1, values);
                // ... alongside the associated longs
                fwrite(&keyValueAssociation.second[i].second, sizeof(LONG_NUMERIC), 1, values);
            }
        }
        offset += offsetsInBucketForKey;

    }
    fclose(hashing);
    fclose(values);
}
