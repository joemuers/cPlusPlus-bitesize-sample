/*
 *  main.cpp
 *
 *  Created by joe muers.
 *  All rights reserved.
 *
 */

#include "CoOrdReader.h"
#include "CharGenerator.h"
#include "AsciiGrid.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <stdexcept>



void usage(const char* taskName);


int run(int argc, char* const argv[]);


void drawLines(std::istream& inStream, CharGenerator& generator);


// ENTRY POINT
int main(int argc, char* const argv[])
{
	try 
	{
		return run(argc, argv);
	}
	catch(const std::bad_alloc& e)
	{
		std::cerr << "main: caught out of memory exception\n";
	}
	catch(const std::invalid_argument& e)
	{
		usage(argv[0]);
	}
	catch( ... )
	{
		std::cerr << "main: caught unknown exception\n";
	}
	
	return 1;
}


int run (int argc, char * const argv[]) 
{
	int option = -1;
	bool parseFile = false;
	bool parseString = false;

	std::string argString;
	std::auto_ptr<CharGenerator> charGen;
	
    while ((option = getopt (argc, argv, "f:s:c:rw:a")) != -1)
    {
		switch (option)
		{
			case 'f':	// option = get coordinates from a file
			{
				if(!parseString)
				{
					argString.assign(optarg);
					parseFile = true;
				}
				else 
				{
					usage(argv[0]);
					return 1;
				}

			}
			break;
			case 's':	// option = get coordinates from command-line string
			{
				if(!parseFile)
				{
					argString.assign(optarg);
					parseString = true;
				}
				else 
				{
					usage(argv[0]);
					return 1;
				}
			}
			break;
			case 'c':	// option = use fixed ascii char for drawing
			{
				if(charGen.get() == 0)
				{
					charGen.reset(new FixedCharGenerator(optarg[0]));
				}
				else 
				{
					usage(argv[0]);
					return 1;
				}
			}
			break;
			case 'r':	// option = use random ascii chars for drawing
			{
				if(charGen.get() == 0)
				{
					charGen.reset(new RandomCharGenerator());
				}
				else 
				{
					usage(argv[0]);
					return 1;
				}
			}
			break;
			case 'w':	// option = use word wrap for drawing
			{
				if(charGen.get() == 0)
				{
					charGen.reset(new WordWrapGenerator(optarg));
				}
				else 
				{
					usage(argv[0]);
					return 1;
				}
			}
			break;
			case 'a':	// option = use arrows for drawing
			{
				if(charGen.get() == 0)
				{
					charGen.reset(new ArrowCharsGenerator());
				}
				else 
				{
					usage(argv[0]);
					return 1;
				}
			}
			break;
			default:
			{
				usage(argv[0]);
				return 1;
			}
			break;
		}
    }

	
	if(charGen.get() == 0)  // 'default' char generator is user has not specified a behaviour
	{
		charGen.reset(new FixedCharGenerator());
	}
	
	
	if(parseFile)
	{
		std::ifstream in(argString.c_str());
		
		if(in.is_open())
		{
			drawLines(in, *charGen);
		}
		else 
		{
			throw std::invalid_argument(std::string("Cannot open file: ") + argString);
		}
	}
	else if(parseString)
	{
		std::istringstream in(argString);
		drawLines(in, *charGen);
	}
	else 
	{
		std::cout << "Please input coordinates...\n";
		std::getline(std::cin, argString);
		std::stringstream in(argString);
		
		drawLines(in, *charGen);
	}
//	else   // if redirecting input at command-line... not really needed for now
//	{
//		drawLines(std::cin, *charGen);
//	}


	
    return 0;
}


void drawLines(std::istream& inStream, CharGenerator& generator)
{
	AsciiGrid grid(generator);
	CoOrdReader reader(inStream);
	CoOrdReader::lineCoords coordsHolder;

	
	while(reader.streamStillGood())
	{
		try 
		{
			if(reader.getNextLine(coordsHolder))
			{
				grid.drawLine(coordsHolder.x1_, coordsHolder.y1_, coordsHolder.x2_, coordsHolder.y2_);
			}
		}
		catch(const std::invalid_argument& e)
		{
			std::cerr << e.what() << '\n';
		}
	}

	std::cout << grid;
}


void usage(const char* taskName)
{
	std::cerr << taskName << " - usage: [-f <filename> | -s <string>] [-c <char> | -r | -w <string> | -d]\n\t"
	<< "f : read coordinates from file.\n\ts : read coordinates from command-line string\n\t"
	<< "c : use fixed ascii char\n\tr : use random ascii chars\n\tw : word wrap chars\n\ta : use arrow chars\n\n";
}
