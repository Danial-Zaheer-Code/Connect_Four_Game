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
	return false;
}
bool Board::topLeftToBottomRight(const int value, const int row, const int col) const	// Checks diagonally from top - left to bottom - right for consecutive discs.
{
	

	return false;
}
bool Board::bottomLeftToTopRight(const int value, const int row, const int col) const	//Checks diagonally from bottom - left to top - right for consecutive discs.
{
	
	return false;
}