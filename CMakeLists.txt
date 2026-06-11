cmake_minimum_required(VERSION 4.1)
project(Demineur C)

set(CMAKE_C_STANDARD 99)

add_executable(Demineur main.c
        demineur.h
        demineur.c
        initialisation.c
        initialisation.h
        sauvegarde.c
        sauvegarde.h)
