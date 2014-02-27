/*
 *  CoOrdReader.h
 *
 *  Created by joe muers.
 *  All rights reserved.
 *
 */

#ifndef COORDREADER_H
#define COORDREADER_H

#include <istream>
#include <boost/regex.hpp>



/*
 * Takes a stream containing coordinate data and extracts the line coordinates
 */
class CoOrdReader
{

public:
	
	struct lineCoords
	{
		int x1_, y1_, x2_, y2_;
		
		lineCoords(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0) : x1_(x1), y1_(y1), x2_(x2), y2_(y2)
		{}
	};

	
	CoOrdReader(std::istream& inStream);
	
	// re-entrant call puts new data into output parameter with each call
	// returns true is all is good, false otherwise.
	// throws std::invalid_argument
	bool getNextLine(CoOrdReader::lineCoords& coords); 
	
	// equivalent to istream::good() function
	bool streamStillGood() const;
	
private:
	
	std::istream& inStream_;
	boost::regex regexStart;
	boost::regex regexEnd;
};


#endif