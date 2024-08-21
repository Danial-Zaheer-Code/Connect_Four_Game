#pragma once
#include<iostream>
class Board		//represent the game board
{
public:
	Board() :rows(6), cols(7), max_moves(7 * 6), current_moves(0)		//constructor
	{
		board = new char* [rows];
		for (int i = 0; i < rows; i++)
		{
			board[i] = new char[cols];
			for (int j = 0; j < cols; j++)
			{
				board[i][j] = '_';
			}
		}
	}
	~Board()	//destructor
	{
		for (size_t i = 0; i < rows; i++)
		{
			delete[] board[i];
		}
		delete[] board;
	}

	int isColumnFree(const int col_number) const;	//find empty row in the given column. Otherwise return -1
	void input(const char to_input, const int row_number, const int col_number);	//put the to_input value at given row,column of board
	void displayBoard() const;

	bool leftToRight(const char, const int row) const;	//Checks for consecutive discs from left to right.
	bool upToDown(const char, const int col) const;		//Checks for consecutive discs from top to bottom.
	bool topLeftToBottomRight(const char value, const int row, const int col) const;	// Checks diagonally from top - left to bottom - right for consecutive discs.
	bool bottomLeftToTopRight(const char value, const int row, const int col) const;	//Checks diagonally from bottom - left to top - right for consecutive discs.

	void incrementMoves();
	int getMoves() const;
private:
	const int cols;
	const int rows;

	char** board;		//main board

	const int max_moves;		//store total moves that can be played
	int current_moves;			//store number of moves that have been played

	bool checkLeftDiognal(const char value, const int row, const int col) const;	//check left diognal of board
	bool checkRightDiognal(const char value, const int row, const int col) const;	//check right diognal of board
};

