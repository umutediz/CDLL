if(NOT TARGET cdll)
    cmake_policy(SET CMP0048 NEW)

    project(CDLL VERSION 0.0.1)

    cmake_minimum_required(VERSION 3.14)

    add_library(cdll cdll.c)
    target_include_directories(cdll PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(tests)
endif()