cmake_minimum_required(VERSION 3.12)
project(withPython)

set(CMAKE_CXX_STANDARD 14)

set(Python_ADDITIONAL_VERSIONS 3.6)

find_package(PythonLibs 3 REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(withPython main.c)

target_link_libraries(withPython ${PYTHON_LIBRARIES})

