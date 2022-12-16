message(STATUS "dwipy - Loading Common Comfiguration")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

include_directories(${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE COMMON_DIR_HEADERS "${CMAKE_CURRENT_LIST_DIR}/*.h")
add_custom_target(common_headers SOURCES ${COMMON_DIR_HEADERS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")