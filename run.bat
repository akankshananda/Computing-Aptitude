@echo off
cd /d "%~dp0"
g++ server.cpp -o server.exe -lws2_32
server.exe