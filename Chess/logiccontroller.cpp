#include "logiccontroller.h"

bool LogicController::allowed(QObject *move) {
    ChessMove *chessmove = qobject_cast<ChessMove*>(move);
    if(chessmove != 0) {

       if(m_chessmoves.count() > 0)
           if(m_chessmoves.last()->side() == chessmove->side())
               return false;

       return chessmove->allowed();
    }
}

void LogicController::initChessman()
{
    m_chessman.clear();
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int column = 0; column < MAX_COLUMNS; column++) {
            //QQmlEngine::setObjectOwnership(chessman, QQmlEngine::JavaScriptOwnership);
            m_chessman.append(new AbstractFigure(row,column,true));
        }
    }
    emit chessmanChanged();
}

QList<QObject *> LogicController::chessman() {
    return m_chessman;
}

void LogicController::setCurrentMove(QObject *move) {
    ChessMove* chessmove = qobject_cast<ChessMove*>(move);
    if(chessmove != 0) {
        ChessMove* nextMove
                = new ChessMove(chessmove->rowFrom(), chessmove->rowTo(), chessmove->columnFrom(), chessmove->columnTo()
                    , chessmove->figure(), chessmove->side());

        m_chessmoves.append(nextMove);
        m_currentMove++;
        moveChessNext(chessmove);
        emit chessmanChanged();
    }
}

void LogicController::clear() {
    m_chessman.clear();
    m_chessmoves.clear();
    m_currentMove = 0;
}

void LogicController::processNextMove() {
    if(m_chessmoves.count() > m_currentMove) {
        moveChessNext(m_chessmoves.at(m_currentMove));
        m_currentMove++;
    }
}

void LogicController::processPrevMove() {
    if(m_currentMove > 0) {
        m_currentMove--;
        moveChessPrev(m_chessmoves.at(m_currentMove));
    }
}

void LogicController::saveGame()
{
    QFile file(m_gamesave);
    auto result = file.open(QIODevice::ReadWrite);
    if(!result) {
        qDebug() << "Something wrong. Can't open file.";
        return;
    }

    file.resize(0);
    QDataStream dataStream(&file);

    int count = m_chessmoves.count();
    dataStream << count;

    foreach (const ChessMove *move, m_chessmoves)
        dataStream << *move;

    file.flush();
    file.close();
}

void LogicController::loadGame()
{
    QFile file(m_gamesave);
    if(!file.exists()) {
        qDebug() << "Something wrong. File doesn't exist.";
        return;
    }

    auto result = file.open(QFile::ReadOnly);
    if(!result) {
        qDebug() << "Something wrong. Can't open file.";
        return;
    }

    clear();
    initChessman();

    QDataStream dataStream(&file);
    int count;
    dataStream >> count;

    for (int i = 0; i < count; i++) {
        ChessMove* move = new ChessMove();
        dataStream >> *move;
        m_chessmoves.append(move);
        processNextMove();
    }

    file.close();
    emit chessmanChanged();
}

int LogicController::index(const int row, const int column) {
    return column + (row * MAX_COLUMNS);
}

int LogicController::findChessMan(const int row, const int column) {
    foreach (QObject* figure, m_chessman) {
        AbstractFigure *abstractFigure = qobject_cast<AbstractFigure*>(figure);
        if(abstractFigure != 0)
            if(abstractFigure->row() == row && abstractFigure->column() == column)
                return m_chessman.indexOf(figure);
    }
    return -1;
}

bool LogicController::checkMove(int from, int to)
{
    qDebug() << "from " << from << "to" << to;
    if(from == to) return false;

    AbstractFigure *figureTo = qobject_cast<AbstractFigure*>(m_chessman[to]);
    if(figureTo == 0) return false;

    AbstractFigure *figureFrom = qobject_cast<AbstractFigure*>(m_chessman[from]);
    if(figureFrom == 0) return false;

    if(figureFrom->side() == figureTo->side())
        return false;

    return true;
}

void LogicController::moveChessNext(ChessMove *move)
{
    auto from = findChessMan(move->rowFrom(), move->columnFrom());
    auto to = findChessMan(move->rowTo(), move->columnTo());

    if(!checkMove(from, to))
        return;

    AbstractFigure *figureFrom = qobject_cast<AbstractFigure*>(m_chessman[from]);
    if(figureFrom == 0) return;

    figureFrom->setRow(move->rowTo());
    figureFrom->setColumn(move->columnTo());
    m_chessman[to] = figureFrom;
    m_chessman[from] = new AbstractFigure(move->rowFrom(), move->columnFrom());

    emit chessmanChanged();
}

void LogicController::moveChessPrev(ChessMove *move)
{
    auto to = findChessMan(move->rowFrom(), move->columnFrom());
    auto from = findChessMan(move->rowTo(), move->columnTo());

    if(!checkMove(from, to))
        return;

    AbstractFigure *figureFrom = qobject_cast<AbstractFigure*>(m_chessman[from]);
    if(figureFrom == 0) return;

    figureFrom->setRow(move->rowFrom());
    figureFrom->setColumn(move->columnFrom());
    m_chessman[to] = figureFrom;
    m_chessman[from] = new AbstractFigure(move->rowTo(), move->columnTo());

    emit chessmanChanged();
}


