# Make JAR library 

Now that we're able to include C code in java program, we just need to define java library to make a binding. 

In that directory, we will focus on writing and using a "plain java library". If you want to see how to build a java binding with C code inside, you should just have a look at the next directory. 

The goal of that library is just to translate some low level C calls to a java library. 

This repository will gather all the previously seen concepts, so we: 

 - put the library in a package
 - call C code from the library 
 - store the library into jar file
 - call some functions from the jar file in a "test class"
