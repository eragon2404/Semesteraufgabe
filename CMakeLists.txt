cmake_minimum_required(VERSION 3.15)
project(Semesteraufgabe C)

set(CMAKE_C_STANDARD 90)

add_executable(Semesteraufgabe main.c "glorifiedifstatements(ai).c" "glorifiedifstatements(ai).h" logic.c logic.h console.c console.h)