CXX=clang++-9
CXXFLAGS=-std=c++17 -stdlib=libc++ -lc++abi -lc++
objects = node.o main.o

%.o: %.cc %.h
	$(CXX) -c -o $@ $< $(CXXFLAGS)

main: $(objects)
	$(CXX) -o $@ $(objects) $(CXXFLAGS)