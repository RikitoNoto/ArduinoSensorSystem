BASE_TEST	= EthernetBase.mk
UDP_TEST	= UserDatagramProtocol.mk

all_tests:
	make -f $(BASE_TEST)
	make -f $(UDP_TEST)


.PHONY: all
all: clean all_tests

.PHONY: clean
clean:
	make clean -f $(BASE_TEST)
	make clean -f $(UDP_TEST)
