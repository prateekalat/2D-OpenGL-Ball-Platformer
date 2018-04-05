Prateek Alat - 20161108

Installation Instructions
=========================


Installation is done using CMake 3.1+ and GCC 4.8.1+ as C++11 has been used. Dependencies are:

1) GLFW
2) GLEW
3) GLM
4) GCC 4.8.1+

**Resolution** can be adjusted in the `main.h` file in `src` folder with `RES_X` and `RES_Y` macros.
Default is *1920x1080*. It's been tested in *1366x768* also.

**Fullscreen** can be configured with `FULLSCREEN` macro in `main.h`. Default is *enabled*.
Please note that score will not be visible in fullscreen mode as it is displayed in title bar.

Type `cmake .` and then `make` to generate an executable in the current directory.


--------------------------------------------------------------------------

Please read `HELP.md` for game instructions
