Code in this directory is for the Labs Programming task I was sent yesterday.

I have included a binary (asciilines.exe) which was compiled on an Intel MacBook, it uses one shared library (boost regex) which on my machine was located in /usr/local/lib/.
If you need to build for a different machine, or your boost libraries are in a different place, just change the include & library paths in the makefile to the boost header & shared libraries respectively and you should have no worries building it.

To run the program, you have the following options:
-f <filename>  to load in coordinates from a file (I've included a sample file you can use - coords.dat).
-s <string> to pass in a string with your coordinates data at the command line.
(if neither -f or -s are specified, then the app will ask you for coordinates at runtime via std::cin).
-c <char> to use single ascill character for all your lines.
-r to use random different ascii character for each line.
-w <string> to print a string across the length of each line (wraps around).
-a to use arrow characters in all the lines.


Hope you like it, any problems please let me know. 

Thanks.