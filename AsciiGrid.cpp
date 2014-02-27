/*
 *  AsciiGrid.cpp
 *
 *  Created by joe muers.
 *  All rights reserved.
 *
 */

#include "AsciiGrid.h"

#include <iostream>
#include <stdexcept>



AsciiGrid::AsciiGrid(CharGenerator& charGen, unsigned int width /* = DEFAULT_WIDTH */, unsigned int height /* = DEFAULT_HEIGHT */) : 
	charGen_(charGen), width_(width), height_(height)
{

	
	int assigned = 0;

	try 
	{	
		grid_ = new char*[width];
	
		while(assigned < width)
		{
			grid_[assigned++] = new char[height];
		
			for(int y = 0; y < height; ++y)
			{
				grid_[assigned-1][y] = ' ';
			}
		}
	}
	catch(const std::bad_alloc& e)
	{ // clean up resources if allocation of 2D array fails...
	
		for(int x = 0; x < assigned; ++x)
		{
			delete [] grid_[x];
		}	
	
		delete [] grid_;
		grid_ = 0;
	
		throw e;
	}
}


AsciiGrid::~AsciiGrid()
{
	if(grid_ != 0)
	{
		for(int x = 0; x < width_; ++x)
		{
			delete [] grid_[x];
		}
		
		delete [] grid_;
		grid_ = 0;
	}
}


void AsciiGrid::drawPoint(int x, int y, char ascii /* = 'X' */)
{
	if(x >= 0 && x < width_ && y >= 0 && y <= height_)
	{
		grid_[x][y] = ascii;
	}
}


void AsciiGrid::swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}


void AsciiGrid::drawLine(int x1, int y1, int x2, int y2)
{
	if((x1 < 0 && x2 < 0) || (x1 >= width_ && x2 >= width_) || 
	   (y1 < 0 && y2 < 0) || (y1 >= height_ && y2 >= height_))
	{
		// not really worthy of an exception, but worth mentioning...
		std::cout << "AsciiGrid::drawLine - line coordinates(" << x1 << ',' << y1 << ")-(" 
				<< x2 << ',' << y2 << ") is completely off-grid.\n";

		return;
	}
	
	
	charGen_.beginLine(x1, y1, x2, y2);
	
	
	if(x1 == x2)   // simple horizontal line, no need to interpolate...
	{
		if(y1 > y2) swap(y1, y2);
		
		while(y1 <= y2)
		{
			drawPoint(x1, y1++, charGen_.getNextChar());
		}
		
		return;
	}
	else if(y1 == y2)  // vertical line
	{
		if(x1 > x2) swap(x1, x2);
		
		while(x1 <= x2)
		{
			drawPoint(x1++, y1, charGen_.getNextChar());
		}
		
		return;
	}
	
				// if we are here, line is at some sort of angle, so interpolate using Bresenham's algorithm...
	if(x1 > x2)	// for this version of Bressenham's, we need x1 <= x2
	{
		swap(x1, x2);
		swap(y1, y2);
	}
	
	
	int dy = y2 - y1;		// delta 'y', from p1 to p2
	int dx = x2 - x1;		// delta 'x'...
	int dy_2 = (dy << 1);	// delta y * 2
	int dx_2 = (dx << 1);	// delta x * 2
	
	
	if(dy > 0)  // line is ascending
	{
		int dy2LessDx2 = dy_2 - dx_2;
		
		if(dy <= dx)  // line is ascending 45 degrees or less (to the horizontal)
		{
			int bError = dy_2 - dx;
			
			while(x1 <= x2)
			{
				drawPoint(x1, y1, charGen_.getNextChar());
				
				if(bError <= 0)
				{
					bError += dy_2;
				}
				else 
				{
					++y1;
					bError += dy2LessDx2; 
				}
				
				++x1;
			}
		}
		else  // line is ascending steeper than 45 degrees
		{
			int bError = dx_2 - dy;
			
			while(y1 <= y2)
			{
				drawPoint(x1, y1, charGen_.getNextChar());
				
				if(bError <= 0)
				{
					bError += dx_2;
				}
				else 
				{
					++x1;
					bError -= dy2LessDx2;
				}

				++y1;
			}
		}
	}
	else  // line is descending...
	{
		int dy2PlussDx2 = dy_2 + dx_2;
		
		if(dx >= -dy)  // line is descending at 45 degrees or less
		{
			int bError = -dy_2 - dx;
			
			while(x1 <= x2)
			{
				drawPoint(x1, y1, charGen_.getNextChar());
				
				if(bError <= 0)
				{
					bError -= dy_2;
				}
				else 
				{
					--y1;
					bError -= dy2PlussDx2;
				}
				
				++x1;
			}
		}
		else   // line is descending steeper than 45 degrees
		{
			int bError = dx_2 + dy;
			
			while(y1 >= y2)
			{
				drawPoint(x1, y1, charGen_.getNextChar());
				
				if(bError <= 0)
				{
					bError += dx_2;
				}
				else 
				{
					++x1;
					bError += dy2PlussDx2;
				}
				
				--y1;
			}
		}
	}
}


std::ostream& operator<<(std::ostream& out, AsciiGrid& grid)
{
	std::string topAndTail(grid.width_, '-');
	out << ' ' << topAndTail << '\n';
	
	for(int y = grid.height_ - 1; y >= 0; --y)  // reverse y-axis so we print on-screen with origin at bottom left
	{
		out << '|';
		
		for(int x = 0; x < grid.width_; ++x)
		{
			out << grid.grid_[x][y];
		}
		
		out << "|\n";
	}
	
	out << ' ' << topAndTail << "\n\nDone printing...\n\n";
	
	return out;
}