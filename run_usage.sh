#!/bin/sh
rm -rf *.class
javac -cp library/lib.jar Usage.java 
java -cp .:library/lib.jar Usage
