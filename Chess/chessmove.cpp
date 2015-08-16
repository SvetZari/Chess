#include "chessmove.h"

int ChessMove::rowTo() {
    return m_rowTo;
}

int ChessMove::rowFrom() {
    return m_rowFrom;
}

int ChessMove::columnTo() {
    return m_columnTo;
}

int ChessMove::columnFrom() {
    return m_columnFrom;
}

int ChessMove::figure() {
    return m_figure;
}

int ChessMove::side() {
    return m_side;
}

void ChessMove::setRowTo(int rowTo) {
    m_rowTo = rowTo;
    emit rowToChanged();
}

void ChessMove::setRowFrom(int rowFrom) {
    m_rowFrom = rowFrom;
    emit rowFromChanged();
}

void ChessMove::setColumnTo(int columnTo) {
    m_columnTo = columnTo;
    emit columnToChanged();
}

void ChessMove::setColumnFrom(int columnFrom) {
    m_columnFrom = columnFrom;
    emit columnFromChanged();
}

void ChessMove::setFigure(int figure) {
    m_figure = figure;
    emit figureChanged();
}

void ChessMove::setSide(int side) {
    m_side = side;
    emit sideChanged();
}

bool ChessMove::invalid() {
    return (m_rowTo < 0 || m_columnTo < 0
            || m_rowFrom < 0 || m_columnFrom < 0);
}

bool ChessMove::moved() {
    return (rowFrom() != rowTo()) || (columnFrom() != columnTo());
}

void ChessMove::clear()
{
    m_rowFrom = -1;
    m_rowTo = -1;
    m_columnFrom = -1;
    m_columnTo = -1;
    m_figure = -1;
    m_side = -1;
}

bool ChessMove::allowed()
{
    if(!moved() || invalid())
        return false;

    switch (m_figure)
    {
        case t_Figure::Pawn: {
            return ((distance(Left) <= 1 && distance(Right) <= 1)
                    && ((distance(Top) == 1 && side() == t_Side::White)
                        || (distance(Bottom) == 1 && side() == t_Side::Black)))

                    || ((distance(Left) <= 0 && distance(Right) <= 0)
                        && ((side() == t_Side::White) && (rowFrom() == MAX_ROWS - 2) && distance(Top) == 2)
                        || ((side() == t_Side::Black) && (rowFrom() == 1) && distance(Bottom) == 2));
        }

        case t_Figure::Rook: {
            return (distance(Top) == 0 || distance(Bottom) == 0
                    || distance(Left) == 0 || distance(Right) == 0);
        }

        case t_Figure::Bishop: {
            return (distance(TopLeft) > 0 || distance(TopRight) > 0
                    || distance(BottomLeft) > 0 || distance(BottomRight) > 0);
        }

        case t_Figure::Queen: {
            return (distance(Top) == 0 || distance(Bottom) == 0
                    || distance(Right) == 0 || distance(Left) == 0
                    || distance(TopLeft) > 0 || distance(TopRight) > 0
                    || distance(BottomLeft) > 0 || distance(BottomRight) > 0);
        }

        case t_Figure::King: {
            return (distance(Top) <= 1 && distance(Bottom) <= 1
                    && distance(Left) <= 1 && distance(Right) <= 1);
        }

        case t_Figure::Knight: {
            return (((distance(Top) + distance(Right)) == 3 && distance(Top) > 0 && distance(Right) > 0)
                    || ((distance(Top) + distance(Left)) == 3 && distance(Top) > 0 && distance(Left) > 0)
                    || ((distance(Bottom) + distance(Right)) == 3 && distance(Bottom) > 0 && distance(Right) > 0)
                    || ((distance(Bottom) + distance(Left)) == 3 && distance(Bottom) > 0 && distance(Left) > 0));
        }
        default: return false;
    }
    return true;
}

int ChessMove::distance(ChessMove::Direction direction)
{
    auto top = rowFrom() - rowTo();
    auto bottom = rowTo() - rowFrom();
    auto right = columnFrom() - columnTo();
    auto left = columnTo() - columnFrom();

    switch (direction)
    {
        case Top: return top;
        case Bottom: return bottom;
        case Right: return right;
        case Left: return left;

        case TopLeft: return (top == left) ? top : 0;
        case TopRight: return (top == right) ? top : 0;
        case BottomLeft: return (bottom == left) ? bottom : 0;
        case BottomRight: return (bottom == right) ? bottom : 0;
    }
}
