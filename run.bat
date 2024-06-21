@echo off
REM Batch script to compile and link C++ source files on Windows

REM Set compiler and flags
set CXX=g++
set CXXFLAGS=-std=c++17 -Wall -I.

REM List of source files
set SOURCES=BinarySearchTree.cpp Book.cpp bookdatabase.cpp LibrarySystem.cpp main.cpp user_system.cpp

REM List of object files
set OBJECTS=BinarySearchTree.obj Book.obj bookdatabase.obj LibrarySystem.obj main.obj user_system.obj

REM Name of the final executable
set TARGET=my_program.exe

REM Compile source files into object files
echo Compiling source files...
for %%f in (%SOURCES%) do (
    echo Compiling %%f
    %CXX% %CXXFLAGS% -c %%f -o %%~nf.obj
    if errorlevel 1 (
        echo Failed to compile %%f
        exit /b 1
    )
)

REM Verify that object files were created
echo Verifying object files...
for %%f in (%OBJECTS%) do (
    if not exist %%f (
        echo Error: %%f not created.
        exit /b 1
    )
)

REM Link object files to create the final executable
echo Linking object files...
%CXX% %CXXFLAGS% -o %TARGET% %OBJECTS%
if errorlevel 1 (
    echo Failed to link object files
    exit /b 1
)

echo Build complete. To run the program, type: %TARGET%
goto :eof

REM Clean rule to remove generated files
:clean
if exist %TARGET% (
    del %TARGET%
)
for %%f in (%OBJECTS%) do (
    if exist %%f (
        del %%f
    )
)
goto :eof

REM Phony targets
if "%1"=="clean" (
    call :clean
)
