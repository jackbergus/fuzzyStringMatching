//
// Created by giacomo on 25/09/18.
//

#include <iostream>
#include "LSVM_Primary.h"

LongStringValueMultimapIndexer_Primary::LongStringValueMultimapIndexer_Primary() : ordered_multimap{&compareUL_Int} {}

void LongStringValueMultimapIndexer_Primary::store(LONG_NUMERIC id, std::string &element) {
    ordered_multimap.insertKey(id)->overflowList.push_back(element);
    if (id > maxLong) maxLong = id;
}

void LongStringValueMultimapIndexer_Primary::serialize(FILE *primaryIndex, FILE *values) {
    RBTree<LONG_NUMERIC, std::string>::rbiterator it = ordered_multimap.iterator();
    LONG_NUMERIC prevElement = 0;
    LONG_NUMERIC noOffset = 0;
    char init = ' ';

    // Initial header: position zero is set to nothing.
    // For this data structure the zero is just a
    fwrite(&init, sizeof(char), 1, values);
    LONG_NUMERIC offset = 1;
    while (it.hasNext()) {
        Node<LONG_NUMERIC, std::string>* element = it.disposeWhileIterating();
        LONG_NUMERIC key = it.getCurrentK();
        // Writing all the longs as not appearing, that is stored at position zero
        // --> This approach would have quicker performances, via an O(1) access time, but I cannot "pay"
        //     for several gigabites of secondary memory. Therefore, even the longs will be sorted
        //     This also makes the serialization far way more efficient
        //for (LONG_NUMERIC i = prevElement; i<key; i++)
        //    fwrite(&noOffset, sizeof(LONG_NUMERIC), 1, primaryIndex);

        // Writing the key and the offset for the current element
        fwrite(&key, sizeof(LONG_NUMERIC), 1, primaryIndex);
        fwrite(&offset, sizeof(LONG_NUMERIC), 1, primaryIndex);

        // -- serializing the size of the properties vector
        LONG_NUMERIC n = element->overflowList.size();
        LONG_NUMERIC buffSize = (n+1)*(sizeof(LONG_NUMERIC));

        fwrite(&n, sizeof(buffSize), 1, values);
        for (LONG_NUMERIC i = 0; i<n; i++) {
            std::string& x = element->overflowList[i];
            fwrite(&buffSize, sizeof(buffSize), 1, values);
            buffSize += (x.size()+1);
        }

        for (LONG_NUMERIC i = 0; i<n; i++) {
            std::string& x = element->overflowList[i];
            fwrite(x.c_str(), x.size()+1, 1, values);
        }
        offset += buffSize;
    }

    fclose(primaryIndex);
    fclose(values);
}
