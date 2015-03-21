.PHONY: all syntax doxygen clean

all: syntax doxygen

syntax: 
	gcc -Wall -Wparentheses -c drv8301.c -fsyntax-only

doxygen:
	doxygen drv8301.doxyfile

clean:
	rm -rf html/
	rm -rf latex/
