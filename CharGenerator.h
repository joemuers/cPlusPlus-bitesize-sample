/*
 *  CharGenerator.h
 *
 *  Created by joe muers.
 *  All rights reserved.
 *
 */

#ifndef CHARGENERATOR_H
#define CHARGENERATOR_H

#include <string>



/*
 * abstract base class - chooses which ascii character to use when drawing lines
 */
class CharGenerator
{
public:
	CharGenerator();
	virtual ~CharGenerator();
	
	virtual void beginLine(int x1, int y1, int x2, int y2);
	virtual char getNextChar() = 0;
};



/*
 * Fixed - used the same ascii character without change
 */
class FixedCharGenerator : public CharGenerator
{
	const char letter_;
	
public:
	FixedCharGenerator(char letter = 'X');
	
	virtual char getNextChar();
};



/*
 * Random - random ascii character for each line
 */
class RandomCharGenerator : public CharGenerator
{
	char letter_;	
	
public:
	virtual void beginLine(int x1, int y1, int x2, int y2);
	virtual char getNextChar();
};



/*
 * Word wrap - uses letters from a string for each line, wrapping round.
 */
class WordWrapGenerator : public CharGenerator
{
	const std::string word_;
	std::string::const_iterator currentPos_;
	std::string::const_reverse_iterator revCurrentPos_;
	bool useReverse_;
	
public:
	WordWrapGenerator(const std::string& word); // throws std::invalid_argument
	
	virtual void beginLine(int x1, int y1, int x2, int y2);
	virtual char getNextChar();
};



/*
 * Directional - uses 'arrow' ascii chars to indicate line direction
 */
class ArrowCharsGenerator : public CharGenerator
{
	enum Direction { UP = 'A', DOWN = 'V', LEFT = '<', RIGHT = '>', POINT = 'X' };
	char letter_;
	
public:
	virtual void beginLine(int x1, int y1, int x2, int y2);
	virtual char getNextChar();	
};
	

#endif