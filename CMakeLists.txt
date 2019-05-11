cmake_minimum_required(VERSION 3.10)
project(inconsistency)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fconstexpr-depth=5023 -m64")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(third_party/rapidjson/include)
include_directories(third_party/graphnestingc)
add_subdirectory(third_party/graphnestingc)

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/modules)

ADD_LIBRARY(fuzzystringmatching STATIC
			fmatch/LongStringValueMultimapIndexer/LSVM_Primary.cpp
                         fmatch/LongStringValueMultimapIndexer/LSVM_Secondary.cpp
                         fmatch/StringLongHashMultimapIndexer/SLHM_Primary.cpp
                         fmatch/StringLongHashMultimapIndexer/SLHM_Secondary.cpp
                         fmatch/StringToTwoGramSizeHashMultimapIndexer/STTGSHM_Primary.cpp
                         fmatch/StringToTwoGramSizeHashMultimapIndexer/STTGSHM_Secondary.cpp
                         fmatch/FuzzyMatch_FDContainer.cpp
                         merging/fuzzymatch/FuzzyMatch.cpp
                        merging/fuzzymatch/FuzzyMatchSerializer.cpp
                        utils/fixed_bimap.h
                        utils/memory_utils.cpp
                        utils/memory_utils.h
                        merging/jsons/idToOffsetHandler.cpp merging/jsons/idToOffsetHandler.h
                        merging/jsons/objectToMultipleStrings.cpp
                        merging/jsons/objectToMultipleStrings.h
                        merging/conceptnet/deserialization/conceptnet5_vertex.cpp
                        merging/conceptnet/deserialization/conceptnet5_vertex.h
                        merging/conceptnet/utils.cpp
                        merging/conceptnet/utils.h
                        fromJava/trimmers.cpp
                        fromJava/trimmers.h)


add_executable(fuzzy_string_matching main.cpp )
add_executable(csv_serializers fmatch/csv_serializer.cpp )
add_executable(lib_fuzzymatch_test fmatch/libfuzzymatching_test.cpp)

#add_executable(inconsistency main.cpp relationships/RelationshipTypes.h internal_state/InternalState.cpp internal_state/InternalState.h merging/conceptnet/deserialization/conceptnet_edge_deserialization.cpp merging/conceptnet/deserialization/conceptnet_edge_deserialization.h merging/conceptnet/utils.cpp merging/conceptnet/utils.h relationships/RelationshipTypes.cpp serializers/commons/secondary_memory/utils/Graph.cpp serializers/utils/mmapFile.cpp merging/graph_conceptnet/GraphQueryIterator.cpp merging/conceptnet/ConceptNet5Dumps.cpp merging/conceptnet/ConceptNet5Dumps.h merging/SplitStringIterator.cpp merging/SplitStringIterator.h numeric/compares.cpp datasets/NELL/NELL.cpp datasets/NELL/NELL.h datasets/ICEWS/ICEWSPlace.h datasets/ICEWS/ICEWSPlace.cpp datasets/ICEWS/ICEWSArgument.cpp datasets/ICEWS/ICEWSArgument.h datasets/ICEWS/ICEWS.cpp datasets/ICEWS/ICEWS.h datasets/NELL/NELLArgument.cpp datasets/NELL/NELLArgument.h datasets/Phoenix/PhoenixTime.cpp datasets/Phoenix/PhoenixTime.h datasets/Phoenix/PhoenixArgument.cpp datasets/Phoenix/PhoenixArgument.h datasets/Phoenix/PhoenixPlace.cpp datasets/Phoenix/PhoenixPlace.h datasets/Phoenix/Phoenix.cpp datasets/Phoenix/Phoenix.h datasets/GDELT/GDELTPlace.cpp datasets/GDELT/GDELTPlace.h datasets/GDELT/GDELTTime.cpp datasets/GDELT/GDELTTime.h datasets/GDELT/GDELTArgument.cpp datasets/GDELT/GDELTArgument.h datasets/GDELT/GDELT.cpp datasets/GDELT/GDELT.h datasets/GDELT/GDELTRelation.cpp datasets/GDELT/GDELTRelation.h datasets/NELL/NELLRelation.cpp datasets/NELL/NELLRelation.h datasets/helpers/Helpers.cpp datasets/helpers/Helpers.h fromJava/trimmers.cpp fromJava/trimmers.h numeric/ProgressBar.cpp numeric/ProgressBar.h merging/csv_istream.cpp merging/csv_istream.h merging/CSVIterator.cpp merging/CSVIterator.h serializers/Streamers.cpp serializers/Streamers.h
#                                      ${FUZZY_MACTH_SOURCES})
#target_include_directories(inconsistency PUBLIC ${LEMON_INCLUDE_DIR})
#target_link_libraries(inconsistency PUBLIC ${LEMON_LIBRARIES})
target_link_libraries(fuzzy_string_matching ${Boost_LIBRARIES} fuzzystringmatching graphserializers)
target_link_libraries(lib_fuzzymatch_test ${Boost_LIBRARIES} fuzzystringmatching graphserializers)
target_link_libraries(csv_serializers ${Boost_LIBRARIES} pthread fuzzystringmatching graphserializers)
