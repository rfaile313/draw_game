# Draw!

![game_screenshot](assets/screenshot.png)

## How to Play:

It's a standoff! Press Space when it's time to draw, but not before!

## MacOS:

1. `./run.sh` cleans, builds, and runs if build successful
2. `./cleanmac.sh` cleans files for git commits

## Windows:

(Everything runs through run.bat)

`run.bat` does everything with options:
1. `run` builds and runs
2. `run build` only builds
3. `run clean` cleans files
4. `run debug` will run a debugger once I set it up

(4coder bindings to run.bat)

1. F1 Clean
2. F2 Build
3. F3 Run
4. F4 Debug

## Linux:

1. `cd /compile/linux/`
2. `cmake .`
3. `make`

---

Old Windows info (MSVC)

1. `run build` calls build.bat with -dv by default (debug build, verbose). See build.bat for more options
2. `run run` calls `builds-debug\windows-msvc\draw_game.exe` by default
3. `run debug` initializes vcvars all then runs the executable with `devenv`
4. `run clean` destroys the `builds`, `builds-debug`, and `temp` directories 

---
