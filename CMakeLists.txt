cmake_minimum_required(VERSION 3.9)
project(edgeindexing)

set(CMAKE_CXX_STANDARD 17)

add_executable(pgdump_serializer pgdump/serializer.cpp numeric/compares.cpp serializers/commons/Serialize.cpp fromJava/evaluateHashes.c fromJava/evaluateHashes.h fmatch/csv.h fromJava/classes.h)

find_package (Threads)
add_executable(fmatch_csv_serializer numeric/compares.cpp serializers/commons/Serialize.cpp serializers/utils/mmapFile.cpp fromJava/evaluateHashes.c fromJava/evaluateHashes.h fmatch/csv_serializer.cpp fmatch/LongStringValueMultimapIndexer/LSVM_Primary.cpp fmatch/LongStringValueMultimapIndexer/LSVM_Primary.h fmatch/libfuzzymatch.h fmatch/StringLongHashMultimapIndexer/SLHM_Primary.cpp fmatch/StringLongHashMultimapIndexer/SLHM_Primary.h fmatch/StringToTwoGramSizeHashMultimapIndexer/STTGSHM_Primary.cpp fmatch/StringToTwoGramSizeHashMultimapIndexer/STTGSHM_Primary.h algorithms/binsearch.h fmatch/LongStringValueMultimapIndexer/LSVM_Secondary.cpp fmatch/LongStringValueMultimapIndexer/LSVM_Secondary.h fmatch/StringLongHashMultimapIndexer/SLHM_Secondary.cpp fmatch/StringLongHashMultimapIndexer/SLHM_Secondary.h fmatch/StringToTwoGramSizeHashMultimapIndexer/STTGSHM_Secondary.cpp fmatch/StringToTwoGramSizeHashMultimapIndexer/STTGSHM_Secondary.h)
target_link_libraries (fmatch_csv_serializer ${CMAKE_THREAD_LIBS_INIT})

set(SOURCE_FILE_READER serializers/utils/mmapFile.cpp serializers/commons/secondary_memory/utils/Graph.cpp numeric/compares.cpp serializers/commons/Serialize.cpp fromJava/evaluateHashes.c fromJava/evaluateHashes.h)
add_executable(libjni_test pgdump/libjni_test.cpp ${SOURCE_FILE_READER})

find_package(Java REQUIRED)
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

add_library(jni SHARED ${SOURCE_FILE_READER} pgdump/libjni.cpp)
set_target_properties(jni PROPERTIES SUFFIX ".so")
target_link_libraries(jni ${JNI_LIBRARIES})

set(SOURCE_FUZZYMATCHER     numeric/compares.cpp
                            serializers/commons/Serialize.cpp
                            serializers/utils/mmapFile.cpp
                            fromJava/evaluateHashes.c
                            fromJava/evaluateHashes.h
                            fmatch/LongStringValueMultimapIndexer/LSVM_Primary.cpp
                            fmatch/LongStringValueMultimapIndexer/LSVM_Primary.h
                            fmatch/libfuzzymatch.h
                            fmatch/StringLongHashMultimapIndexer/SLHM_Primary.cpp
                            fmatch/StringLongHashMultimapIndexer/SLHM_Primary.h
                            fmatch/StringToTwoGramSizeHashMultimapIndexer/STTGSHM_Primary.cpp
                            fmatch/StringToTwoGramSizeHashMultimapIndexer/STTGSHM_Primary.h
                            algorithms/binsearch.h
                            fmatch/LongStringValueMultimapIndexer/LSVM_Secondary.cpp
                            fmatch/LongStringValueMultimapIndexer/LSVM_Secondary.h
                            fmatch/StringLongHashMultimapIndexer/SLHM_Secondary.cpp
                            fmatch/StringLongHashMultimapIndexer/SLHM_Secondary.h
                            fmatch/StringToTwoGramSizeHashMultimapIndexer/STTGSHM_Secondary.cpp
                            fmatch/StringToTwoGramSizeHashMultimapIndexer/STTGSHM_Secondary.h
                            fmatch/PollMap.h
                            fmatch/FuzzyMatch_FDContainer.cpp
                            fmatch/FuzzyMatch_FDContainer.h)

add_executable(libfuzzymatching_test ${SOURCE_FUZZYMATCHER} fmatch/libfuzzymatching_test.cpp)

add_library(fuzzymatching SHARED fmatch/libfuzzymatch.cpp
                                 ${SOURCE_FUZZYMATCHER})
set_target_properties(fuzzymatching PROPERTIES SUFFIX ".so")
target_link_libraries(fuzzymatching ${JNI_LIBRARIES})