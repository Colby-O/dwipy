get_filename_component(MODULUENAME ${CMAKE_CURRENT_LIST_DIR} NAME)

#--- Finds all C++ sources and headers
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")

#--- Sets release flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
#--- Sets debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

#--- Add Shared Library
add_library(${MODULUENAME} SHARED ${SOURCES} ${HEADERS})

#--- Links Lib header files
target_include_directories(${MODULUENAME} PUBLIC ${PYTHON_INCLUDE_DIRS} ${ROOT_DIR})

#--- -flat_namespace works but doesn't work with r-paths
#--- -undefined dynamic_lookup should work but doesn't need to look into why given this is optiomal solution 
#--- -undefined dynamic_lookup deffers all undefined symbols until runtime
#--- Currently this is a necessary "evil" for scalability but should look into better alnertives  
if(APPLE)
    target_link_libraries(${MODULUENAME}
        PRIVATE
            -flat_namespace
            #-Wl,-U,_Py_InitModule4_64
            #-weak_library ${PYTHON_LIBRARIES}
            #-lazy_library ${PYTHON_LIBRARIES}
            ${PYTHON_LIBRARIES}
            GSL::gsl 
            GSL::gslcblas
            #"-undefined dynamic_lookup"
            -O3
    )
else() 
    #--- TODO: Investage linking on platforms other than MacOS
    target_link_libraries(${MODULUENAME} PUBLIC ${PYTHON_LIBRARIES} Unitsv1 GSL::gsl GSL::gslcblas "-O3")
endif()

#--- Set Target properties
set_target_properties(
    ${MODULUENAME}
    PROPERTIES
        PREFIX ""
        OUTPUT_NAME dwipySrc.cpython-39-darwin # TODO: Fix only works for MacOs atm
        LINKER_LANGUAGE CXX
)