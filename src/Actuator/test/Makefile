STEPPER_TEST	= SteppingMotor.mk

all_tests:
	make -f $(STEPPER_TEST)


.PHONY: all
all: clean all_tests

.PHONY: clean
clean:
	make clean -f $(STEPPER_TEST)
