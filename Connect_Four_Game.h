#pragma once
#include"Player.h"
#include"Board.h"
class Connect4Game
{
public:
	Connect4Game() :p1('X'), p2('0') {};
	~Connect4Game() {};

	void rules() const
	{
		std::cout << "The game will be played with two player. Player 1 will start the game.\n"
			<< "Each player will select the column number. The column number or between 1 and 7.\n"
			<< "User Have to create 4 consecutive sighn assign to him in any direction.\n"
			<< "Player1 will have 'X' sign and player 2 will have '0' sign.\n";
	}
private:
	Player p1;
	Player p2;

	Board b;
};

