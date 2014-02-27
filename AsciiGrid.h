/*
 *  AsciiGrid.h
 *
 *  Created by joe muers.
 *  All rights reserved.
 *
 */

#ifndef ASCIIGRID_H
#define ASCIIGRID_H

#include "CharGenerator.h"



// contains data structure for holding ascii data
// & methods to modify & print
class AsciiGrid
{
	static const int DEFAULT_WIDTH = 20;
	static const int DEFAULT_HEIGHT = 10;
	
	CharGenerator& charGen_;
	const unsigned int width_;
	const unsigned int height_;
	char** grid_;
	
public:
	// constructor throws std::bad_alloc
	AsciiGrid(CharGenerator& charGen, unsigned int width = DEFAULT_WIDTH, unsigned int height = DEFAULT_HEIGHT);
	~AsciiGrid();
	
	// drawPoint & drawLine draw only to internal data structure
	// to get visible output, use the overloaded extraction operator
	inline void drawPoint(int x, int y, char ascii = 'X'); 
	void drawLine(int xStart, int yStart, int xEnd, int yEnd);  // throws std::invalid_argument
	
	friend std::ostream& operator<<(std::ostream& out, AsciiGrid& grid);
	
	
private:
	
	static inline void swap(int& a, int& b);

};

#endif 
