cmake_minimum_required(VERSION 3.10)

# Projectnaam
project(test VERSION 1.0 LANGUAGES CXX)

# C++ standaard instellen
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Use AUTOMOC to process Q_OBJECT macros
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Source files
add_executable(test
	src/main.cpp
	src/calculator.cpp
	src/calculator.h
)

target_link_libraries(test PRIVATE Qt6::Widgets)