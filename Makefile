#!/bin/sh
all: clean compile run

clean: 
	make -C library clean
	rm -rf *.class

compile: 
	make -C library compile
	javac -cp library/lib.jar Usage.java 

run: 
	java -cp .:library/lib.jar Usage
