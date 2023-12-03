CXX := g++
CXXFLAGS := -std=c++11 -O3
LDFLAGS :=

# Directories
SRCDIR := sourcefiles
ALGODIR := Algorithms
PRUNEDIR := Prunes
COMPUTEDIR := Compute
OBJDIR := obj
BINDIR := bin


# Files
SRC := $(wildcard $(SRCDIR)/*.cpp) 
ALGOSRC := $(wildcard $(ALGODIR)/*.cpp)
PRUNESRC := $(wildcard $(PRUNEDIR)/*.cpp)
COMPUTESRC := $(wildcard $(COMPUTEDIR)/*.cpp)
MAIN := uc_main.cpp
UNCERTAIN_CLIQUE_SRC := uncertainclique.cpp
OBJ := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
ALGOOBJ := $(patsubst $(ALGODIR)/%.cpp,$(OBJDIR)/%.o,$(ALGOSRC))
PRUNEOBJ := $(patsubst $(PRUNEDIR)/%.cpp,$(OBJDIR)/%.o,$(PRUNESRC))
COMPUTEOBJ := $(patsubst $(COMPUTEDIR)/%.cpp,$(OBJDIR)/%.o,$(COMPUTESRC))
MAINOBJ := $(patsubst %.cpp,$(OBJDIR)/%.o,$(MAIN))
UNCERTAIN_CLIQUEOBJ := $(patsubst %.cpp,$(OBJDIR)/%.o,$(UNCERTAIN_CLIQUE_SRC))
EXECUTABLE := $(BINDIR)/uncertainclique

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ) $(ALGOOBJ) $(PRUNEOBJ) $(COMPUTEOBJ) $(MAINOBJ) $(UNCERTAIN_CLIQUEOBJ)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(ALGODIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(PRUNEDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(COMPUTEDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/uc_main.o: $(MAIN)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/uncertainclique.o: $(UNCERTAIN_CLIQUE_SRC)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
