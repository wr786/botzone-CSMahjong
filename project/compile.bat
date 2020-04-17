@echo off
g++ -std=c++17 main_local.cpp -o main
pause;
chcp 65001
.\main.exe
pause;