cmake_minimum_required(VERSION 3.20)
project(Lab4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Enable AddressSanitizer and UBSan" OFF)
option(BUILD_EXPERIMENTS "Build separate diagnostic examples" OFF)

add_library(lab4_options INTERFACE)
target_compile_options(lab4_options INTERFACE -Wall -Wextra -Wpedantic)
if(ENABLE_SANITIZERS)
    target_compile_options(lab4_options INTERFACE
        -g -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(lab4_options INTERFACE -fsanitize=address,undefined)
endif()

add_library(restaurant_menu src/ingredient_list.cpp src/dish.cpp)
target_include_directories(restaurant_menu PUBLIC src)
target_link_libraries(restaurant_menu PUBLIC lab4_options)

add_executable(Lab4 src/main.cpp)
target_link_libraries(Lab4 PRIVATE restaurant_menu)

if(BUILD_EXPERIMENTS)
    add_executable(vector_counts experiments/vector_counts.cpp)
    target_link_libraries(vector_counts PRIVATE restaurant_menu)

    add_executable(vector_counts_may_throw
        experiments/vector_counts.cpp src/ingredient_list.cpp)
    target_include_directories(vector_counts_may_throw PRIVATE src)
    target_compile_definitions(vector_counts_may_throw PRIVATE LAB4_MOVE_MAY_THROW)
    target_link_libraries(vector_counts_may_throw PRIVATE lab4_options)

    add_executable(shallow_copy experiments/shallow_copy.cpp)
    target_include_directories(shallow_copy PRIVATE src)
    target_link_libraries(shallow_copy PRIVATE lab4_options)

    add_executable(no_destructor experiments/shallow_copy.cpp)
    target_include_directories(no_destructor PRIVATE src)
    target_compile_definitions(no_destructor PRIVATE LAB4_NO_DESTRUCTOR)
    target_link_libraries(no_destructor PRIVATE lab4_options)
endif()

include(CTest)
if(BUILD_TESTING)
    add_executable(ingredient_list_test tests/ingredient_list_test.cpp)
    target_include_directories(ingredient_list_test SYSTEM PRIVATE third_party)
    target_link_libraries(ingredient_list_test PRIVATE restaurant_menu)
    add_test(NAME ingredient_list COMMAND ingredient_list_test)
endif()
