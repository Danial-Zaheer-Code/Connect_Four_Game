# Connect 4 Game - Class Structure and Rules

## Class `Player`

### Attributes:

#### Private:
- **`string name`**: Stores the name of the player.
- **`int moves_count`**: Keeps count of the player's moves, initially set to zero.
- **`char item`**: Stores the character that will be placed on the board during the player's turn.

### Methods:

#### Public Methods:
- **`void getName(const string& n)`**: set the name of the player.
- **`string getName() const`**: Returns the name of the player.
- **`string getMoveCount() const`**:Returns number of moves of player.
- **`void incrementMoveCount()`**: Increments the player's move count by one.
- **`string convertToString() const`**: Converts the player's data into a string format, making it easier to write and read from a file.

---

## Class `Board`

### Attributes:

#### Private:
- **`const int col = 7`**: Number of columns on the board.
- **`const int row = 6`**: Number of rows on the board.
- **`int board[row][col]`**: The main board, initialized with the `'-'` character to indicate empty slots.
- **`const int total_moves`**:Store the total number of moves that can be played
- **'int current_moves`**:Store the number of moves that have been played

### Methods:

#### Public Methods:
- **`int isColumnFree(const int col_number) const`**: 
  - Receives a column number and checks if there is any empty space in that column.
  - Returns the row number of the first empty slot if available; otherwise, returns `-1`.

- **`void input(const char to_input, const int row_number, const int col_number)`**: 
  - Receives the row number, column number, and the character to input.
  - Places the character in the specified row and column on the board.

- **`void displayBoard() const`**: Displays the current state of the board on the screen.

- **`bool leftToRight(const char value, const int row) const`**: Checks for consecutive discs from left to right.

- **`bool upToDown(const char value, const int col) const`**: Checks for consecutive discs from top to bottom.

- **`bool leftToRightDiagonal(const char value, const int row,const int col) const`**: Checks diagonally from top-left to bottom-right for consecutive discs.

- **`bool rightToLeftDiagonal(const char value, const int row, const int col) const`**: Checks diagonally from bottom-left to top-right for consecutive discs.

---

## Class `Connect4Game`

### Attributes:

#### Private:
    - **`Board board`**: Instance of the `Board` class representing the game board.
    - **`Player p1`**: Instance of the `Player` class representing player 1.
    - **`Player p2`**: Instance of the `Player` class representing player 2.

### Methods:

#### Public Methods:
- **`void playGame()`**: 
  - Contains the main functionality of the game, coordinating the flow of turns and game logic.
#### Private Methods:
- **`int toss() const`**: 
  - Returns the result of a toss to decide the first player. 
  - Returns `0` for player 1 and `1` for player 2.

- **`void playerTurn(Player p)`**: 
  - Handles the turn of the player, taking input and updating the board accordingly.

- **`int getUserInput() const`**: 
  - Prompts the user to input a column number and returns it.

- **`void checkUserInput(int user_input) const`**: 
  - Validates the user input to ensure it is within the valid range and corresponds to an available column.

- **`void writePlayersData() const`**: 
  - Writes the data of all players who have participated in the game to a file.

- **`void writeWinnerData() const`**: 
  - Writes the data of the winners to a separate file.

- **`void readPlayersData() const`**: 
  - Reads and displays the data of players from the players' data file.

- **`void readWinnerData() const`**: 
  - Reads and displays the data of winners from the winners' data file.

- **`void rules() const`**: 
  - Displays the rules of the Connect 4 game in a formatted manner.

---
