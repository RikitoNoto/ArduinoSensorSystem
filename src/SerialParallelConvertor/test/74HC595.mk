CC 				= g++
CPPFLAGS 		= -Wall -g
INCLUDES 		= -I ../src -I spy -I ../../ArduinoSensorSystemCommonInclude/src -I ../../ArduinoSensorSystemCommonInclude/test/spy
LIBRARIES		= $$CPPUTEST_HOME/lib/libCppUTest.a
VPATH 			= spy ../src ../../ArduinoSensorSystemCommonInclude/test/spy .
vpath %.o temp
OBJDIR			= temp

#source files
SRCFILES		= $(foreach dir,$(VPATH),$(wildcard $(dir)/*.cpp))
#target object files.
OBJFILES		= $(foreach name,$(SRCFILES),$(addprefix $(OBJDIR)/,$(notdir $(patsubst %.cpp,%.o,$(name)))))

#======== write project info ========
PROGRAM			= 74HC595
EXPANDED_INCLUDES =

#====================================

all_tests: $(OBJDIR)/$(PROGRAM)
	$^

$(OBJDIR)/$(PROGRAM): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBRARIES)

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $< $(INCLUDES) $(EXPANDED_INCLUDES)


.PHONY: debug_print
debug_print:
	echo $(OBJFILES)

.PHONY: all
all: clean all_tests

.PHONY: clean
clean:
	rm -f -r $(OBJDIR)/*
