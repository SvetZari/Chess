var columns = 8;
var rows = 8;
var plateSize = 50;
var maxIndex = columns * rows;
var board = new Array(maxIndex);
var plate;

function index(column, row) {
    return column + (row * columns);
}

function createGameBoard()
{
    // Calculate plate size
    plateSize = Math.min(gameBoard.width/columns, gameBoard.height/rows)

    // Clear
    for (var i = 0; i < maxIndex; i++) {
        if (board[i] != null)
            board[i].destroy();
    }

    // Init board
    board = new Array(maxIndex);
    for (var column = 0; column < columns; column++) {
        for (var row = 0; row < rows; row++) {
            board[index(column, row)] = null;
            createPlate(column, row);
        }
    }
}

function createPlate(column, row) {
    if (plate == null)
        plate = Qt.createComponent("Plate.qml");

    if (plate.status == Component.Ready) {
        var plateObject = plate.createObject(gameBoard);
        if (plateObject == null) {
            console.log("error creating plate");
            console.log(plate.errorString());
            return false;
        }

        plateObject.type = (column + row) % 2 == 0 ? 0 : 1
        plateObject.x = column * plateSize;
        plateObject.y = row * plateSize;
        plateObject.width = plateSize;
        plateObject.height = plateSize;
        board[index(column, row)] = plateObject;
    } else {
        console.log("error loading plate");
        console.log(plate.errorString());
        return false;
    }
    return true;
}

