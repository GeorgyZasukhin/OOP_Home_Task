cmake_minimum_required(VERSION 3.20)

project(Lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

add_executable(Lab1
    src/main.cpp
    src/Plant.cpp
)

target_compile_options(Lab1 PRIVATE -Wall -Wextra -Wpedantic)

if(ENABLE_SANITIZERS)
    target_compile_options(Lab1 PRIVATE -fsanitize=address,undefined)
    target_link_options(Lab1 PRIVATE -fsanitize=address,undefined)
endif()
