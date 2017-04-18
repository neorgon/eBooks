cmake_minimum_required(VERSION 2.6)
set(NAME_PROJECT thinker_All)
project(${NAME_PROJECT})
set(GLOB abc ./src/*.cpp)
set(GLOB asd ./include/*.h)
set(libreria 
	./exceptions/SemanticException.cpp
	./exceptions/SemanticException.h
	./exceptions/SyntaxException.cpp
	./exceptions/SyntaxException.h 
	${abc} 
	${asd}
)


add_library(scannerlib STATIC
    ${libreria}
)

# Specify here the include directories exported
# by this library
target_include_directories(scannerlib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(Main_SRCS
    main.cpp
)

add_executable(scanner
    ${Main_SRCS}
)

# Specify here the libraries this program depends on
target_link_libraries(scanner
    scannerlib
)
