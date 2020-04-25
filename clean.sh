#!/bin/bash
GAME="game"
WEIRDMACFILE="game.dSYM"
USELESSMACFILE=".DS_Store"

echo "**Cleaning**"

rm -f $GAME; rm -Rf $WEIRDMACFILE; rm -f $USELESSMACFILE 

echo "**Removed  $GAME && $WEIRDMACFILE && $USELESSMACFILE**" 
