#pragma once
#include<fstream>
#include"Player.h"
#include"Board.h"
class Connect4Game
{
public:
	Connect4Game() :p1('X'), p2('0') {};
	~Connect4Game() {};

	void rules() const; //check rules
	void playGame();			//this function will be called when user want to play the game
	void readWinnerData() const;
	void readPlayerData() const;
private:
	Player p1;
	Player p2;

	Board b;

	bool playerTurn(Player* p);		//this function will be called on each player turn

	void writeWinnerData(Player* p) const;		//write data of winner
	void writePlayerData() const;			//write data of both player

	int getUserInput() const;				//get column number from user
	void checkUserInput(int& n) const;		//check the user inputed number

	bool checkAllDirection(const char in, const int row, const int col) const;		//this function will call functions to check every direction 
};

