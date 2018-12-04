cmake_minimum_required(VERSION 3.10)
project(inconsistency)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-fconstexpr-depth=5023")
include_directories(lib/rapidjson/include)

add_executable(inconsistency main.cpp relationships/RelationshipTypes.h internal_state/InternalState.cpp internal_state/InternalState.h conceptnet/deserialization/conceptnet_edge_deserialization.cpp conceptnet/deserialization/conceptnet_edge_deserialization.h conceptnet/utils.cpp conceptnet/utils.h relationships/RelationshipTypes.cpp)