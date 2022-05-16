CC 				= g++
CFLAGS 			= -Wall -g -D_DEBUG_
INCLUDE			= ../../ArduinoSensorSystemCommonInclude/src -I ../../MemoryUtility/src -I../test/spy
LIBRARIES		= $$CPPUTEST_HOME/lib/libCppUTest.a
SRCDIR 			= ../src
OBJDIR			= temp
MEM_UTL_DIR		= ../../MemoryUtility/src

PROGRAM		 			= schedulertest
BASE_OBJECTS			= Scheduler.o
TESTOBJECTS				= SchedulerTest.o
LIB_MEM_OBJECTS			= MemoryUtility.o

all_tests: $(OBJDIR)/$(PROGRAM)
	$(OBJDIR)/$(PROGRAM)

# Base class test
$(OBJDIR)/$(PROGRAM): $(OBJDIR)/$(BASE_OBJECTS) $(OBJDIR)/$(TESTOBJECTS) $(OBJDIR)/$(LIB_MEM_OBJECTS)
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

.PHONY: all
all: clean all_tests

.PHONY: clean
clean:
	rm -f $(OBJDIR)/$(BASE_OBJECTS) $(OBJDIR)/$(TESTOBJECTS) $(OBJDIR)/$(PROGRAM)
