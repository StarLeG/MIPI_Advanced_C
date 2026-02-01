cmake_minimum_required(VERSION 3.28.3)

project(MIPI_Advanced_C VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

#Test A applications
add_subdirectory(apps/Test_A/A00)
add_subdirectory(apps/Test_A/A01)
add_subdirectory(apps/Test_A/A02)
add_subdirectory(apps/Test_A/A03)
add_subdirectory(apps/Test_A/A04)
add_subdirectory(apps/Test_A/A05)
add_subdirectory(apps/Test_A/A06)
add_subdirectory(apps/Test_A/A07)
add_subdirectory(apps/Test_A/A08)
add_subdirectory(apps/Test_A/A09)
add_subdirectory(apps/Test_A/A10)

#Test B applications
add_subdirectory(apps/Test_B/B00)
#add_subdirectory(apps/Test_B/B01)       

#Snake game application
add_subdirectory(apps/snake)