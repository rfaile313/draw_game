# draw_game

MacOS:
    ./run.sh cleans, builds, and runs if build successful
    ./cleanmac.sh cleans files for git commits

Windows: 
    4coder - f1 clean f2 build f3 run f4 debug

## Debugging on Windows

### 4coder bindings or run `run.bat [run, build, clean, debug]` in cmd

1. `run build` calls build.bat with -dv by default (debug build, verbose). See build.bat for more options
2. `run run` calls `builds-debug\windows-msvc\draw_game.exe` by default
3. `run debug` initializes vcvars all then runs the executable with `devenv`
4. `run clean` destroys the `builds`, `builds-debug`, and `temp` directories 
