cmake_minimum_required(VERSION 3.28.3)

# Создание исполняемого файла
add_executable(snake
    src/main.c
)

# Подключение заголовочных файлов
target_include_directories(snake PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# Настройка свойств C
set_target_properties(snake PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
)

# Поиск и подключение ncurses
find_package(Curses REQUIRED)
target_include_directories(snake PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(snake PRIVATE ${CURSES_LIBRARIES})