class Board {
    constructor(rows = 6, cols = 7) {
        this.rows = rows;
        this.cols = cols;
        this.grid = [];
        this.current_moves = 0;
        this.reset();
    }

    reset() {
        this.grid = Array.from({ length: this.rows }, () => Array(this.cols).fill(0));
        this.current_moves = 0;
    }

    getMoves() {
        return this.current_moves;
    }

    incrementMoves() {
        this.current_moves++;
    }

    isColumnFree(colIndex) {
        // Starts from bottom up to find the first empty space
        for (let r = this.rows - 1; r >= 0; r--) {
            if (this.grid[r][colIndex] === 0) {
                return r;
            }
        }
        return -1;
    }

    input(playerValue, rowNumber, colNumber) {
        this.grid[rowNumber][colNumber] = playerValue;
    }

    checkWin(row, col, playerValue) {
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

                while (r >= 0 && r < this.rows && c >= 0 && c < this.cols && this.grid[r][c] === playerValue) {
                    count++;
                    r += vector[0];
                    c += vector[1];
                }
            }

            if (count >= 4) return true;
        }
        return false;
    }
}
