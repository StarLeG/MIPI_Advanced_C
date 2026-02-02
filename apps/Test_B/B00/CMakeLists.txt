cmake_minimum_required(VERSION 3.28.3)

add_executable(test_B00 main.c
        findMaxBlock.h
        findMaxBlock.c
)

set_target_properties(test_B00 PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
)