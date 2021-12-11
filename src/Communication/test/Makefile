CC 				= g++
CFLAGS 			= -Wall -g
INCLUDE			= ../../ArduinoSensorSystemCommonInclude/src -I ../../MemoryUtility/src
LIBRARIES		= $$CPPUTEST_HOME/lib/libCppUTest.a
SRCDIR 			= ../src
OBJDIR			= temp
MEM_UTL_DIR		= ../../MemoryUtility/src

BASE_PROGRAM 			= testBase
BASE_OBJECTS			= EthernetBase.o
BASE_TESTOBJECTS		= EthernetBaseTest.o
LIB_MEM_OBJECTS			= MemoryUtility.o

all_tests: $(OBJDIR)/$(BASE_PROGRAM)
	$(OBJDIR)/$(BASE_PROGRAM)

# Base class test
$(OBJDIR)/$(BASE_PROGRAM): $(OBJDIR)/$(BASE_OBJECTS) $(OBJDIR)/$(BASE_TESTOBJECTS) $(OBJDIR)/$(LIB_MEM_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBRARIES)

# compile test.
$(OBJDIR)/%.o:	%.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)

# compile source.
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)

# compili library of mem util.
$(OBJDIR)/%.o:	$(MEM_UTL_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)

.PHONY: all
all: clean $(BASE_PROGRAM)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/$(BASE_OBJECTS) $(OBJDIR)/$(BASE_TESTOBJECTS) $(OBJDIR)/$(BASE_PROGRAM)
