# botzone-CSMahjong
A bot of Chinese Standard Mahjong in botzone



`tree /f`：

```
│  README.md
│
├─material							// 用于存放参考资料
│      Botzone2020_Mahjong.pptx		// 官方PPT
│      Building a Computer Mahjong Player Based on Monte Carlo Simulation and Opponent Models.pdf
│      资料导航.md					 // 一些关于国标麻将及botzone的资料
│
└─project
    ├─src
    │      cs_mahjong.cpp
    │      cs_mahjong.h
    │      project.sln
    │      project.vcxproj
    │      project.vcxproj.filters
    │      project.vcxproj.user
    │
    └─utils								
        ├─ChineseOfficialMahjongHelper			// 官方所给的库（见wiki页），也是番数库的依赖库
        │  └─Classes
        │      └─mahjong-algorithm
        │              CHANGELOG
        │              fan_calculator.cpp
        │              fan_calculator.h
        │              LICENSE
        │              README-zh.md
        │              README.md
        │              shanten.cpp
        │              shanten.h
        │              standard_tiles.h
        │              stringify.cpp
        │              stringify.h
        │              tile.h
        │              unit_test.cpp
        │
        └─Mahjong-GB-CPP						// 官方所给的番数计算库
            │  README-zh.md
            │  README.md
            │  test.cpp
            │
            └─MahjongGB
                    MahjongGB.cpp
                    MahjongGB.h
```

