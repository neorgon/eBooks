cmake_minimum_required(VERSION 2.8)

set(test 
    ITest.cpp
    ATest.cpp
    Utest.cpp
)

add_executable(optionparser
    ${test}
)

# Specify here the libraries this program depends on
if(TARGET googlet)

add_subdirectory(../../thirdParty/googletest googletest)

endif()
target_link_libraries(optionparser 
    googlet
)
target_include_directories(thinker PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
