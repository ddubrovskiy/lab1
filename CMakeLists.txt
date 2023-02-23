cmake_minimum_required(VERSION 3.21)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab1 main.cpp AneuMeshLoader.cpp AneuMeshLoader.h MeshLoader.cpp MeshLoader.h Struct.cpp Struct.h Exception.h Hash.h)
