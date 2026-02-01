cmake_minimum_required(VERSION 3.28.3)

add_executable(test_A04 main.c)

set_target_properties(test_A04 PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
)