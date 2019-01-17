cmake_minimum_required(VERSION 2.8)
project(nanolod)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps")

add_definitions(
    -DNNL_USE_DATETIME
    #-DNNL_USE_BOOST_FORMAT
    -DNNL_SHORT_FILEPATH
)

include_directories(
    ./include
)

add_executable(
    ${PROJECT_NAME}
    ./include/nanolog/nanolog.hpp
    test.cpp
)
