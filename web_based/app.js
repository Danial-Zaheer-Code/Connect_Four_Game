/* Game Settings */
const rows = 6;
const cols = 7;
let player1Name = "Player 1";
let player2Name = "Player 2";
let currentPlayer = 1;
let gameActive = false;
let boardState = [];
let moveCount = 0;

/* DOM Elements */
const boardElement = document.getElementById('game-board');
const turnIndicator = document.getElementById('turn-indicator');
const turnText = document.getElementById('turn-text');
const endMessage = document.getElementById('end-message');

/* Screens */
const mainMenuScreen = document.getElementById('main-menu');
const nameInputScreen = document.getElementById('name-input-screen');
const gameScreen = document.getElementById('game-screen');

/* Modals */
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
        player1Name = document.getElementById('p1-name').value.trim() || "Player 1";
        player2Name = document.getElementById('p2-name').value.trim() || "Player 2";
        switchScreen(gameScreen);
        initBoard();
    });

    // Game Actions
    document.getElementById('reset-btn').addEventListener('click', initBoard);
    document.getElementById('quit-btn').addEventListener('click', () => {
        gameActive = false;
        switchScreen(mainMenuScreen);
    });

    // Modals Close/Actions
    document.getElementById('close-credits-btn').addEventListener('click', () => creditsModal.classList.add('hidden-modal'));
    document.getElementById('close-results-btn').addEventListener('click', () => resultsModal.classList.add('hidden-modal'));
    document.getElementById('play-again-btn').addEventListener('click', () => {
        winModal.classList.add('hidden-modal');
        initBoard();
    });
    document.getElementById('win-menu-btn').addEventListener('click', () => {
        winModal.classList.add('hidden-modal');
        switchScreen(mainMenuScreen);
    });

    // History Downloads
    document.getElementById('download-all-results-btn').addEventListener('click', downloadAllHistoryJson);
});

function switchScreen(targetScreen) {
    document.querySelectorAll('.screen').forEach(el => {
        el.classList.replace('active-screen', 'hidden-screen');
    });
    targetScreen.classList.replace('hidden-screen', 'active-screen');
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
    const directions = [
        [[0, 1], [0, -1]],   // Horizontal
        [[1, 0], [-1, 0]],   // Vertical
        [[1, 1], [-1, -1]],  // Diagonal \
        [[1, -1], [-1, 1]]   // Diagonal /
    ];

    for (let dir of directions) {
        let count = 1;

        for (let vector of dir) {
            let r = row + vector[0];
            let c = col + vector[1];

            while (r >= 0 && r < rows && c >= 0 && c < cols && boardState[r][c] === player) {
                count++;
                r += vector[0];
                c += vector[1];
            }
        }

        if (count >= 4) return true;
    }
    return false;
}

function endGame(winnerName) {
    gameActive = false;
    let message = winnerName === "Draw" ? "Game Ended in a Draw!" : `${winnerName} Wins!`;
    endMessage.textContent = message;
    winModal.classList.remove('hidden-modal');

    saveAndDownloadResult(winnerName);
}

function saveAndDownloadResult(winnerName) {
    const timestamp = new Date().toISOString();
    let resultObj = {
        timestamp: timestamp,
        player1: player1Name,
        player2: player2Name,
        winner: winnerName === "Draw" ? "None" : winnerName,
        loser: winnerName === "Draw" ? "None" : (winnerName === player1Name ? player2Name : player1Name),
        isDraw: winnerName === "Draw",
        totalMoves: moveCount
    };

    // Attempt to save to Local Storage for "View Results" screen
    let history = [];
    try {
        history = JSON.parse(localStorage.getItem('connect4_history') || '[]');
    } catch (e) { }

    history.push(resultObj);
    localStorage.setItem('connect4_history', JSON.stringify(history));

    // DOWNLOAD JSON
    downloadFile(JSON.stringify(resultObj, null, 4), 'application/json', `connect_4_result_${Date.now()}.json`);

    // DOWNLOAD TXT
    let txtContent = `--- Connect 4 Game Result ---\n`;
    txtContent += `Date: ${new Date().toLocaleString()}\n`;
    txtContent += `Player 1 (Red): ${player1Name}\n`;
    txtContent += `Player 2 (Yellow): ${player2Name}\n`;
    if (winnerName === "Draw") {
        txtContent += `Result: Draw\n`;
    } else {
        txtContent += `Winner: ${resultObj.winner}\n`;
        txtContent += `Loser: ${resultObj.loser}\n`;
    }
    txtContent += `Total Moves: ${moveCount}\n`;
    txtContent += `-----------------------------\n`;

    downloadFile(txtContent, 'text/plain', `connect_4_result_${Date.now()}.txt`);
}

function downloadFile(content, mimeType, filename) {
    const blob = new Blob([content], { type: mimeType });
    const url = URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.href = url;
    a.download = filename;
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
    URL.revokeObjectURL(url);
}

function showResultsModal() {
    resultsModal.classList.remove('hidden-modal');
    const resultsList = document.getElementById('results-list');
    resultsList.innerHTML = '';

    let history = [];
    try {
        history = JSON.parse(localStorage.getItem('connect4_history') || '[]');
    } catch (e) { }

    if (history.length === 0) {
        resultsList.innerHTML = '<p style="color:white; text-align:center;">No matches played yet.</p>';
        return;
    }

    // Display from newest to oldest
    history.slice().reverse().forEach(match => {
        const item = document.createElement('div');
        item.classList.add('result-item');

        let displayStr = `<span class="result-tag">Time:</span> ${new Date(match.timestamp).toLocaleString()}<br>`;
        displayStr += `<span class="result-tag">Match:</span> ${match.player1} vs ${match.player2}<br>`;

        if (match.isDraw) {
            displayStr += `<span class="result-tag">Outcome:</span> <span style="color:#fbbf24; font-weight:bold;">Draw</span><br>`;
        } else {
            displayStr += `<span class="result-tag">Outcome:</span> Winner: <span class="result-winner">${match.winner}</span> | Loser: ${match.loser}<br>`;
        }
        displayStr += `<span class="result-tag">Moves:</span> ${match.totalMoves}`;
        item.innerHTML = displayStr;
        resultsList.appendChild(item);
    });
}

function downloadAllHistoryJson() {
    let history = localStorage.getItem('connect4_history') || '[]';
    downloadFile(history, 'application/json', `connect_4_full_history_${Date.now()}.json`);
}
