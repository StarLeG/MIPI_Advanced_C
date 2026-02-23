cmake_minimum_required(VERSION 3.22)

add_executable(AreaCalc main.c)

set_target_properties(AreaCalc PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
)