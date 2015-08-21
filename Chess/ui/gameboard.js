var columns = 8;
var rows = 8;
var plateSize = 50;
var maxIndex = columns * rows;
var chessboard = new Array(maxIndex);
var chessman = new Array(maxIndex);

function index(column, row) {
    return column + (row * columns);
}

function chessBoardModel() {
    chessboard = new Array(maxIndex);
    for (var column = 0; column < columns; column++)
        for (var row = 0; row < rows; row++)
            chessboard[index(column, row)]
                    = { row: row, column: column }

    return chessboard;
}
