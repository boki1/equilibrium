#!/bin/sh

project_name="equilibrium"
out_dir=build/out

usage() {
	echo "Bad usage: ./build/$project_name [build|test|clean]"
}

make_build() {
	mkdir -p $out_dir
	conan install . -if $out_dir --build=missing
	cmake -S . -B $out_dir -G Ninja
	ninja -j $(nproc) -C $out_dir
}

make_test() {
	ctest --test-dir $out_dir
}

make_clean() {
	rm -rf $out_dir
}

main() {
	for arg in "$@"
	do
		case $arg in
		    "build") make_build;;
		    "test") make_test;;
		    "clean") make_clean;;
		    *) usage && exit;;
		esac
	done

}

main $@
