#!/bin/bash
COMPILER="clang"
CFLAGS="-Wall -g"
SOURCE="main.c"
LIBS="-lraylib"
OUTPUT="-o game"
COMPLETE="**Build Complete**"

echo "**Building game with $COMPILER**"
echo "Flags: $CFLAGS"
echo "Source: $SOURCE"
echo "Output: $OUTPUT"
echo "Linked Libs: $LIBS"

$COMPILER $CFLAGS $SOURCE $OUTPUT $LIBS

echo $COMPLETE
