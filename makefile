CFLAGS = -I/usr/local/include/
LFLAGS = -L/usr/local/lib/
libs = -lboost_regex

asciilines.exe : CoOrdReader.o CharGenerator.o AsciiGrid.o main.o
	g++ $(LFLAGS) $(libs) CoOrdReader.o CharGenerator.o AsciiGrid.o main.o -o asciilines.exe

CoOrdReader.o : CoOrdReader.cpp CoOrdReader.h
	g++ $(CFLAGS) -c CoOrdReader.cpp

CharGenerator.o : CharGenerator.cpp CharGenerator.h
	g++ -c CharGenerator.cpp

AsciiGrid.o : AsciiGrid.cpp AsciiGrid.h
	g++ -c AsciiGrid.cpp

main.o : main.cpp
	g++ -c main.cpp

clean : 
	rm *.o
