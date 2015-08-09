var columns = 8;
var rows = 8;
var plateSize = 50;
var maxIndex = columns * rows;
var chessboard = new Array(maxIndex);
var chessman = new Array(maxIndex);
var plate;
var figure;

function index(column, row) {
    return column + (row * columns);
}

function createGameBoard()
{
    // Calculate plate size
    plateSize = Math.min(gameBoard.width/columns, gameBoard.height/rows)

    // Clear
    for (var i = 0; i < maxIndex; i++) {
        if (chessboard[i] != null)
            chessboard[i].destroy();
    }

    // Init board
    chessboard = new Array(maxIndex);
    for (var column = 0; column < columns; column++) {
        for (var row = 0; row < rows; row++) {
            chessboard[index(column, row)] = null;
            createPlate(column, row);
        }
    }
}

function createPlate(column, row) {
    if (plate == null)
        plate = Qt.createComponent("BoardPlate.qml");

    if (plate.status == Component.Ready) {
        var plateObject = plate.createObject(gameBoard);
        if (plateObject == null) {
            console.log("error creating plate");
            console.log(plate.errorString());
            return false;
        }

        plateObject.row = row;
        plateObject.column = column;
        plateObject.x = column * plateSize;
        plateObject.y = row * plateSize;
        plateObject.width = plateSize;
        plateObject.height = plateSize;
        chessboard[index(column, row)] = plateObject;
    } else {
        console.log("error loading plate");
        console.log(plate.errorString());
        return false;
    }
    return true;
}


function startGame()
{
    // Clear
    for (var i = 0; i < maxIndex; i++) {
        if (chessman[i] != null)
            chessman[i].destroy();
    }

    // Init figures
    chessman = new Array(maxIndex);
    for (var column = 0; column < columns; column++) {
        for (var row = 0; row < rows; row++) {
            chessman[index(column, row)] = null;
       }
    }

    for (var column = 0; column < columns; column++) {
        createFigure(column, 0);
        createFigure(column, 1);
        createFigure(column, 6);
        createFigure(column, 7);
    }
}


function createFigure(column, row, figure, side) {
    if (figure == null)
        figure = Qt.createComponent("GameFigure.qml");

    if (figure.status == Component.Ready) {
        var figureObject = figure.createObject(gameBoard);
        if (figureObject == null) {
            console.log("error creating figure");
            console.log(figure.errorString());
            return false;
        }

        figureObject.row = row;
        figureObject.column = column;
        figureObject.x = column * plateSize;
        figureObject.y = row * plateSize;
        figureObject.width = plateSize;
        figureObject.height = plateSize;
        figureObject.init();
        chessman[index(column, row)] = figureObject;
    } else {
        console.log("error loading figure");
        console.log(plate.errorString());
        return false;
    }
    return true;
}

