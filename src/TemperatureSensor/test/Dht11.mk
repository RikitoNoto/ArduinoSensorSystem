CC 				= g++
CFLAGS 			= -Wall -g
INCLUDE			= ../../ArduinoSensorSystemCommonInclude/src -I ../../MemoryUtility/src -I../test/spy -I../../ArduinoSensorSystemCommonInclude/test/spy
LIBRARIES		= $$CPPUTEST_HOME/lib/libCppUTest.a
SRCDIR 			= ../src
OBJDIR			= temp
SPYDIR			= ../../ArduinoSensorSystemCommonInclude/test/spy
MEM_UTL_DIR		= ../../MemoryUtility/src

PROGRAM		 			= Dht11
BASE_OBJECTS			= Dht11.o
TESTOBJECTS				= Dht11Test.o
SPYOBJECTS				= ArduinoSpy.o $(OBJDIR)/TimerSpy.o
LIB_MEM_OBJECTS			= MemoryUtility.o

all_tests: $(OBJDIR)/$(PROGRAM)
	$(OBJDIR)/$(PROGRAM)

# Base class test
$(OBJDIR)/$(PROGRAM): $(OBJDIR)/$(BASE_OBJECTS) $(OBJDIR)/$(TESTOBJECTS) $(OBJDIR)/$(SPYOBJECTS) $(OBJDIR)/$(LIB_MEM_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBRARIES)

# compile test.
$(OBJDIR)/%.o:	%.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)

# compile source.
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)

# compile library of mem util.
$(OBJDIR)/%.o:	$(MEM_UTL_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)

# compile spy.
$(OBJDIR)/%.o:	$(SPYDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)

.PHONY: all
all: clean all_tests

.PHONY: clean
clean:
	rm -f $(OBJDIR)/$(BASE_OBJECTS) $(OBJDIR)/$(TESTOBJECTS) $(OBJDIR)/$(PROGRAM)
