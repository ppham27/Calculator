include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(Calculator Calculator.cpp)

add_executable(calc main.cpp)
