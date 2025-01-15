cmake_minimum_required(VERSION 3.30)
project(LodickyUdSP C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})
add_definitions(${GTK_CFLAGS_OTHER})

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")


add_executable(LodickyUdSP main.c
        TypPolickaEnum.h
        HraciaPlocha.h
        Policko.h
        Policko.c
        HraciaPlocha.c
        Game_Logic.h
        Game_Logic.c
        GUI.h
        GUI.c
        Hrac.h
        Hrac.c)

target_link_libraries(LodickyUdSP ${GTK_LIBRARIES})
