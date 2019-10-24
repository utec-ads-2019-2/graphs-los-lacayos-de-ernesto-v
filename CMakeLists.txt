cmake_minimum_required(VERSION 3.14)
project(graphs_los_lacayos_de_ernesto_v)

set(CMAKE_CXX_STANDARD 14)

include(/Users/m.noel/Desktop/ya/graphs-los-lacayos-de-ernesto-v/Build/conanbuildinfo.cmake)

conan_basic_setup()

add_executable(graphs_los_lacayos_de_ernesto_v
        Airports.h
        Edge.h
        graph.h
        main.cpp
        nodos.h)

link_libraries(graphs_los_lacayos_de_ernesto_v ${CONAN_LIBS})