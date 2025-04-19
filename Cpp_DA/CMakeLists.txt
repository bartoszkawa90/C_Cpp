# # PYTHON BIND VERSION
cmake_minimum_required(VERSION 3.18)
project(cpp_da)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG        v2.13.0  # explicitly use version 2.13.0
)
FetchContent_MakeAvailable(pybind11)

pybind11_add_module(cpp_da main.cpp)

# Test version
# cmake_minimum_required(VERSION 3.18)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# project(cpp_da)

# find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# add_subdirectory(pybind11)

# add_executable(cpp_da test.cpp)

# # Link pybind11 headers and Python include dirs
# target_include_directories(cpp_da PRIVATE ${Python3_INCLUDE_DIRS})
# target_link_libraries(cpp_da PRIVATE pybind11::headers)
