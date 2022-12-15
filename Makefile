all:
	g++-11 -std=c++20 -g -fopenmp data.cpp entrypoint.cpp -o energy

