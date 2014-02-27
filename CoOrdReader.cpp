/*
 *  CoOrdReader.cpp
 *
 *  Created by joe muers.
 *  All rights reserved.
 *
 */

#include "CoOrdReader.h"



CoOrdReader::CoOrdReader(std::istream& inStream) : 
inStream_(inStream), 
// regular expressions for matching start and end coordinates of a line
regexStart("\\s*,{0,1}\\s*\\(" /**/ "(-{0,1}\\d+)" /**/ "\\s*,\\s*" /**/ "(-{0,1}\\d+)"),
regexEnd("\\s*-\\s*\\(" /**/ "(-{0,1}\\d+)" /**/ "\\s*,\\s*" /**/ "(-{0,1}\\d+)")
{}


bool CoOrdReader::getNextLine(CoOrdReader::lineCoords& coords)
{
	if(inStream_.good())
	{
		std::string startStr, endStr;
		boost::smatch matchStart, matchEnd;
		
		
		std::getline(inStream_, startStr, ')');		// extract co-ordinate pairs from stream
		std::getline(inStream_, endStr, ')');
		
		if(boost::regex_match(startStr, matchStart, regexStart) &&	// verify integrity of coordinates
		   boost::regex_match(endStr, matchEnd, regexEnd))			// and put into output variable if all is good
		{			
			coords.x1_ = atoi(std::string(matchStart[1].first, matchStart[1].second).c_str());
			coords.y1_ = atoi(std::string(matchStart[2].first, matchStart[2].second).c_str());
			
			coords.x2_ = atoi(std::string(matchEnd[1].first, matchEnd[1].second).c_str());
			coords.y2_ = atoi(std::string(matchEnd[2].first, matchEnd[2].second).c_str());
			
			
			std::getline(inStream_, startStr, ',');		// advance to next pair, or skip whitespace at end of stream...
			return true;
		}
		else
		{
			// if we're here then something is wrong with the input data - try to find start of next co-ord, & inform user.
			bool foundComma = false;
			char temp;
			
			while(inStream_.good())
			{
				if((temp = inStream_.get()) == ',')
				{
					foundComma = true;
				}
				else if(temp == '(' && foundComma)
				{
					inStream_.putback(temp);
					break;
				}
				else if(isalnum(temp))
				{
					foundComma = false;
				}
			}
					
			throw std::invalid_argument(std::string("CoOrdReader::getNextLine - invalid coordinates: ") + startStr + ')' + endStr + ')');
		}
	}
	
	return false;
}


bool CoOrdReader::streamStillGood() const
{
	return inStream_.good();
}
