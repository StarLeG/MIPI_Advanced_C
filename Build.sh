#!/bin/bash

# Создание директории для сборки
mkdir -p build
cd build

# Запуск CMake и сборка
cmake ..
make