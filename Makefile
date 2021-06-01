CXX = g++-10
CXXFLAGS = -std=c++17 -w -g3
PROGRAM = asr
DIR = src
OBJS = $(patsubst %.cpp, %.o, $(wildcard $(DIR)/*.cpp)) $(patsubst %.cpp, %.o, $(wildcard $(DIR)/*/*.cpp))

$(PROGRAM): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(PROGRAM)

clean:
	rm -f $(DIR)/*.o $(DIR)/*/*.o $(PROGRAM)
