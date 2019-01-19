cmake_minimum_required(VERSION 2.8)
project(nanolog)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps")

add_definitions(
    -DNNL_USE_DATETIME
    -DNNL_CONSIDER_TIMEZONE
    #-DNNL_USE_BOOST_FORMAT
    -DNNL_SHORT_FILEPATH
    #-DNNL_DISABLE_LOGGING
    -DNNL_FLUSH_EACH_RECORD
)

include_directories(
    ./include
)

add_executable(
    ${PROJECT_NAME}
    ./include/nanolog/nanolog.hpp
    test.cpp
)
