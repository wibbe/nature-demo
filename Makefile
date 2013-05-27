all: compile

configure:
	(cd build/ && cmake28 -DCMAKE_BUILD_TYPE=Debug ..)

compile:
	make -C build/

run:
	(cd build/bin/linux && ./Nature)

debug:
	(cd build/bin/linux && gdb Nature)