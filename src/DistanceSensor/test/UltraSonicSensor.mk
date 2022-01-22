CC 				= g++
CFLAGS 			= -Wall -g
INCLUDE			= ../../ArduinoSensorSystemCommonInclude/src -I../test/spy -I../../MemoryUtility/src -I../../Vector/src
LIBRARIES		= $$CPPUTEST_HOME/lib/libCppUTest.a
SRCDIR 			= ../src
OBJDIR			= temp
SPYDIR			= spy
MEM_UTL_DIR		= ../../MemoryUtility/src

PROGRAM 				= testUltraSonic
OBJECTS					= UltraSonicSensor.o
TESTOBJECTS				= UltraSonicSensorTest.o
SPYOBJECTS				= ArduinoSpy.o $(OBJDIR)/TimerSpy.o
LIB_MEM_OBJECTS			= MemoryUtility.o

all_tests: $(OBJDIR)/$(PROGRAM)
	$(OBJDIR)/$(PROGRAM)

# Base class test
$(OBJDIR)/$(PROGRAM): $(OBJDIR)/$(OBJECTS) $(OBJDIR)/$(TESTOBJECTS) $(OBJDIR)/$(SPYOBJECTS) $(OBJDIR)/$(LIB_MEM_OBJECTS)
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
	rm -f $(OBJDIR)/$(OBJECTS) $(OBJDIR)/$(TESTOBJECTS) $(OBJDIR)/$(PROGRAM)
