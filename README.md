# draw_game

MacOS:
    1. `./run.sh` cleans, builds, and runs if build successful
    2. `./cleanmac.sh` cleans files for git commits

Windows: 
    1. F1 Clean
    2. F2 Build
    3. F3 Run
    4. F4 Debug
    
Linux:
    1. `cd /compile/linux/`
    2. `cmake .`
    3. `make`

## More info on Windows

### 4coder bindings or run `run.bat [run, build, clean, debug]` in cmd

1. `run build` calls build.bat with -dv by default (debug build, verbose). See build.bat for more options
2. `run run` calls `builds-debug\windows-msvc\draw_game.exe` by default
3. `run debug` initializes vcvars all then runs the executable with `devenv`
4. `run clean` destroys the `builds`, `builds-debug`, and `temp` directories 
