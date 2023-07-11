# CPP Ray Tracing (v0.1)

The following will describe the procedures to be able to construct, compile and build project with edited sources scripts on Windows.

## Dependencies

### MinGW-W64 GCC-8.1.0 : x86_64-posix-seh

*Download link : https://sourceforge.net/projects/mingw-w64/files/*

Reference it to `Path` environment variable of system as following :  
C:\...\mingw64\bin

### CMake

*Download link : https://cmake.org/download/*

Reference it to `Path` environment variable of system as following :  
C:\...\CMake\bin

### OpenCV – 3.4.1X

*Download link : https://opencv.org/releases/*

Reference it to `Path` environment variable of system as following :  
C:\...\opencv\build\x64\mingw\bin  
C:\...\opencv\build\x64\mingw\lib

### Special mingw builder for OpenCV

Add mingw folder of the following link to C:\...\opencv\build\x64\mingw\build\x64 (next to vc14 and vc15 builders) :

*https://drive.google.com/file/d/1SflymUxuZESJE0G_T8ZVABC3wNwt1V-j/view*


## Installation check

You may need to reboot your computer after CMake installation to make it work.  
```
g++ --version
cmake --version
```

## Terminal commands

The commands below must be executed in the project's `sources` folder.  
- Construct project  
```
cmake . -G "MinGW Makefiles"
```

- Build (compile)  
```
mingw32-make.exe
```

- Execute  
```
.\Lancer_de_rayon.exe
```
*Note : You cannot construct project structure over a different CMakeCache.txt, remove it first*
