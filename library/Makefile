all: compile 

## Actualising it for java 1.8
libname = "mptcp-api"
jdkpath = "/usr/java/jdk1.8.0_101"
jdkpath = "/usr/lib/jvm/java-7-openjdk-amd64"

cheader = "header.h"


compile: 
	# make classes from java files
	javac com/mptcp/*.java

	# make c header from java files 
	$(jdkpath)/bin/javah -o $(cheader) com.mptcp.Mptcp
	
	# make .o file from c file
	gcc -fpic \
	-I $(jdkpath)/include/ \
	-I $(jdkpath)/include/linux/ \
	-c code.c -o s1.o
	gcc -fpic \
	-I $(jdkpath)/include/ \
	-I $(jdkpath)/include/linux/ \
	-c getsublist.c -o s2.o
	gcc -fpic \
	-I $(jdkpath)/include/ \
	-I $(jdkpath)/include/linux/ \
	-c getsubtuple.c -o s3.o
	
	# make .so file from o file
	gcc -shared -o lib$(libname).so *.o

	# place .so file in native directory
	mkdir -p native
	cp lib$(libname).so native/lib$(libname).so

	# make jar archive
	$(jdkpath)/bin/jar cf lib.jar native/* com/mptcp/*.class

test: 
	javac -cp lib.jar Usage.java 
	java -cp .:lib.jar Usage

clean: 
	rm -f *.o com/mptcp/*.class
	rm -f *.so
	rm -f *.jar
	rm -f *.class
	rm -rf native
