cmake_minimum_required(VERSION 3.15)
project(project)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm)
include_directories(utils/MahjongGB)

add_executable(project
        src/Majang.cpp
        src/Majang.h
        src/RequestReader.cpp
        src/RequestReader.h
        src/ResponseOutput.cpp
        src/ResponseOutput.h
        src/ScoreCalculator.cpp
        src/ScoreCalculator.h
        src/StateContainer.cpp
        src/StateContainer.h
        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.cpp
        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.h
        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.cpp
        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h
        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/standard_tiles.h
        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.cpp
        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.h
        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h
        utils/MahjongGB/MahjongGB.cpp
        utils/MahjongGB/MahjongGB.h
        main_local.cpp)
