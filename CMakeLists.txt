cmake_minimum_required(VERSION 3.10)

# Projectnaam
project(test VERSION 1.0 LANGUAGES CXX)

# C++ standaard instellen
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files toevoegen
add_executable(test src/main.cpp)