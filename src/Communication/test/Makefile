CC 				= g++
CFLAGS 			= -Wall -g
INCLUDE			= ../../ArduinoSensorSystemCommonInclude/src
LIBRARIES		= $$CPPUTEST_HOME/lib/libCppUTest.a
SRCDIR 			= ../src
OBJDIR			= temp

BASE_PROGRAM 			= testBase
BASE_OBJECTS			= EthernetBase.o
BASE_TESTOBJECTS		= EthernetBaseTest.o

all_tests: $(OBJDIR)/$(BASE_PROGRAM)
	$(OBJDIR)/$(BASE_PROGRAM)

# Base class test
$(OBJDIR)/$(BASE_PROGRAM): $(OBJDIR)/$(BASE_OBJECTS) $(OBJDIR)/$(BASE_TESTOBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBRARIES)



$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)


$(OBJDIR)/%.o:	%.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)


.PHONY: all
all: clean $(BASE_PROGRAM)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/$(BASE_OBJECTS) $(OBJDIR)/$(BASE_TESTOBJECTS) $(OBJDIR)/$(BASE_PROGRAM)
