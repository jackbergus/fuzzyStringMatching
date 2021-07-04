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
include_directories(third_party/yaucl/include)
add_subdirectory(third_party/graphnestingc)
add_subdirectory(third_party/varsorter)
add_subdirectory(third_party/yaucl)
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
		src/versions/v0.2/FuzzyMatchSerializerSEC.cpp include/versions/v0.2/FuzzyMatchSerializerSEC.h)
target_link_libraries(fuzzystringmatching yaucl_strings)

add_executable(fuzzy_string_matching mains/main.cpp)

add_executable(csv_serializers mains/csv_serializer.cpp)
add_executable(lib_fuzzymatch_test mains/libfuzzymatching_test.cpp)


target_link_libraries(fuzzy_string_matching LINK_PUBLIC  ${Boost_LIBRARIES} yaucl_strings fuzzystringmatching graphserializers libvarsorter stdc++fs)
target_link_libraries(lib_fuzzymatch_test LINK_PUBLIC  ${Boost_LIBRARIES} yaucl_strings fuzzystringmatching graphserializers libvarsorter stdc++fs)
target_link_libraries(csv_serializers LINK_PUBLIC  ${Boost_LIBRARIES} pthread yaucl_strings fuzzystringmatching graphserializers libvarsorter stdc++fs)
