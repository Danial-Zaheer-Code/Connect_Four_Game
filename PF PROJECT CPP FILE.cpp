/*we are going to create the connect-4 game. user can selet from 4 choices.
1. play
2. credits
3. rules
4. record
5. exit
on selscting 1. first of all name of both players is taken. both players will be given an color between blue
and red. then we toss between them. the winning player will take the first turn. the player will select the
coulum of his choice. we will enter the value in lowest empty box(row) of that coulumn. we will then check
right, left, up, down, right diagonal, left diognal combinations of 4 boxes with same color. if we find one,
that player will be the winner. ohterwise the game continue. if no one won the game will be a tie.*/
//including libaries
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<ctime>
#include<string>
#include<cmath>


//all functions declaration

// Function declarations
void readWinnerRecord();				//Reading record of winner file
void readPlayersRecord();				//Reading record of drawn file

void writeWinnerRecord(char[], int, int);			//Writing winner record in an external file 
void writePlayersRecord(char[], int, int, char[], int, int, int);		//writing draw record in another file

void emptyboard(char[][7], int, int);			//Initializing whole board to 0
void displayboard(char[][7], int, int);			//display the baord in each turn
void toss(char[], int, char[], int);  // Function for toss

void findemptyindex(char[][7], int, int, int&, int&, char);			//check the user inout and find the empty box to place

void coulumnvalidation(int&, int = 7);			//checking coulumn

void rules();
void quit();
//These fuctions are for diagonal checking and up down left and right 
bool left_right(char[][7], int, int, int, int, char);
bool up_down(char[][7], int, int, int, int, char);
int top_left_to_bottom_right(char[][7], int, int, char);
int bottom_left_to_top_right(char[][7], int, int, char);		//this function will chehck the right diognal combination






//All function definations comes here

//contains the rules of the game
void rules()
{
	std::cout << "\nThe user will enter their names. "<<std::endl
		<< "Then the players will toss. " << std::endl
		<< "The winning player will start the game, " << std::endl
		<< "Each player will choose which coulumn they want to select. " << std::endl
		<< "The lowest empty cell of the coulumn will be filled. " << std::endl
		<< "The players will make a combination of 4. " << std::endl
		<< "The combination could be up, down, right, left and both diognals. " << std::endl
		<< "The first player to make the combination will win.\n";
}

/*******End of function*********/

//exiting the game
void quit()
{
	exit(0);
}
/**********end of function*********/



void emptyboard(char board[][7], int rows, int coulumns)			//intialize the board to '-'
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < coulumns; j++)
		{
			board[i][j] = '-';
		}
	}
}
/***********end of function*********/

//this function is just displaying the array after each input from the user
void displayboard(char board[][7], int rows, int coulumns)
{
	std::cout << "0  1  2  3  4  5  6\n\n";
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < coulumns; j++)
		{
			std::cout << board[i][j] << "  ";
		}
		std::cout << std::endl << std::endl;
	}
}
/***********end of function*********/

//this function here will check the input of user.
void coulumnvalidation(int& col, int before)
{

	/*here before is a deafualt variable. basically it stores thre vlaue of coulumn if it is full to campare with the next input.
	but if the coulumn is out of range when inputted at the start of turn. the before have default value 7. so that it do not effect the condition*/
	while (col < 0 || col > 6 || col == before)
	{
		std::cout << "Wrong input.Input again: ";
		std::cin >> col;
	}

}

/***********end of function*********/




//here is the funcion finding empty spaces from the bottem for the coulumn the user has entered
void findemptyindex(char board[][7], int rows, int columns, int& row, int& col, char ch)
{
	int before; // it will store the value of column if it is full
	bool flag = true;

	for (row = rows - 1; row >= 0; row--)
	{
		flag = true;
		while (flag == true)
		{
			if (board[0][col] == '-')
			{
				/* If the slot is empty at the row of given coulumn than it is filled */
				if (board[row][col] == '-')
				{
					board[row][col] = ch;
					return;
				}
				flag = false;

			}
			else
			{
				before = col;

				std::cout << "\nThe column is full.Input again: ";
				std::cin >> col;

				coulumnvalidation(col, before);
			}
		}
	}
}
/***********end of function*********/


//check the left and right combination
bool left_right(char board[][7], int rows, int coulumns, int row, int coulumn, char ch)
{
	int result = 0;

	for (int j = 0; j < coulumns; j++)
	{
		if (board[row][j] == ch)
		{
			result++;
		}
		else
		{
			result = 0;
		}

		if (result == 4)
		{
			return 1;
		}
	}


	return 0;
}
/********End of function********/


//This function will find the up-down combination
bool up_down(char board[][7], int rows, int coulumns, int row, int col, char ch)
{
	int result = 0;

	for (int i = 0; i < rows; i++)
	{
		if (board[i][col] == ch)
		{
			result++;
		}
		else
		{
			result = 0;
		}

		if (result == 4)
		{
			return 1;
		}
	}


	return 0;;
}
/**********End of function**********/



int top_left_to_bottom_right(char board[][7], int ROWS, int COLS, char ch)
{

	for (int i = 0; i <= ROWS - 4; i++)
	{
		for (int j = 0; j <= COLS - 4; j++)
		{
			if (board[i][j] == ch &&
				board[i + 1][j + 1] == ch &&
				board[i + 2][j + 2] == ch &&
				board[i + 3][j + 3] == ch)
			{
				return 1;
			}
		}
	}
	return 0;
}
/*******End of file****************/



int bottom_left_to_top_right(char board[][7], int ROWS, int COLS, char ch)
{
	for (int i = 3; i < ROWS; i++)
	{
		for (int j = 0; j <= COLS - 4; j++)
		{
			if (board[i][j] == ch &&
				board[i - 1][j + 1] == ch &&
				board[i - 2][j + 2] == ch &&
				board[i - 3][j + 3] == ch)
			{
				return 1;
			}
		}
	}
	return 0;
}
/*******End of file************/


void readWinnerRecord()
{
	std::string line;
	std::ifstream winnerFile;
	winnerFile.open("winner_record.txt");

	if (!winnerFile.is_open())
	{
		std::cout << "file not found." << std::endl;
	}
	else
	{

		while (!winnerFile.eof())
		{
			getline(winnerFile, line);
			std::cout << line << std::endl;
		}
		winnerFile.close();

	}
}
/*********End of file********/



void readPlayersRecord()
{
	std::string line;
	std::ifstream playersFile;
	playersFile.open("players_record.txt");

	if (!playersFile.is_open())
	{
		std::cout << "file not found" << std::endl;
	}
	else
	{

		while (!playersFile.eof())
		{
			getline(playersFile, line);
			std::cout << line << std::endl;
		}
		playersFile.close();

	}
}
/***********End of function*********/


void writeWinnerRecord(char winner[], int size, int winnerTurns) {
	std::ofstream winnerFile;
	winnerFile.open("winner_record.txt", std::ios::app);

	if (!winnerFile.is_open())
	{
		std::cout << "File not found." << std::endl;

	}
	else
	{
		winnerFile << "Winner: " << winner << "\tTurns: " << winnerTurns << std::endl;
		winnerFile.close();
	}
}
/***********End of function*********/


void writePlayersRecord(char player1[], int size1, int p1Turns, char player2[], int size2, int p2Turns, int totalTurns) {
	std::ofstream playersFile;
	playersFile.open("players_record.txt", std::ios::app);

	if (!playersFile.is_open())
	{
		std::cout << "file not found " << std::endl;
	}
	else
	{
		playersFile << "Player 1: " << player1 << "\tTurns: " << p1Turns << std::endl;
		playersFile << "Player 2: " << player2 << "\tTurns: " << p2Turns << std::endl;
		playersFile << "Total Turns: " << totalTurns << std::endl << std::endl;
		playersFile.close();
	}
}
/***********End of function*********/


//tossing between the players
void toss(char player1[], int size1, char player2[], int size2)
{
	std::cout << "Tossing to decide who goes first...\n";

	srand(time(0));//seeding

	// Generating a random number
	int tossResult = rand() % 2;

	if (tossResult == 0)
	{
		std::cout << player1 << " wins the toss!\n";
	}
	else
	{
		std::cout << player2 << " wins the toss!\n";
		for (int i = 0; i < size1; ++i)
		{
			std::swap(player1[i], player2[i]);//Swaping character by character index.
		}

	}


}