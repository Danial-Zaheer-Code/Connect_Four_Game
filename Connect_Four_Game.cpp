
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
	while (std::cin.fail() || n == INT_MAX || n == INT_MIN || n <= 0 || n > 7)	//check for any error
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Wrong Input. Enter an integer between 1 and 7: ";
		std::cin >> n;
	}
	
}


bool Connect4Game::playerTurn(Player* p)		//this function will be called on each player turn
{
	int col = 0, row = 0;	//store the row and column number on which user will input
	while(1)
	{
		std::cout << p->getName() << " turn:\n";
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

			if (checkAllDirection(p->getInputChar(), row, col - 1))		//if any one combination is found
			{
				std::cout<<p->getName()<<" Won!\n";
				writeWinnerData(p);
				return 1;
			}
			else
			{				//if no combination is found
				return 0;
			}
		}	
	}
}


bool Connect4Game::checkAllDirection(const char in,const int row, const int col) const
{
	return (b.leftToRight(in, row) || b.upToDown(in, col) || b.bottomLeftToTopRight(in, row, col) || b.topLeftToBottomRight(in, row, col));
}

void Connect4Game::playGame()
{
	std::string name;
	bool is_combination_found = false;		//it will store one if any player won. Otherwise false
	//Getting players Name
	std::cout << "Enter First Player Name: ";
	std::getline(std::cin, name);
	p1.setName(name);
	std::cout << "Enter Second Player Name: ";
	std::getline(std::cin, name);
	p2.setName(name);

	std::cin.ignore();
	
	while (b.getMoves() < 42)
	{
		b.displayBoard();
		if (b.getMoves() % 2 == 0)
		{
			is_combination_found = playerTurn(&p1);
		}
		else
		{
			is_combination_found = playerTurn(&p2);
		}
		b.incrementMoves();
		if (is_combination_found)
		{
			writePlayerData();
			return;
		}
		system("cls");
	}

	b.displayBoard();
	std::cout << "Match is a tie\n";
	writePlayerData();

}


void Connect4Game::writeWinnerData(Player* p) const		//write data of winner
{
	std::ofstream handler;

	handler.open("Winner_Data.txt");

	if (!handler.is_open())			//if file is not opened
	{
		std::cout << "Winner_Data File Not Found.\n";
	}
	else
	{
		handler << p->convertToString() << std::endl;
	}

	handler.close();
}
void Connect4Game::writePlayerData() const			//write data of both player
{
	std::ofstream handler;

	handler.open("Player_Data.txt");

	if (!handler.is_open())		//if file is not opened
	{
		std::cout << "Player_Data File Not Found.\n";
	}
	else
	{
		handler << p1.convertToString() << std::endl<<p2.convertToString()<<std::endl;
	}

	handler.close();
}


void Connect4Game::readWinnerData() const
{
	std::ifstream handler;

	handler.open("Winner_Data.txt");

	if (!handler.is_open())
	{
		std::cout << "\nNo record Found\n";
	}
	else
	{
		std::string data;
		while (!handler.eof())
		{
			std::getline(handler, data);
			std::cout << data << "\n";
		}
	}
}
void Connect4Game::readPlayerData() const
{
	std::ifstream handler;

	handler.open("Player_Data.txt");

	if (!handler.is_open())
	{
		std::cout << "\nNo record Found\n";
	}
	else
	{
		std::string data;
		while (!handler.eof())
		{
			std::getline(handler, data);
			std::cout << data << "\n";
		}
	}
}