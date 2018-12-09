//
// Created by giacomo on 26/09/18.
//

#include <cstring>
#include "STTGSHM_Secondary.h"

/*STTGSHM_Secondary::STTGSHM_Secondary(std::string &csvFile) {
    std::string vector = csvFile + "_vector.bin";
    std::string values = csvFile + "_values.bin";
    ///media/giacomo/OutputBlank/cout_exe/Weapon_csvDir/objectToMultipleStrings.csv_vector.bin
    pimarySparseIndex = (struct long_index_file*)(((char*)mmapFile(vector, &this->sizeVector, &fdVector)));
    primarySize = sizeVector / sizeof(struct long_index_file);
    element = ((char*)mmapFile(values, &this->sizeValues, &fdValues));
}

void STTGSHM_Secondary::clos() {
    if (pimarySparseIndex != nullptr) {
        munmap(pimarySparseIndex, sizeVector);
        pimarySparseIndex = nullptr;
        close(fdVector);
        sizeVector = fdVector = 0;
    }

    if (element != nullptr) {
        munmap(element, sizeValues);
        element = nullptr;
        close(fdValues);
        sizeValues = fdValues = 0;
    }
}

void *STTGSHM_Secondary::searchForId(std::string &toSearch) {
    LONG_NUMERIC hash = hashf(toSearch);
    struct long_index_file toSearchVehicle{};
    toSearchVehicle.id = hash;
    struct long_index_file* ptr = binVectorFixedSizeArray<struct long_index_file>(pimarySparseIndex, primarySize, &toSearchVehicle, &findLongIndexOffset);
    if (ptr == nullptr) return nullptr;
    LONG_NUMERIC* offsets = (LONG_NUMERIC*)(this->element+ptr->offset);
    LONG_NUMERIC n               = offsets[0];
    const LONG_NUMERIC* offsetPointer  = &offsets[1];
    LONG_NUMERIC toSerialize = toSearch.size()+1+sizeof(LONG_NUMERIC);
    const char*         bucketElements = (char*)offsets;//((char*)offsets)+((n+1)* sizeof(LONG_NUMERIC));
    char* mall = (char*)malloc(toSerialize);
    memset(mall, 0, toSerialize);
    strcpy(mall+ sizeof(LONG_NUMERIC), toSearch.c_str());
    void* toret = binVectorMutableSizeArray<char>(bucketElements, offsetPointer, n, mall, findStringndexOffset);
    toret = LONG_ARRAY_START(toret);
    free(mall);
    return toret;
}
*/