#!/bin/bash
#macos only
#system_profiler SPSoftwareDataType
CFLAGS="-Wall -g"
SOURCE="main.c"
LIBS="-lraylib"
OUTPUT="-o game"

COMPLETE="**Build Complete**"

clang $CFLAGS $SOURCE $OUTPUT $LIBS

echo $COMPLETE
