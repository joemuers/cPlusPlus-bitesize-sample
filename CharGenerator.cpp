/*
 *  CharGenerator.cpp
 *
 *  Created by joe muers.
 *  All rights reserved.
 *
 */

#include "CharGenerator.h"

#include <stdexcept>
#include <cmath>



CharGenerator::CharGenerator()
{}


CharGenerator::~CharGenerator()
{}


void CharGenerator::beginLine(int x1, int y1, int x2, int y2)
{
	// empty for base implementation
}



FixedCharGenerator::FixedCharGenerator(char letter /* = 'X' */) : letter_(letter)
{}
	

char FixedCharGenerator::getNextChar()
{
	return letter_;
}



void RandomCharGenerator::beginLine(int x1, int y1, int x2, int y2)
{
	static bool callOnce = true;
	
	if(callOnce)
	{
		srand((unsigned)time(0));
		callOnce = false;
	}
	
	// this gives us a random ascii character within the printable range- '!' (33) to '~' (126)
	letter_ = (rand() % 94) + '!';
}


char RandomCharGenerator::getNextChar()
{
	return letter_;
}



WordWrapGenerator::WordWrapGenerator(const std::string& word) : 
word_(word), currentPos_(word_.begin()), revCurrentPos_(word_.rbegin()), useReverse_(false)
{
	if(word_.empty())
	{
		throw std::invalid_argument("WordWrapGenerator - empty string passed to constructor");
	}
}

	
void WordWrapGenerator::beginLine(int x1, int y1, int x2, int y2)
{
	if(x1 > x2 || (x2 == x1 && y1 > y2))
	{
		useReverse_ = true;
		revCurrentPos_ = word_.rbegin();
	}
	else 
	{
		useReverse_ = false;
		currentPos_ = word_.begin();
	}
}


char WordWrapGenerator::getNextChar()
{
	if(!useReverse_)
	{
		char ret = *currentPos_;
	
		if(++currentPos_ == word_.end())
		{
			currentPos_ = word_.begin();
		}
	
		return ret;
	}
	else 
	{
		char ret = *revCurrentPos_;
		
		if(++revCurrentPos_ == word_.rend())
		{
			revCurrentPos_ = word_.rbegin();
		}
		
		return ret;
	}
}



void ArrowCharsGenerator::beginLine(int x1, int y1, int x2, int y2)
{	
	int dx = x2 - x1;
	int dy = y2 - y1;
	
	if(abs(dx) >= abs(dy))
	{
		letter_ = (dx == 0 ? POINT : (dx > 0 ? RIGHT : LEFT));
	}
	else 
	{
		letter_ = (dy > 0 ? UP : DOWN);
	}
}

	
char ArrowCharsGenerator::getNextChar()
{
	return letter_;
}