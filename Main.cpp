#include"Connect_Four_Game.h"

int main()
{
	Connect4Game game;
	char choice;
	while (1)
	{
		std::cout << "\n1. Play Game\n"
			<< "2. Rules\n"
			<< "3. Players Record\n"
			<< "4. Winners Record\n"
			<< "5. Exit\n"
			<< "Enter your choice: ";
		choice = std::cin.get();
		system("cls");
		switch (choice)
		{
		case '1':
			game.playGame();
			std::cin.ignore(1000, '\n');
			std::cout << "\n\nPress any key to continue:\n";
			std::cin.get();
			break;
		case '2':
			game.rules();
			break;
		case '3':
			game.readPlayerData();
			break;
		case '4':
			game.readWinnerData();
			break;
		case '5':
			exit(0);
		default:
			std::cout << "\n\nWrong Input\n\n";
			break;
		}
		system("cls");
	}

}