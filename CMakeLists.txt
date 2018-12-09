cmake_minimum_required(VERSION 3.10)
project(inconsistency)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fconstexpr-depth=5023 -O2 -m64")
include_directories(lib/rapidjson/include)

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/modules)

add_executable(inconsistency main.cpp relationships/RelationshipTypes.h internal_state/InternalState.cpp internal_state/InternalState.h conceptnet/deserialization/conceptnet_edge_deserialization.cpp conceptnet/deserialization/conceptnet_edge_deserialization.h conceptnet/utils.cpp conceptnet/utils.h relationships/RelationshipTypes.cpp serializers/commons/secondary_memory/utils/Graph.cpp serializers/utils/mmapFile.cpp merging/graph_conceptnet/GraphQueryIterator.cpp)
target_include_directories(inconsistency PUBLIC ${LEMON_INCLUDE_DIR})
target_link_libraries(inconsistency PUBLIC ${LEMON_LIBRARIES})