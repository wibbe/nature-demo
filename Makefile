all: compile

configure:
	(cd build/ && cmake28 -DCMAKE_BUILD_TYPE=Debug ..)

compile:
	make -C build/

run:
	(cd bin/linux && ./Nature)

debug:
	(cd bin/linux && gdb Nature)