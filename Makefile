# program settings
## program name
PROGRAM = asr
## source directories
SOURCE_DIRECTORIES = ./src/ \
	./src/ga/ \
	./src/similarity/ \
	./src/utility/

# compiler settings
## c++ compiler
CXX = g++-10
## c++ compiler flags
CXXFLAGS = -g3 -Wall -std=c++20
## c++ preprocessor
CPP = g++-10 -E
## c++ preprocessor flags
CPPFLAGS = 

###########################################################
## all files
ALL_FILES = $(foreach DIR \
	, $(SOURCE_DIRECTORIES) \
	, $(wildcard $(DIR)*))

## object files
OBJECT_FILES = $(foreach DIR, \
	$(SOURCE_DIRECTORIES), \
	$(patsubst %.cpp, \
		%.o, \
		$(wildcard $(DIR)*.cpp)))

## header files
HEADER_FILES = $(foreach DIR, \
	$(SOURCE_DIRECTORIES), \
	$(wildcard $(DIR)*.hpp)))
	
## dependency files
DEPENDENCY_FILES = $(foreach DIR, \
	$(SOURCE_DIRECTORIES), \
	$(patsubst %.cpp, \
		%.d, \
		$(wildcard $(DIR)*.cpp)))

# all
.PHONY: all
all: $(PROGRAM)
	rm -rf $(DEPENDENCY_FILES)

# $(PROGRAM) recipe
$(PROGRAM): $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

# dependency file recipe
$(DEPENDENCY_FILES):
	echo -n $(dir $@) > $@
	$(CXX) -MM -c $(basename $@).cpp >> $@
	echo "\t$(CXX) $(CXXFLAGS) -c $(basename $@).cpp -o $(basename $@).o" >> $@

# clean
.PHONY: clean
clean:
	rm -rf $(PROGRAM) $(OBJECT_FILES) $(DEPENDENCY_FILES)

# include dependency files
-include $(DEPENDENCY_FILES)