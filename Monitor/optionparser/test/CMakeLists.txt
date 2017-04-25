cmake_minimum_required(VERSION 2.8.9)
project(testParcer)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_compile_options(-std=c++11)

set(test 
   // ITest.cpp
    ATest.cpp
  //  Utest.cpp
)

add_executable(optionparser
    ${test}
)

if(TARGET optionparserlib)
	
else()
	add_subdirectory(./../../optionparser optionparser)
endif() 

if(TARGET googlet)

else()
	add_subdirectory(./../../thirdParty/googletest googletest)
endif()

if(TARGET optionparser)

add_subdirectory(../../thirdParty/googletest googletest)

endif()
target_link_libraries(optionparser 
    optionparserlib googlet 
)
target_include_directories(optionparser PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
