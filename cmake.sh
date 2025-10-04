#!/bin/bash

BUILD_DIR='./build/'
EXEC_FILE=$BUILD_DIR'snake'

build() {
	command cmake --build $BUILD_DIR
}

cmake() {
	command cmake -B $BUILD_DIR "$1"
}

main() {
	case $1 in
	cmake)
		cmake ""
		;;
	cmake-debug)
		cmake -DCMAKE_BUILD_TYPE=debug
		;;
	build)
		build
		;;
	test)
		build
		command ctest --test-dir $BUILD_DIR
		;;
	run)
		build
		command $EXEC_FILE
		;;
	clean)
		command make -C $BUILD_DIR clean
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
