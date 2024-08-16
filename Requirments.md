//In each class all the attributes are private and all the methods are public unless mentioned otherwise

Class Player:
  Attributes:
    string name  //store name of player
    string moves_count  //keep count of user moves. Intially set to zero
    char item  //store the charactor that will input in board on that player turn
  Methods:
    void setName() const
    string getName() const
    void incrementMoveCount()
    string covertToString() const  //this function player data into a string to make writing and reading from file easy
End Class PLayer

Class Board:
  Attributes:
    const int col = 6
    const int row = 7
    int board[row][col]  //main board. Initialized to '-' character
  Methods:
    int isColumnFree(const int col_number) const    //recieve column number and check whether it is has any empty place or not. Returns the row number if any empty slot is found otherwise returns -1
    void input(const char to_input,const int row_number, const int col_number)  //reiceve the row number, column number and charactor to input
    void displayBoard() const    //display board on screen
    bool leftToRight() const     //check for discs on left and right
    bool upToDown() const        //check for discs upward and downward
    bool leftToRightDiognal() const  //check diognally from top right to bottom left
    bool rightToLeftDiognal() const  //check diognally from boothem right to top left
End Class Board


class Connect4Game:
  Attributes:
    Board board
    Player p1
    Player p2
  Methods:
    private: int toss() const //return result of toss. 0 for player1 and 1 player2
    void playGame()  //this function contains all the funtunality of game
    void playerTurn(Player p)  //this function will take input from the player whose turn is this
    int getUserInput() const   //return user inputted column number
    void checkUserInput(int user_input) const  //this function make sure that user input is valid
    void writePLayersData() const  //write data of all player who have played the game
    void writeWinnerData() const  //write data of all the winners of the game
    void readPlayersData() const    //read the data in playersData file
    void readWinnerData() const    //read the data in the winnerData file
    void rules() const
    
    

    
