/* Phase 1 & 2: Board Initialization and Game Logic */
const rows = 6;
const cols = 7;
const boardElement = document.getElementById('game-board');
const turnIndicator = document.getElementById('turn-indicator');
const turnText = document.getElementById('turn-text');

let currentPlayer = 1; // 1 for Red (Player 1), 2 for Yellow (Player 2)
let gameActive = true;
let boardState = []; // 2D array representing the board (0 = empty, 1 = p1, 2 = p2)

function initBoard() {
    boardElement.innerHTML = '';
    // Initialize 6x7 empty board
    boardState = Array.from({ length: rows }, () => Array(cols).fill(0));
    currentPlayer = 1;
    gameActive = true;
    updateTurnUI();
    
    for (let c = 0; c < cols; c++) {
        // Create columns dynamically
        const column = document.createElement('div');
        column.classList.add('column');
        column.dataset.col = c;
        
        // Listen to click event for dropping pieces
        column.addEventListener('click', () => handleColumnClick(c));
        
        for (let r = 0; r < rows; r++) {
            // Create cells within each column dynamically
            const cell = document.createElement('div');
            cell.classList.add('cell');
            cell.dataset.row = r;
            cell.dataset.col = c;
            
            // Create placeholder disc for animation/state
            const disc = document.createElement('div');
            disc.classList.add('disc');
            cell.appendChild(disc);
            
            column.appendChild(cell);
        }
        
        boardElement.appendChild(column);
    }
}

function handleColumnClick(colIndex) {
    if (!gameActive) return; // Prevent moves if game over

    // Find the lowest empty row in this column (start from bottom up: row 5 to 0)
    for (let r = rows - 1; r >= 0; r--) {
        if (boardState[r][colIndex] === 0) {
            // Drop piece physically in data state
            boardState[r][colIndex] = currentPlayer;
            
            // Animate piece onto the UI grid
            const cell = document.querySelector(`.cell[data-row="${r}"][data-col="${colIndex}"]`);
            const disc = cell.querySelector('.disc');
            disc.classList.add(currentPlayer === 1 ? 'p1' : 'p2');
            
            // Switch player turns properly
            currentPlayer = currentPlayer === 1 ? 2 : 1;
            updateTurnUI();
            
            // Phase 3 Note: Check for win / draw would happen right here
            
            return; // We placed a piece successfully, exit loop
        }
    }
    // If the loop finished and column is full, do nothing
}

function updateTurnUI() {
    if (currentPlayer === 1) {
        turnIndicator.classList.remove('yellow-turn');
        turnIndicator.classList.add('red-turn');
        turnText.textContent = "Player 1's Turn";
    } else {
        turnIndicator.classList.remove('red-turn');
        turnIndicator.classList.add('yellow-turn');
        turnText.textContent = "Player 2's Turn";
    }
}

document.addEventListener('DOMContentLoaded', () => {
    initBoard();
    
    // Connect the reset button directly to our initialization 
    document.getElementById('reset-btn').addEventListener('click', initBoard);
});
