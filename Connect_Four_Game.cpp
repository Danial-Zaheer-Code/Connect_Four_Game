#include "Connect_Four_Game.h"


void Connect4Game::rules() const
{
	std::cout << "The game will be played with two player. Player 1 will start the game.\n"
		<< "Each player will select the column number. The column number or between 1 and 7.\n"
		<< "User Have to create 4 consecutive sighn assign to him in any direction.\n"
		<< "Player1 will have 'X' sign and player 2 will have '0' sign.\n";
}



int Connect4Game::getUserInput() const//get column number from user
{
	int input;

	std::cout << "Enter column Number between 1 and 7: ";
	std::cin >> input;
	checkUserInput(input);
	return input;
}
void Connect4Game::checkUserInput(int& n) const		//check the user inputed number
{
	while (std::cin.fail() || n == INT_MAX || n == INT_MIN || n <= 0 || n > 7)
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Wrong Input. Enter an integer between 1 and 7: ";
		std::cin >> n;
	}
	
}


void Connect4Game::playerTurn(Player* p)		//this function will be called on each player turn
{
	int col = 0, row = 0;
	while(1)
	{
		int col = getUserInput();
		int row = b.isColumnFree(col-1);
		if (row == -1)
		{
			std::cout << "The Column is Not free. Enter again.\n";
		}
		else
		{
			b.input(p->getInputChar(), row, col - 1);
			p->incremetMove();
			break;
		}

	}

	


}



void Connect4Game::playGame()
{
	while (b.getMoves() < 42)
	{
		b.displayBoard();
		if (b.getMoves() % 2 == 0)
		{
			playerTurn(&p1);
		}
		else
		{
			playerTurn(&p2);
		}

		system("cls");
	}
}
