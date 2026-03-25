function saveAndDownloadResult(winnerName) {
    const timestamp = new Date().toISOString();
    let resultObj = {
        timestamp: timestamp,
        player1: player1.getName(),
        player2: player2.getName(),
        winner: winnerName === "Draw" ? "None" : winnerName,
        loser: winnerName === "Draw" ? "None" : (winnerName === player1.getName() ? player2.getName() : player1.getName()),
        isDraw: winnerName === "Draw",
        totalMoves: gameBoard.getMoves(), // Retrieved dynamically from board class
        p1Moves: player1.getMoveCount(),
        p2Moves: player2.getMoveCount()
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
    txtContent += `Player 1 (Red): ${player1.convertToString()}\n`;
    txtContent += `Player 2 (Yellow): ${player2.convertToString()}\n`;
    if (winnerName === "Draw") {
        txtContent += `Result: Draw\n`;
    } else {
        txtContent += `Winner: ${resultObj.winner}\n`;
        txtContent += `Loser: ${resultObj.loser}\n`;
    }
    txtContent += `Total Moves: ${gameBoard.getMoves()}\n`; // Pulled intelligently
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
