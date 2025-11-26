INCLUDE_DIR = include
SRCS_DIR = src
CXX  = g++

all: release

release: 
	mkdir -p out/
	$(CXX) --std=c++11 -O2 -I $(INCLUDE_DIR) src/main.cpp -o out/main

debug:
	$(CXX) --std=c++11 -O0 -g -DWAVE_DEBUG=1 -I $(INCLUDE_DIR) src/main.cpp -o main

clean:
	rm -rf out/
