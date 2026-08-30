cmake_minimum_required(VERSION 3.10)
project(matr_pseudobasic CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(matr_pseudobasic src/matr_pseudobasic.cpp)

# The program reads "matr.txt" relative to the current working directory.
# Copy the sample input next to the built binary for convenience.
add_custom_command(TARGET matr_pseudobasic POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/examples/matr.txt
            $<TARGET_FILE_DIR:matr_pseudobasic>/matr.txt)
