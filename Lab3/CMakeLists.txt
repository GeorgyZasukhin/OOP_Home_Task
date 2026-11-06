cmake_minimum_required(VERSION 3.20)
project(Lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Enable AddressSanitizer and UBSan" OFF)

add_library(seed_fund
    src/seed_variety.cpp src/agronomist.cpp src/lifetime_log.cpp)
target_include_directories(seed_fund PUBLIC src)
target_compile_options(seed_fund PUBLIC -Wall -Wextra -Wpedantic -g)
if(ENABLE_SANITIZERS)
    target_compile_options(seed_fund PUBLIC
        -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(seed_fund PUBLIC -fsanitize=address,undefined)
endif()

add_executable(Lab3 src/main.cpp)
target_link_libraries(Lab3 PRIVATE seed_fund)

add_executable(lifetime_demo experiments/lifetime_demo.cpp)
target_link_libraries(lifetime_demo PRIVATE seed_fund)

include(CTest)
if(BUILD_TESTING)
    add_executable(constructor_test tests/constructor_test.cpp)
    target_include_directories(constructor_test SYSTEM PRIVATE third_party)
    target_link_libraries(constructor_test PRIVATE seed_fund)
    foreach(case RANGE 1 16)
        add_test(NAME constructors_${case}
            COMMAND constructor_test --test-case=case_${case})
    endforeach()
endif()
