var columns = 8;
var rows = 8;
var plateSize = 50;
var maxIndex = columns * rows;
var chessboard = new Array(maxIndex);
var chessman = new Array(maxIndex);

function index(column, row) {
    return column + (row * columns);
}

function chessBoardModel()
{
    chessboard = new Array(maxIndex);
    for (var column = 0; column < columns; column++)
        for (var row = 0; row < rows; row++)
            chessboard[index(column, row)]
                    = { row: row, column: column }

    return chessboard;
}



/*
var fillFound; //Set after a floodFill call to the number of blocks found
var floodBoard; //Set to 1 if the floodFill reaches off that node

//![1]
function handleClick(xPos, yPos) {
    var current_column = Math.floor(xPos / plateSize);
    var current_row = Math.floor(yPos / plateSize);
    if (current_column >= columns || current_column < 0 || current_row >= rows || current_row < 0)
        return;
    if (chessman[index(current_column, current_row)] == null)
        return;

    console.log( current_column.toString() + current_row.toString());


    //If it's a valid block, remove it and all connected (does nothing if it's not connected)


    //floodFill(column, row, -1);
    //if (fillFound <= 0)
     //   return;

    //shuffleDown();
}
//![1]



function floodFill(column, row, type) {
    if (board[index(column, row)] == null)
        return;
    var first = false;
    if (type == -1) {
        first = true;
        type = board[index(column, row)].type;

        //Flood fill initialization
        fillFound = 0;
        floodBoard = new Array(maxIndex);
    }
    if (column >= maxColumn || column < 0 || row >= maxRow || row < 0)
        return;
    if (floodBoard[index(column, row)] == 1 || (!first && type != board[index(column, row)].type))
        return;
    floodBoard[index(column, row)] = 1;
    floodFill(column + 1, row, type);
    floodFill(column - 1, row, type);
    floodFill(column, row + 1, type);
    floodFill(column, row - 1, type);
    if (first == true && fillFound == 0)
        return;     //Can't remove single blocks
    board[index(column, row)].opacity = 0;
    board[index(column, row)] = null;
    fillFound += 1;
}

function shuffleDown() {
    //Fall down
    for (var column = 0; column < maxColumn; column++) {
        var fallDist = 0;
        for (var row = maxRow - 1; row >= 0; row--) {
            if (board[index(column, row)] == null) {
                fallDist += 1;
            } else {
                if (fallDist > 0) {
                    var obj = board[index(column, row)];
                    obj.y += fallDist * plateSize;
                    board[index(column, row + fallDist)] = obj;
                    board[index(column, row)] = null;
                }
            }
        }
    }
    //Fall to the left
    var fallDist = 0;
    for (var column = 0; column < maxColumn; column++) {
        if (board[index(column, maxRow - 1)] == null) {
            fallDist += 1;
        } else {
            if (fallDist > 0) {
                for (var row = 0; row < maxRow; row++) {
                    var obj = board[index(column, row)];
                    if (obj == null)
                        continue;
                    obj.x -= fallDist * plateSize;
                    board[index(column - fallDist, row)] = obj;
                    board[index(column, row)] = null;
                }
            }
        }
    }
}


//only floods up and right, to see if it can find adjacent same-typed blocks
function floodMoveCheck(column, row, type) {
    if (column >= maxColumn || column < 0 || row >= maxRow || row < 0)
        return false;
    if (board[index(column, row)] == null)
        return false;
    var myType = board[index(column, row)].type;
    if (type == myType)
        return true;
    return floodMoveCheck(column + 1, row, myType) || floodMoveCheck(column, row - 1, board[index(column, row)].type);
}
*/

