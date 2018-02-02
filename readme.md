# Java Mptcp binding 

Binding of the MPTCP socket library to java

That library is designed to work in a functionnal way. It consists on a list of static methods that take a socket as first parameter. 

*IMPORTANT ! This is an binding od an old version of mptcp and it's not maintained anymore ! Use it as an inspiration or a a base of work but the bindings are currently broken !*

## How to install

To install, just run the command: `sudo make compile`. If you want to test that the program works correctly, just run `sudo make run`. 

## Architecture of the directory 

The structure of the directory is the following. 

 * . contains a test that show how the library works
 * ./library contains the whole library (java and native C part) 
 * ./library/com/... contains only the java part of the library 

## Documentation 
Ongoing... (don't put too much hope in it)
Authors: Guillaume Demaude, Pierre Ortegat, Alexis Clarembeau

This repository is under the MIT license
