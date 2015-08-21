#include "logiccontroller.h"

void LogicController::initChessman()
{
    clear();
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int column = 0; column < MAX_COLUMNS; column++) {
            m_chessman.append(new AbstractFigure(row, column, true, this));
        }
    }
    emit chessmanChanged();
}

LogicController::LogicController(QObject *parent)
    : QObject(parent) {
    initChessman();
}

QList<QObject *> LogicController::chessman() {
    return m_chessman;
}

bool LogicController::allowed(QObject *move) {
    ChessMove *chessmove = qobject_cast<ChessMove*>(move);
    if(chessmove != 0) {
        return checkMoveParity(chessmove->side()) && chessmove->isAllowed()
                && isValidMove(chessmove) && isValidTrace(chessmove);
    }
    return false;
}

void LogicController::setCurrentMove(QObject *move) {
    ChessMove* chessmove = qobject_cast<ChessMove*>(move);
    if(chessmove != 0) {
        ChessMove* nextMove
                = new ChessMove(chessmove->rowFrom(), chessmove->rowTo(), chessmove->columnFrom(), chessmove->columnTo()
                    , chessmove->figure(), chessmove->side(), chessmove->prevFigure(), chessmove->prevSide(), this);

        m_chessmoves.append(nextMove);
        m_currentMove++;
        moveNext(chessmove);
        emit chessmanChanged();
    }
}

void LogicController::clear() {
    m_chessman.clear();
    m_chessmoves.clear();
    m_currentMove = 0;
}

void LogicController::processNextMove(bool fast) {
    if(m_chessmoves.count() > m_currentMove) {
        moveNext(m_chessmoves.at(m_currentMove), fast);
        m_currentMove++;
    }
}

void LogicController::processPrevMove() {
    if(m_currentMove > 0) {
        m_currentMove--;
        movePrev(m_chessmoves.at(m_currentMove));
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
        ChessMove* move = new ChessMove(this);
        dataStream >> *move;
        m_chessmoves.append(move);
        processNextMove(true);
    }

    file.close();
    emit chessmanChanged();
}

int LogicController::index(const int row, const int column) {
    return column + (row * MAX_COLUMNS);
}

int LogicController::findChessman(const int row, const int column) {
    foreach (QObject* figure, m_chessman) {
        AbstractFigure *abstractFigure = qobject_cast<AbstractFigure*>(figure);
        if(abstractFigure != 0)
            if(abstractFigure->row() == row && abstractFigure->column() == column)
                return m_chessman.indexOf(figure);
    }
    return -1;
}

bool LogicController::isValidMove(ChessMove *move, bool back)
{
    auto to = findChessman(move->rowFrom(), move->columnFrom());
    auto from = findChessman(move->rowTo(), move->columnTo());

    if(from == to) return false;

    AbstractFigure *figureTo = qobject_cast<AbstractFigure*>(m_chessman[to]);
    if(figureTo == 0) return false;

    AbstractFigure *figureFrom = qobject_cast<AbstractFigure*>(m_chessman[from]);
    if(figureFrom == 0) return false;

    if(figureFrom->side() == figureTo->side())
        return false;

    if(!back) {
        switch (move->figure()) {
        case t_Figure::Pawn:
            if(figureFrom->side() != figureTo->side() && figureFrom->side() != -1) {
                if((move->rowFrom() != move->rowTo() && (move->columnFrom() != move->columnTo())))
                    return true;
                else
                return false;
            } break;
        default: break;
        }
    }

    return true;
}

bool LogicController::isValidTrace(ChessMove *move) {

    switch (move->figure()) {
    case t_Figure::Pawn:
    case t_Figure::Rook:
    case t_Figure::Queen:
    case t_Figure::Bishop:
         return validateTrace(move);
        break;

    case t_Figure::Knight:
    case t_Figure::King:
        return true;

    default:
        return false;
    }
}

bool LogicController::checkMoveParity(int side)
{
    if(m_chessmoves.empty()) {
        if(side != t_Side::White)
            return false;
    } else {
        if(m_chessmoves.last()->side() == side)
            return false;
    }
    return true;
}

bool LogicController::validateTrace(ChessMove *move)
{
    auto traceFailed = [&](int index) -> bool {
        AbstractFigure *figure = qobject_cast<AbstractFigure*>(m_chessman[index]);
        if (figure == 0) return false;
        return (figure->figure() != -1 && figure->figure() != move->figure());
    };

    if((move->rowFrom() != move->rowTo() && (move->columnFrom() != move->columnTo())))
    {
        auto deltaH = move->rowFrom() - move->rowTo();
        auto deltaW = move->columnFrom() - move->columnTo();
        if(abs(deltaH) != abs(deltaW))
            return false;

        auto delta = abs(deltaH);

        for (int i = 1; i < delta; i++) {
            auto rowSign = deltaH > 0 ? -1 : 1;
            auto columnSign = deltaW > 0 ? -1 : 1;
            auto index = findChessman(move->rowFrom() + i * rowSign, move->columnFrom() + i * columnSign);
            if (traceFailed(index)) return false;
        }
    }
    else
    {
        if(move->rowFrom() < move->rowTo())
        {
            for (int i = move->rowFrom() + 1; i < move->rowTo(); i++) {
                auto index = findChessman(i, move->columnTo());
                if (traceFailed(index)) return false;
            }
        }
        else if (move->rowFrom() > move->rowTo())
        {
            for (int i = move->rowFrom() - 1; i > move->rowTo(); i--) {
                auto index = findChessman(i, move->columnTo());
                if (traceFailed(index)) return false;
            }
        }

        if(move->columnFrom() < move->columnTo())
        {
            for (int i = move->columnFrom() + 1; i < move->columnTo(); i++) {
                auto index = findChessman(move->rowTo(), i);
                if (traceFailed(index)) return false;
            }
        }
        else if (move->columnFrom() > move->columnTo())
        {
            for (int i = move->columnFrom() - 1; i > move->columnTo(); i--) {
                auto index = findChessman(move->rowTo(), i);
                if (traceFailed(index)) return false;
            }
        }
    }

    return true;
}

void LogicController::moveNext(ChessMove *move, bool fast)
{
    if(!isValidMove(move)) return;

    auto from = findChessman(move->rowFrom(), move->columnFrom());
    auto to = findChessman(move->rowTo(), move->columnTo());

    AbstractFigure *figureFrom = qobject_cast<AbstractFigure*>(m_chessman[from]);
    if(figureFrom == 0) return;

    AbstractFigure *figureTo = qobject_cast<AbstractFigure*>(m_chessman[to]);
    if(figureTo == 0) return;

    move->setPrevFigure(figureTo->figure());
    move->setPrevSide(figureTo->side());

    figureFrom->setRow(move->rowTo());
    figureFrom->setColumn(move->columnTo());
    m_chessman[to] = figureFrom;
    m_chessman[from] = new AbstractFigure(move->rowFrom(), move->columnFrom(), false, this);

    if(!fast)
    emit chessmanChanged();
}

void LogicController::movePrev(ChessMove *move)
{
    if(!isValidMove(move, true)) return;

    auto to = findChessman(move->rowFrom(), move->columnFrom());
    auto from = findChessman(move->rowTo(), move->columnTo());

    AbstractFigure *figureFrom = qobject_cast<AbstractFigure*>(m_chessman[from]);
    if(figureFrom == 0) return;

    figureFrom->setRow(move->rowFrom());
    figureFrom->setColumn(move->columnFrom());
    m_chessman[to] = figureFrom;
    m_chessman[from] = new AbstractFigure(move->rowTo(), move->columnTo()
                              , (t_Side)move->prevSide(), (t_Figure)move->prevFigure(), this);

    emit chessmanChanged();
}
