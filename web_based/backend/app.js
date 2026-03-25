/* Game Instances */
let gameBoard = new Board(6, 7);
let player1 = new Player("Player 1", "p1");
let player2 = new Player("Player 2", "p2");

let currentPlayer = 1;
let gameActive = false;

/* DOM Elements */
const boardElement = document.getElementById('game-board');
const turnIndicator = document.getElementById('turn-indicator');
const turnText = document.getElementById('turn-text');
const endMessage = document.getElementById('end-message');

/* Screens & Modals */
const mainMenuScreen = document.getElementById('main-menu');
const nameInputScreen = document.getElementById('name-input-screen');
const gameScreen = document.getElementById('game-screen');
const winModal = document.getElementById('win-modal');
const resultsModal = document.getElementById('results-modal');
const creditsModal = document.getElementById('credits-modal');

document.addEventListener('DOMContentLoaded', () => {
    // Menu Buttons
    document.getElementById('menu-play-btn').addEventListener('click', () => switchScreen(nameInputScreen));
    document.getElementById('menu-results-btn').addEventListener('click', showResultsModal);
    document.getElementById('menu-credits-btn').addEventListener('click', () => creditsModal.classList.remove('hidden-modal'));

    // Setup Buttons
    document.getElementById('back-to-menu-btn').addEventListener('click', () => switchScreen(mainMenuScreen));
    document.getElementById('start-match-btn').addEventListener('click', () => {
        player1.setName(document.getElementById('p1-name').value.trim() || "Player 1");
        player2.setName(document.getElementById('p2-name').value.trim() || "Player 2");
        switchScreen(gameScreen);
        initBoardUI();
    });

    // Game Actions
    document.getElementById('reset-btn').addEventListener('click', initBoardUI);
    document.getElementById('quit-btn').addEventListener('click', () => {
        gameActive = false;
        switchScreen(mainMenuScreen);
    });

    // Modals Close/Actions
    document.getElementById('close-credits-btn').addEventListener('click', () => creditsModal.classList.add('hidden-modal'));
    document.getElementById('close-results-btn').addEventListener('click', () => resultsModal.classList.add('hidden-modal'));
    document.getElementById('play-again-btn').addEventListener('click', () => {
        winModal.classList.add('hidden-modal');
        initBoardUI();
    });
    document.getElementById('win-menu-btn').addEventListener('click', () => {
        winModal.classList.add('hidden-modal');
        switchScreen(mainMenuScreen);
    });

    // History Downloads
    document.getElementById('download-all-results-btn').addEventListener('click', downloadAllHistoryJson);
});

function switchScreen(targetScreen) {
    document.querySelectorAll('.screen').forEach(el => el.classList.replace('active-screen', 'hidden-screen'));
    targetScreen.classList.replace('hidden-screen', 'active-screen');
}

function initBoardUI() {
    boardElement.innerHTML = '';
    gameBoard.reset();
    
    currentPlayer = 1;
    gameActive = true;
    
    // Reset specific player moves tally
    player1.moves_count = 0;
    player2.moves_count = 0;

    updateTurnUI();

    for (let c = 0; c < gameBoard.cols; c++) {
        const column = document.createElement('div');
        column.classList.add('column');
        column.dataset.col = c;
        
        column.addEventListener('click', () => handleColumnClick(c));

        for (let r = 0; r < gameBoard.rows; r++) {
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

    let availableRow = gameBoard.isColumnFree(colIndex);
    if (availableRow !== -1) {
        
        // Register move in Board logically
        gameBoard.input(currentPlayer, availableRow, colIndex);
        gameBoard.incrementMoves();
        
        // Log move in Player systematically
        if (currentPlayer === 1) player1.incrementMoveCount();
        else player2.incrementMoveCount();

        // Update DOM Object
        const cell = document.querySelector(`.cell[data-row="${availableRow}"][data-col="${colIndex}"]`);
        const disc = cell.querySelector('.disc');
        disc.classList.add(currentPlayer === 1 ? player1.getInputChar() : player2.getInputChar());

        if (gameBoard.checkWin(availableRow, colIndex, currentPlayer)) {
            endGame(currentPlayer === 1 ? player1.getName() : player2.getName());
        } else if (gameBoard.getMoves() === gameBoard.rows * gameBoard.cols) {
            endGame("Draw");
        } else {
            currentPlayer = currentPlayer === 1 ? 2 : 1;
            updateTurnUI();
        }
    }
}

function updateTurnUI() {
    const activeName = currentPlayer === 1 ? player1.getName() : player2.getName();
    turnText.textContent = `${activeName}'s Turn`;

    if (currentPlayer === 1) {
        turnIndicator.classList.remove('yellow-turn');
        turnIndicator.classList.add('red-turn');
    } else {
        turnIndicator.classList.remove('red-turn');
        turnIndicator.classList.add('yellow-turn');
    }
}

function endGame(winnerName) {
    gameActive = false;
    let message = winnerName === "Draw" ? "Game Ended in a Draw!" : `${winnerName} Wins!`;
    endMessage.textContent = message;
    winModal.classList.remove('hidden-modal');

    // Securely call separated logic in storage.js
    saveAndDownloadResult(winnerName);
}
