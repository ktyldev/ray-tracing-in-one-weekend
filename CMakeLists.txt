cmake_minimum_required(VERSION 3.10)

project(flark)

file(GLOB flark_src
    "src/*.h"
    "src/*.cpp"
)

add_executable(flark ${flark_src})

