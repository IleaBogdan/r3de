@echo off

cp -r shaders bin
gcc src\*.c ^
    -o .\bin\cube.exe ^
    -lglfw3 -lopengl32 -lgdi32 ^
    -I .\include ^
    -I .\include\myh
