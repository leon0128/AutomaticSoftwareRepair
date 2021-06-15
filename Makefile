# software settings
## all program name
PROGRAMS           = asr
## source direcory
SOURCE_DIRECTORIES = ./src/ \
	./src/ga/

# compiler settings
## recommending CXX (cpp compiler)
RECOMMENDING_CXX  = g++-10
# preprocessor flags
CPPFLAGS         +=
# compiler flags
CXXFLAGS         += -std=c++17 -g3 -w

# other settings
## c++ source suffix
CXX_SOURCE_SUFFIX = .cpp
## c++ header suffix
CXX_HEADER_SUFFIX = .hpp
## c++ object suffix
CXX_OBJECT_SUFFIX = .o
## objects name
OBJECTS = \
	$(foreach DIR,\
		$(SOURCE_DIRECTORIES),\
		$(patsubst %$(CXX_SOURCE_SUFFIX),\
			%$(CXX_OBJECT_SUFFIX),\
			$(wildcard $(DIR)*$(CXX_SOURCE_SUFFIX))))
## headers name
HEADERS = \
	$(foreach DIR,\
		$(SOURCE_DIRECTORIES),\
		$(wildcard $(DIR)*$(CXX_HEADER_SUFFIX)))

# set CXX (c++ compiler)
ifneq ($(strip $(shell which $(RECOMMENDING_CXX))),)
CXX = $(RECOMMENDING_CXX)
else ifneq ($(strip $(shell which g++-11)),)
CXX = g++-11
else ifneq ($(strip $(shell which g++-10)),)
CXX = g++-10
else ifneq ($(strip $(shell which g++)),)
CXX = g++
endif
ifneq ($(CXX), $(RECOMMENDING_CXX))
$(warning Recommended c++ compiler is not found, so $(CXX) is used.)
endif

# make all
.PHONY: all
all: $(PROGRAMS)

# make $(PROGRAMS)
$(PROGRAMS): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ 

# make object
%$(CXX_OBJECT_SUFFIX): %$(CXX_SOURCE_SUFFIX) $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean
.PHONY: clean
clean:
	rm -rf $(PROGRAMS) $(OBJECTS)