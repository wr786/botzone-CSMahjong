C:\mingw-w64\x86_64-8.1.0-win32-seh-rt_v6-rev0\mingw64\bin\g++ -D_PREPROCESS_ONLY -D_BOTZONE_ONLINE -E .\main.cpp -o .\main.am2.cpp.tmp
echo #include^<bits/stdc++.h^> > .\main.am2.cpp
echo #include "MahjongGB/MahjongGB.h" >> .\main.am2.cpp
type .\main.am2.cpp.tmp >> .\main.am2.cpp
del .\main.am2.cpp.tmp
pause