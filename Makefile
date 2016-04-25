CONFIG   =  Config.sh
PYTHON   =  /usr/bin/python
CFLAGS   =
CC       = g++
INCL	 = include/Node.h include/Graph.h include/Compile_Time_Options.h include/Proto.h
SRC 	 = src/main.cpp src/Node.cpp src/Init.cpp src/Graph.cpp src/Stats.cpp src/Finalize.cpp src/Distances.cpp\
	src/Potentials.cpp

make:
	python make_macros.py
	$(CC) $(CFLAGS) $(SRC) -std=c++11 -Wall -O3 -lm -fopenmp -o bin/sw_network

clean:
	rm *~ src/*.o src/*~ include/*.o include/*~ bin/* \#* src/\#* include/\#* bin/\#* \
	python/*~ python/\#* OUTPUTS/*~ OUTPUTS/\#* OUTPUTS/*
