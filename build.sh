#!/usr/bin/env bash

handle_options() {
	if [ -z $* ]; then
		debug_compile
		exit 0
	fi

	while getopts "idrtch" opt; do
		case $opt in
			i) install_lib ;;
			d) debug_compile ;;
			r) release_compile ;;
			t) run_test ;;
			c) clean_build ;;
			h) help_message ;;
			*) unknown option ;;
		esac
	done
}

debug_compile() {
	mkdir -p build && cd build
	cmake "-DCMAKE_BUILD_TYPE=DEBUG" ".."
	make
}

release_compile() {
	mkdir -p build && cd build
	cmake "-DCMAKE_BUILD_TYPE=RELEASE" ".."
	make
}

install_lib() {
	if [ ! -d "./build" ]; then
		echo "build directory does not exists."
		exit 0
	fi

	cd build
	sudo make install
}	

run_test() {
	if [ ! -d "./build" ]; then
		echo "build directory does not exists."
		exit 0
	fi

	printf "[TEST] : #1 : testc_logc\n\n"
	./build/testc_logc
	test_result=$?

	if [ $test_result -ne 0 ]; then
		printf "\n[TEST] : #1 : result - test failed\n"
	else
		printf "\n[TEST] : #1 : result - test passed\n"
	fi
}

clean_build() {
	if [ ! -d "./build" ]; then
		echo "build directory does not exists."
		exit 0
	fi

	rm -rf ./build
}

help_message() {
	printf "build.sh options:\n"
	printf "\t-d - build debug version\n"
	printf "\t-r - build release version\n"
	printf "\t-i - install the library\n"
	printf "\t-c - clean the build directory(just delete)\n"
	printf "\t-t - run test, only after build\n"
	printf "\t-h - prints this help message\n"
}

handle_options "$@"

