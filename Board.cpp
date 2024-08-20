#include<iostream>
#include "Board.h"



int Board::isColumnFree(const int col_number) const	//find empty row in the given column. Otherwise return -1
{
	for (int i = rows - 1; i >= 0; i--)
	{
		if (board[i][col_number] == '_')
			return i;
	}
	return -1;
}
void Board::input(const char to_input, const int row, const int col)	//put the to_input value at given row,column of board
{
	board[row][col] = to_input;
}
void Board::displayBoard() const
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << board[i][j] << "|";
		}
		std::cout << std::endl;
	}
}

bool Board::leftToRight(const char value, const int row) const	//Checks for consecutive discs from left to right.
{
	int count = 0;
	for (int i = 0; i < cols; i++)
	{
		if (board[row][i] == value)	//increent count if the value is found
			count++;
		else
			count = 0;		//if consecutive pattern is broken

		if (count == 4)		//if consecutive 4 same value are found
			return true;
	}
	return false;
}
bool Board::upToDown(const char value, const int col) const		//Checks for consecutive discs from top to bottom.
{
	int count = 0;
	for (int i = 0; i < rows; i++)
	{
		if (board[i][col] == value)	//increent count if the value is found
			count++;
		else
			count = 0;		//if consecutive pattern is broken

		if (count == 4)		//if consecutive 4 same value are found
			return true;
	}
	return false;
}
bool Board::topLeftToBottomRight(const char value, const int row, const int col) const	// Checks diagonally from top - left to bottom - right for consecutive discs.
{
	
	
	if (!((row > 3 && col < 2) || (row < 2 && col > 4)))
	{
		int r = 0;
		int c = 0;
		
		for (int i = 0; i < 4; i++)
		{
			c = abs(col - i);
			if (row == c)
			{
				r = row;
				break;
			}

			if (i < 3)
			{
				r = abs(row - i);
				if (col == row)
				{
					c = col;
					break;
				}
			}
		}
		return checkLeftDiognal(value, r, c);
	}
	return false;
}

bool Board::checkLeftDiognal(const char value, const int row, const int col) const	//checking left diognal
{
	int count = 0;
	for (int i = row, j = col; i < rows && j < cols; i++,j++)
	{
		if (board[i][j] == value)
			count++;
		else
			count = 0;

		if (count == 4)
			return true;
	}
	return false;
}




bool Board::bottomLeftToTopRight(const char value, const int row, const int col) const	//Checks diagonally from bottom - left to top - right for consecutive discs.
{
	
	if (!((row < 2 && col < 2) || (row > 3 && col > 3)))
	{
		for (int i = 6; i > 0; i--)
		{
			;
		}
	}

	return false;
}