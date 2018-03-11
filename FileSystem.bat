@echo off
title Wallpaper Sync
md Wallpaper 2>nul
echo A| xcopy *.jpg Wallpaper 2>nul >nul
del *.jpg 2>nul >nul
echo Please wait..
robocopy "D:\Batch Downloader\[C++] LoL-SL-Downloader\Wallpaper" "C:\Users\frede\Pictures\Wallpaper\League of Legends" /mir >nul
echo Done..
pause >nul
