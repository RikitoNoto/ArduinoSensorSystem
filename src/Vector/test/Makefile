CC 				= g++
CFLAGS 			= -Wall
OBJECTS			= Point.o
PROGRAM       	= test
LIBRARIES		= $$CPPUTEST_HOME/lib/libCppUTest.a
SRCDIR 			= ../src
OBJDIR			= temp

all_tests: $(OBJDIR)/$(PROGRAM)
	$(OBJDIR)/$(PROGRAM)


$(OBJDIR)/$(PROGRAM): $(OBJDIR)/$(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBRARIES)


$(OBJDIR)/%.o:	%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: all
all: clean $(PROGRAM)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/$(OBJECTS) $(OBJDIR)/$(PROGRAM)

# g++ test/Point2.cpp -o test/temp.o $CPPUTEST_HOME/lib/libCppUTest.a
# test/temp/temp.o
# rm test/temp.o