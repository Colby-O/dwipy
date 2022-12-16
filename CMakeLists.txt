cmake_minimum_required(VERSION 3.10)

project(dwipy)

#--- Sets root of the project
set(ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/src/")

#-- Sets Shared Library output to .so instead of a .dylib if MacOS
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build architectures for Mac OS X" FORCE)
    set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
endif(APPLE)

#--- Load the common configuration
include(common/config.cmake)

#--- Python configuration
include(common/FindPython.cmake)
include(common/GetGSL.cmake)

#--- add subdirectory
add_subdirectory(src/dwipy)


#--- C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)