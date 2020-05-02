#!/bin/bash

# combines clean, build, and run game
# into one script, leveraging logical
# operator && which runs only if 
# previous command succeded

# cleaning constants
GAME="game"
WEIRDMACFILE="game.dSYM"
USELESSMACFILE=".DS_Store"
# build constants
COMPILER="clang"
CFLAGS="-Wall -g"
SOURCE="main.c"
LIBS="-lraylib"
OUTPUT="-o game"
COMPLETE="**Build Succeded**"
RUNGAME="./game"
# other
NEWLINE="\n"
BREAK="-----------------------------"

echo "**Cleaning**" && rm -f $GAME; rm -Rf $WEIRDMACFILE; rm -f $USELESSMACFILE \
  && echo "Removed  $GAME && $WEIRDMACFILE && $USELESSMACFILE" \ 
echo $BREAK
echo "**Cleaning Done**"
echo "**Building game with $COMPILER**"
echo "Flags: $CFLAGS"
echo "Source: $SOURCE"
echo "Output: $OUTPUT"
echo "Linked Libs: $LIBS"
echo $BREAK

$COMPILER $CFLAGS $SOURCE $OUTPUT $LIBS
if [ $? -eq 0 ]; then
    echo $COMPLETE
    $RUNGAME
else
    echo "******Build Failed******"
fi



