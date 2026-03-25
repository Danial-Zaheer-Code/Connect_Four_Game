class Player {
    constructor(name, inputChar) {
        this.name = name;
        this.moves_count = 0;
        this.item = inputChar;
    }

    setName(n) {
        this.name = n;
    }

    getName() {
        return this.name;
    }

    getMoveCount() {
        return this.moves_count;
    }

    getInputChar() {
        return this.item;
    }

    incrementMoveCount() {
        this.moves_count++;
    }

    convertToString() {
        return `${this.name},${this.moves_count},${this.item}`;
    }
}
