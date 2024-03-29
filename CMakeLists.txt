cmake_minimum_required(VERSION 3.27)
project(HashTable C)

set(CMAKE_C_STANDARD 11)

add_executable(HashTable
        app/main.c
        src/hash_table.c
)
