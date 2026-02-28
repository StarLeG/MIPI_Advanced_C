cmake_minimum_required(VERSION 3.10)
project(AreaCalculation C)

set(CMAKE_C_STANDARD 99)

# Основная библиотека
add_library(arealib 
    src/functions.c
    src/root.c
    src/integral.c
    src/plotting.c
)

target_include_directories(arealib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Исполняемый файл
add_executable(area_calc src/main.c)
target_link_libraries(area_calc arealib)
target_link_libraries(area_calc arealib m)

# Создаем исполняемый файл для тестирования
add_executable(tests_area_calc test/test_main.c)
target_link_libraries(tests_area_calc arealib)
target_link_libraries(tests_area_calc arealib m)