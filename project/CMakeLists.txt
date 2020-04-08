cmake_minimum_required(VERSION 3.15)
project(project)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
#include_directories(utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm)
#include_directories(utils/Mahjong-GB-CPP/MahjongGB)

add_executable(project
#        src/cs_mahjong.cpp
#        src/cs_mahjong.h
        src/Mahjong.cpp
        src/Mahjong.h
        src/StateContainer.h
        #        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.cpp
#        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.h
#        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.cpp
#        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h
#        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/standard_tiles.h
#        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.cpp
#        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.h
#        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h
#        utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/unit_test.cpp
#        utils/Mahjong-GB-CPP/MahjongGB/MahjongGB.cpp
#        utils/Mahjong-GB-CPP/MahjongGB/MahjongGB.h
#        utils/Mahjong-GB-CPP/test.cpp
        )
