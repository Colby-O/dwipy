find_package(GSL REQUIRED)

include_directories(${GSL_INCLUDE_DIR})

#--- Error Handling
if(NOT GSL_FOUND)
    messgae(ERROR "GSL was not found!")
else()
    add_definitions(-DWITH_GSL)
endif()