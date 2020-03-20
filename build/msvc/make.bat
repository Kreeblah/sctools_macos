@echo off
if "%1" == "clean" devenv sctools.sln /clean Release
if "%1" != "clean" devenv sctools.sln /build Release
