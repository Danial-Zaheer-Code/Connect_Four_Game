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
		
		for (int i = 0; i < 3; i++)
		{
			if (abs(row - i) == col)
			{
				r = i;
				c = 0;
				return checkLeftDiognal(value, r, c);
			}
		}

		for (int i = 1; i < 4; i++)
		{
			if (abs(col - i) == row)
			{
				r = 0;
				c = i;
				return checkLeftDiognal(value, r, c);
			}
		}
		
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
		int r = 0;
		int c = 0;
		for (int i = 3; i < 6; i++)		//checking rows at first column
		{
			if (abs(i - row) == col)
			{
				r = i;
				c = 0;
				return checkRightDiognal(value, r, c);
			}
		}

		for (int i = 1; i < 4; i++)
		{
			if (abs(5 - row) == abs(col - i))
			{
				r = 5;
				c = i;
				return checkRightDiognal(value, r, c);
			}
		}
	}

	return false;
}


bool Board::checkRightDiognal(const char value, const int row, const int col) const
{
	int count = 0;
	for (int i = row, j = col; i > 0 && j < 7; i--,j++)
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