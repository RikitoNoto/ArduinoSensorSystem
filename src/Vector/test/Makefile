CC 				= g++
CFLAGS 			= -Wall
OBJECTS			= temp/Point.o
PROGRAM       	= myprogram
LIBRARIES		= `$CPPUTEST_HOME/lib/libCppUTest.a`

.PHONY: all
all: all_tests


all_tests: $(PROGRAM)


$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $^ $(LIBRARIES)


.cpp.o:
	$(CC) -c -o $@ $<


# .PHONY: clean

# clean:
# 	rm -f $(PGNAME) $(OBJS)

# g++ test/Point2.cpp -o test/temp.o $CPPUTEST_HOME/lib/libCppUTest.a
# test/temp/temp.o
# rm test/temp.o