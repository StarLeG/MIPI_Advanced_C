cmake_minimum_required(VERSION 3.22)

add_executable(test_C02 main.c)

set_target_properties(test_C02 PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
)