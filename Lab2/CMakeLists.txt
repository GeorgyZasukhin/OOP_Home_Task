cmake_minimum_required(VERSION 3.20)
project(Lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Enable address and undefined sanitizers" OFF)

add_library(performance Lab2/performance.cpp)
target_include_directories(performance PUBLIC Lab2)
target_compile_options(performance PUBLIC -Wall -Wextra -Wpedantic)

if(ENABLE_SANITIZERS)
    target_compile_options(performance PUBLIC
        -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(performance PUBLIC -fsanitize=address,undefined)
endif()

add_executable(Lab2 Lab2/main.cpp)
target_link_libraries(Lab2 PRIVATE performance)

include(CTest)
if(BUILD_TESTING)
    add_executable(performance_test tests/performance_test.cpp)
    target_include_directories(performance_test SYSTEM PRIVATE third_party)
    target_link_libraries(performance_test PRIVATE performance)
    foreach(case RANGE 1 15)
        add_test(NAME performance_${case}
            COMMAND performance_test --test-case=case_${case})
    endforeach()
endif()
