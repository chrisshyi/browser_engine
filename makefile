CXX=clang++-9
CXXFLAGS=-std=c++17 -stdlib=libc++ -lc++abi -lc++
objects = build/node.o build/main.o

build/%.o: src/%.cc src/%.h
	$(CXX) -c -o $@ $< $(CXXFLAGS)

.PHONY: main
main: $(objects)
	$(CXX) -o $@ $(objects) $(CXXFLAGS)