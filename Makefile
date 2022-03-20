SRCDIR := src/
BLDDIR := build/
TESTDIR := tests/
SRCS := main.cpp liesDetector/liesDetector.cpp set/set.cpp int/int.cpp
SOURCES := $(SRCS:%=$(SRCDIR)%)
BLD := lies-detector.exe
DATA := statements.txt
HEADERS := liesDetector/liesDetector.hpp set/set.hpp int/int.hpp
HEADERS_IN_DIR := $(HEADERS:%=$(SRCDIR)%)
CC := g++

build: $(SOURCES) $(HEADERS_IN_DIR)
	$(CC) $(SOURCES) -o $(BLDDIR)$(BLD)

debug: $(SOURCES) $(HEADERS_IN_DIR)
	$(CC) $(SOURCES) -o $(BLDDIR)$(BLD) -D DEBUG

run:
	cd $(BLDDIR) && $(BLD) $(DATA)

tests: $(SRCDIR)tests/setTest.cpp
	$(CC) $(SRCDIR)tests/setTest.cpp $(SRCDIR)set/set.cpp $(SRCDIR)int/int.cpp -o $(BLDDIR)$(TESTDIR)setTest.exe

run_tests:
	cd $(BLDDIR)$(TESTDIR) && setTest.exe