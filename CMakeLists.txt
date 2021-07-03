cmake_minimum_required(VERSION 3.10)
project(fuzzyStringMatching)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-fconstexpr-depth=5023 -m64")
#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME ON)
include_directories(include)
find_package(Boost 1.71.0 REQUIRED COMPONENTS system filesystem serialization)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(third_party/rapidjson/include)
include_directories(third_party/graphnestingc)
add_subdirectory(third_party/graphnestingc)
add_subdirectory(third_party/varsorter)
include_directories(third_party/csv)

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/modules)

ADD_LIBRARY(fuzzystringmatching STATIC
		src/versions/v0.1/LongStringValueMultimapIndexer/LSVM_Primary.cpp
		src/versions/v0.1/LongStringValueMultimapIndexer/LSVM_Secondary.cpp
		src/versions/v0.1/StringLongHashMultimapIndexer/SLHM_Primary.cpp
		src/versions/v0.1/StringLongHashMultimapIndexer/SLHM_Secondary.cpp
		src/versions/v0.1/StringToTwoGramSizeHashMultimapIndexer/STTGSHM_Primary.cpp
		src/versions/v0.1/StringToTwoGramSizeHashMultimapIndexer/STTGSHM_Secondary.cpp
		src/versions/v0.1/FuzzyMatch_FDContainer.cpp
		src/versions/v0.2/FuzzyMatch.cpp
		src/versions/v0.2/FuzzyMatchSerializer.cpp
		include/structures/fixed_bimap.h
		src/utils/memory_utils.cpp
		include/utils/memory_utils.h
		#merging/jsons/objectToMultipleStrings.cpp
        #                merging/jsons/objectToMultipleStrings.h
        #                merging/conceptnet/deserialization/conceptnet5_vertex.cpp
        #                merging/conceptnet/deserialization/conceptnet5_vertex.h
		src/utils/trimmers.cpp
		include/utils/trimmers.h src/versions/v0.2/FuzzyMatchSerializerSEC.cpp include/versions/v0.2/FuzzyMatchSerializerSEC.h src/utils/stringuitls.cpp include/utils/stringuitls.h include/structures/LinkedHashMultimap.h)


add_executable(fuzzy_string_matching mains/main.cpp)
add_executable(csv_serializers mains/csv_serializer.cpp)
add_executable(lib_fuzzymatch_test mains/libfuzzymatching_test.cpp)

#add_executable(inconsistency main.cpp relationships/RelationshipTypes.h internal_state/InternalState.cpp internal_state/InternalState.h merging/conceptnet/deserialization/conceptnet_edge_deserialization.cpp merging/conceptnet/deserialization/conceptnet_edge_deserialization.h merging/conceptnet/utils.cpp merging/conceptnet/utils.h relationships/RelationshipTypes.cpp serializers/commons/secondary_memory/utils/Graph.cpp serializers/utils/mmapFile.cpp merging/graph_conceptnet/GraphQueryIterator.cpp merging/conceptnet/ConceptNet5Dumps.cpp merging/conceptnet/ConceptNet5Dumps.h merging/SplitStringIterator.cpp merging/SplitStringIterator.h numeric/compares.cpp datasets/NELL/NELL.cpp datasets/NELL/NELL.h datasets/ICEWS/ICEWSPlace.h datasets/ICEWS/ICEWSPlace.cpp datasets/ICEWS/ICEWSArgument.cpp datasets/ICEWS/ICEWSArgument.h datasets/ICEWS/ICEWS.cpp datasets/ICEWS/ICEWS.h datasets/NELL/NELLArgument.cpp datasets/NELL/NELLArgument.h datasets/Phoenix/PhoenixTime.cpp datasets/Phoenix/PhoenixTime.h datasets/Phoenix/PhoenixArgument.cpp datasets/Phoenix/PhoenixArgument.h datasets/Phoenix/PhoenixPlace.cpp datasets/Phoenix/PhoenixPlace.h datasets/Phoenix/Phoenix.cpp datasets/Phoenix/Phoenix.h datasets/GDELT/GDELTPlace.cpp datasets/GDELT/GDELTPlace.h datasets/GDELT/GDELTTime.cpp datasets/GDELT/GDELTTime.h datasets/GDELT/GDELTArgument.cpp datasets/GDELT/GDELTArgument.h datasets/GDELT/GDELT.cpp datasets/GDELT/GDELT.h datasets/GDELT/GDELTRelation.cpp datasets/GDELT/GDELTRelation.h datasets/NELL/NELLRelation.cpp datasets/NELL/NELLRelation.h datasets/helpers/Helpers.cpp datasets/helpers/Helpers.h fromJava/trimmers.cpp fromJava/trimmers.h numeric/ProgressBar.cpp numeric/ProgressBar.h merging/csv_istream.cpp merging/csv_istream.h merging/CSVIterator.cpp merging/CSVIterator.h serializers/Streamers.cpp serializers/Streamers.h
#                                      ${FUZZY_MACTH_SOURCES})
#target_include_directories(inconsistency PUBLIC ${LEMON_INCLUDE_DIR})
#target_link_libraries(inconsistency PUBLIC ${LEMON_LIBRARIES})
target_link_libraries(fuzzy_string_matching LINK_PUBLIC ${Boost_LIBRARIES} fuzzystringmatching graphserializers libvarsorter stdc++fs)
target_link_libraries(lib_fuzzymatch_test LINK_PUBLIC ${Boost_LIBRARIES} fuzzystringmatching graphserializers libvarsorter stdc++fs)
target_link_libraries(csv_serializers LINK_PUBLIC ${Boost_LIBRARIES} pthread fuzzystringmatching graphserializers libvarsorter stdc++fs)
