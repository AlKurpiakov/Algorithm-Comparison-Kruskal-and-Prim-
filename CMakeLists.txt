cmake_minimum_required(VERSION 3.10)

project(AlgorithmComparison)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    main.cpp    
    src/DSU.cpp
    src/Graph.cpp
    src/Kruskal.cpp
    src/Prim.cpp
    testkit/testkit.cpp
)

set(HEADERS
    testkit/testkit.h
    include/DSU.h
    include/Graph.h
    include/Kruskal.h
    include/Prim.h
)



add_executable(AlgorithmComparison main.cpp ${SOURCES} ${HEADERS})

target_include_directories(AlgorithmComparison PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_compile_options(AlgorithmComparison PRIVATE
    -march=native
    -ffast-math
    -ftree-vectorize
    -fpic
)

target_compile_features(AlgorithmComparison PRIVATE cxx_std_17)