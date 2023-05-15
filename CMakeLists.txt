cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)
project(SpMV LANGUAGES C CXX)

add_executable(test)
include_directories(utils)

aux_source_directory(. SOURCES)
aux_source_directory(utils SOURCES)
target_sources(test PUBLIC ${SOURCES})