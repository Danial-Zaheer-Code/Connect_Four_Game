const rows = 6;
const cols = 7;
const boardElement = document.getElementById('game-board');
const turnIndicator = document.getElementById('turn-indicator');
const turnText = document.getElementById('turn-text');

// Modals
const startModal = document.getElementById('start-modal');
const winModal = document.getElementById('win-modal');
const endMessage = document.getElementById('end-message');
const p1Input = document.getElementById('p1-name');
const p2Input = document.getElementById('p2-name');

let player1Name = "Player 1";
let player2Name = "Player 2";
let currentPlayer = 1; // 1 for P1, 2 for P2
let gameActive = false;
let boardState = [];
let moveCount = 0;

document.addEventListener('DOMContentLoaded', () => {
    // Show start modal natively loaded without "hidden"
    document.getElementById('start-btn').addEventListener('click', startGame);
    document.getElementById('play-again-btn').addEventListener('click', () => {
        winModal.classList.add('hidden');
        initBoard();
    });
    document.getElementById('reset-btn').addEventListener('click', initBoard);
});

function startGame() {
    // Get names from inputs
    player1Name = p1Input.value.trim() || "Player 1";
    player2Name = p2Input.value.trim() || "Player 2";
    
    // Hide start modal
    startModal.classList.add('hidden');
    
    initBoard();
}

function initBoard() {
    boardElement.innerHTML = '';
    boardState = Array.from({ length: rows }, () => Array(cols).fill(0));
    currentPlayer = 1;
    gameActive = true;
    moveCount = 0;
    updateTurnUI();
    
    for (let c = 0; c < cols; c++) {
        const column = document.createElement('div');
        column.classList.add('column');
        column.dataset.col = c;
        
        column.addEventListener('click', () => handleColumnClick(c));
        
        for (let r = 0; r < rows; r++) {
            const cell = document.createElement('div');
            cell.classList.add('cell');
            cell.dataset.row = r;
            cell.dataset.col = c;
            
            const disc = document.createElement('div');
            disc.classList.add('disc');
            cell.appendChild(disc);
            
            column.appendChild(cell);
        }
        boardElement.appendChild(column);
    }
}

function handleColumnClick(colIndex) {
    if (!gameActive) return;

    for (let r = rows - 1; r >= 0; r--) {
        if (boardState[r][colIndex] === 0) {
            boardState[r][colIndex] = currentPlayer;
            moveCount++;
            
            const cell = document.querySelector(`.cell[data-row="${r}"][data-col="${colIndex}"]`);
            const disc = cell.querySelector('.disc');
            disc.classList.add(currentPlayer === 1 ? 'p1' : 'p2');
            
            if (checkWin(r, colIndex, currentPlayer)) {
                endGame(currentPlayer === 1 ? player1Name : player2Name);
            } else if (moveCount === rows * cols) {
                endGame("Draw");
            } else {
                currentPlayer = currentPlayer === 1 ? 2 : 1;
                updateTurnUI();
            }
            return;
        }
    }
}

function updateTurnUI() {
    const activeName = currentPlayer === 1 ? player1Name : player2Name;
    turnText.textContent = `${activeName}'s Turn`;
    
    if (currentPlayer === 1) {
        turnIndicator.classList.remove('yellow-turn');
        turnIndicator.classList.add('red-turn');
    } else {
        turnIndicator.classList.remove('red-turn');
        turnIndicator.classList.add('yellow-turn');
    }
}

function checkWin(row, col, player) {
    // Directions: Horizontal, Vertical, Diagonal 1, Diagonal 2
    const directions = [
        [[0, 1], [0, -1]],
        [[1, 0], [-1, 0]],
        [[1, 1], [-1, -1]],
        [[1, -1], [-1, 1]]
    ];

    for (let dir of directions) {
        let count = 1; // Count includes the piece just dropped

        for (let vector of dir) {
            let r = row + vector[0];
            let c = col + vector[1];

            while (r >= 0 && r < rows && c >= 0 && c < cols && boardState[r][c] === player) {
                count++;
                r += vector[0];
                c += vector[1];
            }
        }

        if (count >= 4) {
            return true;
        }
    }
    return false;
}

function endGame(winnerName) {
    gameActive = false;
    let message = winnerName === "Draw" ? "Game Ended in a Draw!" : `${winnerName} Wins!`;
    endMessage.textContent = message;
    winModal.classList.remove('hidden');
    
    saveResultToFile(winnerName);
}

function saveResultToFile(winnerName) {
    const timestamp = new Date().toLocaleString();
    let fileContent = `--- Connect 4 Game Result ---\n`;
    fileContent += `Date: ${timestamp}\n`;
    fileContent += `Player 1 (Red): ${player1Name}\n`;
    fileContent += `Player 2 (Yellow): ${player2Name}\n`;
    
    if (winnerName === "Draw") {
        fileContent += `Result: Draw\n`;
    } else {
        const loserName = winnerName === player1Name ? player2Name : player1Name;
        fileContent += `Winner: ${winnerName}\n`;
        fileContent += `Loser: ${loserName}\n`;
        fileContent += `Total Moves: ${moveCount}\n`;
    }
    
    fileContent += `-----------------------------\n`;

    // Create a Blob and trigger download
    const blob = new Blob([fileContent], { type: 'text/plain' });
    const url = URL.createObjectURL(blob);
    
    const a = document.createElement('a');
    a.href = url;
    a.download = `connect_4_result_${Date.now()}.txt`;
    document.body.appendChild(a);
    a.click();
    
    // Cleanup
    document.body.removeChild(a);
    URL.revokeObjectURL(url);
}
