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



//main program begin from here
int main()
{
	const int rows = 6;				//store the total rows of game board
	const int coulumns = 7;			//store the total coulumns of game board

	char board[rows][coulumns];			//array for whole game board


	int col;				//take the user input for the coulumn
	int row;				//it will detect empty row of given coulumn

	int choice;		//it will store what the user want to do [e.g play game, show record etc]
	int again = 1;	/*it will be used to control the loop. because after the end of game user can
					want to do anything. like they want to see credits etc after the end of game*/

	char name1[21];			//store name of player one
	char name2[21];			//store name of player two

	char ch = '-';			//Store which player will use which characters

	int t_turns = 0;			//store the total turns used to end the game
	int win_turns = 0;			//store the number of turns of winner
	int p1_turns = 0;			//store the turns of (player 1)
	int p2_turns = 0;			//store the turns of (player 2)

	while (again != 0)
	{


		std::cout << "1. Play\n"
			<< "2. Credits\n"
			<< "3. Rules/Regulation\n"
			<< "4. Records\n"
			<< "5. Exit\n"
			<< " Enter your choice:  ";
		std::cin >> choice;
		std::cin.ignore();

		switch (choice)
		{
		case 1:
			//all the functions and functunality for playing game come here


			std::cout << "Enter the name of first player: ";
			std::cin.getline(name1, 21);


			std::cout << "Enter the name of second player: ";
			std::cin.getline(name2, 21);

			toss(name1, 21, name2, 21);//This fuction will toss which player should play first.

			emptyboard(board, rows, coulumns);				//calling the empty board function that will intailize the whole board to '-'

			for (int i = 0; i < 42; i++)//This will rotate from all board
			{

				displayboard(board, rows, coulumns);			//displaying board;

				t_turns++;//Counting the total turns of both players.

				//Here i am using if else to know which player turn is this
				if (i % 2 == 0)
				{

					p1_turns++;//This calculating player 1 turns
					ch = 'X';
					std::cout << name1 << " turn.\nEnter the column of your choice [0 to 6]: ";
					std::cin >> col;//player one will enter the column for input
				}
				else
				{
					p2_turns++;//This calculating player 2 turns
					ch = '0';
					std::cout << name2 << " turn.\nEnter the column of your choice [0 to 6]: ";
					std::cin >> col;//player two will enter the column for input
				}

				//Calling all the functions
				coulumnvalidation(col);
				findemptyindex(board, rows, coulumns, row, col, ch);
				displayboard(board, rows, coulumns);			//displaying board;

				if (left_right(board, rows, coulumns, row, col, ch) || up_down(board, rows, coulumns, row, col, ch) || top_left_to_bottom_right(board, rows, coulumns, ch) || bottom_left_to_top_right(board, rows, coulumns, ch))
				{
					std::cout <<"Congratulations! " << ((ch == 'X') ? name1 : name2) << " Won.\n";

					//We are checking through the value of ch which player has won
					writeWinnerRecord(((ch == 'X') ? name1 : name2), 21, ((ch == 'X') ? p1_turns : p2_turns));
					break;
				}
				system("cls");
			}

			if (t_turns == 42)			//Checking whether the game is drawn or not
			{
				std::cout << "\nThe game is a tie!\n";

			}

			writePlayersRecord(name1, 21, p1_turns, name2, 21, p2_turns, t_turns);
			system("pause");
			break;
		case 2:
			//the credits function will come here
			std::cout << std::endl << std::endl;
			std::cout << "Abdullah Habib\t\t\t23F-3061\nMuhammad Danial Zaheer\t\t23F-3082\nAbdulRehman\t\t\t23F-3048\n\n\n********Thanks*********\n";
			break;
		case 3:
			//the rules function come here

			rules();
			break;
		case 4:
			//the records function came here

			// Display records
			int recordChoice;
			std::cout << "Select records to display:\n";
			std::cout << "1. Winner Records\n";
			std::cout << "2. Player Records\n";
			std::cout << "Enter your choice: ";
			std::cin >> recordChoice;
			std::cout << std::endl << std::endl << std::endl;

			switch (recordChoice) {
			case 1:
				// Display winner records
				readWinnerRecord();
				break;
			case 2:
				// Display player records
				readPlayersRecord();
				break;
			default:
				std::cout << "Invalid choice for records display.\n";
			}
			break;
		case 5:
			//the quit function will come here

			quit();
			break;
		default:
			std::cout << "wrong input";
		}

		std::cout << "\nDo you want to go again? [1 for yes] [0 for no]: ";
		std::cin >> again;
		std::cout << std::endl << std::endl << std::endl;
	}
}
/* -------------------------- - end of main function----------------*/



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