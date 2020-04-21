@echo off
g++ -D_PREPROCESS_ONLY -D_BOTZONE_ONLINE -E .\main.cpp -o .\main.am2.cpp.tmp
echo #include^<bits/stdc++.h^> > .\main.am2.cpp
echo #include "MahjongGB/MahjongGB.h" >> .\main.am2.cpp
type .\main.am2.cpp.tmp >> .\main.am2.cpp
del .\main.am2.cpp.tmp
pause;