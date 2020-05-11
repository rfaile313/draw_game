#/bin/bash

# combines clean, build, and run game
# into one script, leveraging logical
# operator && which runs only if 
# previous command succeded

# build constants
COMPILER="clang"
CFLAGS="-Wall -g -Wno-missing-braces"
SOURCE="../../../main.c"
LIBS="-lraylib"
OUTPUT="-o draw_game"
COMPLETE="**Build Succeded**"
RUNGAME="./draw_game"
BUILDDIR="Build"
BREAK="-----------------------------"



if [ $1 = "prod" ]; then
	mkdir $BUILDDIR && cd $BUILDDIR
	cp ../libraylib.a .
	clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a ../../../main.c -o draw_game
	mkdir draw_game.app 
	mkdir draw_game.app/Contents
	cp -a ../Resources draw_game.app/Contents
	cp ../info.plist draw_game.app/Contents
	mkdir draw_game.app/Contents/MacOS
	mv ./draw_game draw_game.app/Contents/MacOS
fi


if [ $1 = "clean" ]; then
	if [[ -d $BUILDDIR ]]
		then
			rm -rf $BUILDDIR && echo "Removed $BUILDDIR folder + files"
			echo "**Cleaning Done**"
		else
	echo "No $BUILDDIR folder to remove"
	fi
fi

if [ -z "$1"  ]; then
	
	if [[ -d $BUILDDIR ]]
		then
			rm -rf $BUILDDIR && echo "Removed $BUILDDIR folder + files"
			echo "**Cleaning Done**"
		else
	echo "No $BUILDDIR folder to remove"
	fi

	mkdir $BUILDDIR && cd $BUILDDIR
	
	echo $BREAK
	echo "**Building game with $COMPILER**"
	echo "Flags: $CFLAGS"
	echo "Source: $SOURCE"
	echo "Output: $OUTPUT"
	echo "Linked Libs: $LIBS"
	echo $BREAK

	$COMPILER $CFLAGS $SOURCE $OUTPUT $LIBS
	#check if previous command built
	if [ $? -eq 0 ]; then
		echo $COMPLETE
		$RUNGAME
	else
		echo "******Build Failed******"
	fi

fi

