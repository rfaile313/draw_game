#!/bin/bash
GAME="game"
WEIRDMACFILE="game.dSYM"

echo "**Cleaning**"

rm -f $GAME; rm -Rf $WEIRDMACFILE

echo "**Cleaned $GAME and $WEIRDMACFILE**" 
