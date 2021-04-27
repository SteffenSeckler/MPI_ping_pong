cmake_minimum_required(VERSION 3.17)
project(MPI_ping_pong)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)
if (NOT ${MPI_CXX_FOUND})
    message(FATAL_ERROR "cxx mpi could not be found")
endif ()

add_executable(MPI_ping_pong main.cpp)
target_link_libraries(MPI_ping_pong
        PUBLIC
        MPI::MPI_CXX)