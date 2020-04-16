cmake_minimum_required(VERSION 3.15)
project(project)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(project
#        src/cs_mahjong.cpp
#        src/cs_mahjong.h
        src/Mahjong.cpp
        src/Mahjong.h
        src/StateContainer.h
        src/StateContainer.cpp
        src/RequestReader.h
        src/RequestReader.cpp
        src/ScoreCalculator.cpp
        src/ScoreCalculator.h
        src/ResponseOutput.cpp
        src/ResponseOutput.h
        src/main.cpp
        )
