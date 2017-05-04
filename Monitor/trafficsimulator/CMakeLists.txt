cmake_minimum_required(VERSION 2.6)
set(NAME_PROJECT ciudadlib)
project(${NAME_PROJECT})

add_compile_options(-std=c++11)

set(libreria 
	

)


add_library(ciudadlib STATIC
    ${libreria}
)

# Specify here the include directories exported
# by this library
target_include_directories(ciudadlib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)



