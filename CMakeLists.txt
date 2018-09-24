cmake_minimum_required(VERSION 3.9)
project(edgeindexing)

set(CMAKE_CXX_STANDARD 17)

add_executable(edgeindexing serializer.cpp numeric/compares.cpp serializers/commons/Serialize.cpp relationships.h fromJava/evaluateHashes.c fromJava/evaluateHashes.h)

set(SOURCE_FILE_READER serializers/utils/mmapFile.cpp serializers/commons/secondary_memory/utils/Graph.cpp numeric/compares.cpp serializers/commons/Serialize.cpp relationships.h fromJava/evaluateHashes.c fromJava/evaluateHashes.h)
add_executable(reader reader_test.cpp ${SOURCE_FILE_READER})

find_package(Java REQUIRED)
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})
add_library(jni SHARED ${SOURCE_FILE_READER} jni.cpp)
set_target_properties(jni PROPERTIES SUFFIX ".so")
target_link_libraries(jni ${JNI_LIBRARIES})