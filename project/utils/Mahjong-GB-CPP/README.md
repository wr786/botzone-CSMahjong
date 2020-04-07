Mahjong Fan Calculator CPP
=====

README:[English](https://github.com/ailab-pku/Chinese-Standard-Mahjong/blob/master/fan-calculator-usage/Mahjong-GB-CPP/README.md)|[中文](https://github.com/ailab-pku/Chinese-Standard-Mahjong/blob/master/fan-calculator-usage/Mahjong-GB-CPP/README-zh.md)

The usage is shown in test.cpp

***Please choose "G++ 7.2.0 with many lib" as compiler on Botzone.***

```cpp
#include "MahjongGB/MahjongGB.h"

// Init
void MahjongInit();  

// Fan calculator
vector<pair<int, string> > MahjongFanCalculator(
    vector<pair<string, pair<string, int> > > pack,
    vector<string> hand,
    string winTile,
    int flowerCount,
    bool isZIMO,
    bool isJUEZHANG,
    bool isGANG,
    bool isLAST,
    int menFeng,
    int quanFeng
);
```

- pack: The declared tiles. Each pair in the vector consists of a string ("PENG", "GANG", or "CHI") and another pair which contains the information of the declared tiles. Click [here](https://github.com/ailab-pku/Chinese-Standard-Mahjong/blob/master/fan-calculator-usage/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/README.md) for details.
- hand: The concealed tiles in hand. Each string is a tile.
- winTile: This tile could make Mahjong.
- flowerCount: The number of the Flower and Season tiles.
- isZIMO: Whether self-draw winning or not.
- isJUEZHANG: Whether the winning tile is the 4th one.
- isGANG: Whether the win is because of GANG. If the player wins by other's discard, it is Robbing the Kong. Otherwise, if the player wins by self-drawn, it is Out with Replacement Tile.
- isLast: Whether the winning tile is the last one in tile wall. If self-drawn, it is Last Tile Draw. Otherwise, it is Last Tile Claim.
- menFeng: Seat wind. The number 0, 1, 2, 3 represent East, South, West, and North respectively.
- quanFeng: Round Wind. The number 0, 1, 2, 3 represent East, South, West, and North respectively.
- return: This function returns a vector of pair. Each pair is a fan, with the int as the point and the string as the description.
