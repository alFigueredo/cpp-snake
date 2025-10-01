#!/bin/bash

BUILD_DIR='./build/'
RELEASE_DIR=$BUILD_DIR'release/'
DEBUG_DIR=$BUILD_DIR'debug/'
EXEC_FILE=$RELEASE_DIR'snake'

build() {
	command cmake --build "$1"
}

cmake() {
	command cmake -B $DEBUG_DIR -DCMAKE_BUILD_TYPE=debug
	command cmake -B $RELEASE_DIR
}

main() {
	case $1 in
	cmake)
		cmake
		;;
	build)
		build $RELEASE_DIR
		;;
	test)
		build $RELEASE_DIR
		command ctest --test-dir $RELEASE_DIR
		;;
	run)
		build $RELEASE_DIR
		command $EXEC_FILE
		;;
	debug)
		build $DEBUG_DIR
		;;
	clean)
		command make -C $RELEASE_DIR clean
		command make -C $DEBUG_DIR clean
		;;
	clean-all)
		command rm -rf $BUILD_DIR
		;;
	*)
		command echo "Invalid input!"
		exit 1
		;;
	esac
}

if [[ -z $1 ]]; then
	cmake
	exit 0
fi
for arg in "$@"; do
	main "$arg"
done
