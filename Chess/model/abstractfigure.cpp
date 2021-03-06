#include "abstractfigure.h"

AbstractFigure::AbstractFigure(QObject *parent) :
    m_row(-1), m_column(-1), m_side(None), m_figure(Empty), QObject(parent) {
}

AbstractFigure::AbstractFigure(int row, int column, bool initialize, QObject *parent) :
    m_row(row), m_column(column), m_side(None), m_figure(Empty), QObject(parent) {
    if(initialize) init();
}

AbstractFigure::AbstractFigure(int row, int column, Side side, Figure figure, QObject *parent) :
    m_row(row), m_column(column), m_side(side), m_figure(figure), QObject(parent) {
    init();
}

int AbstractFigure::row() const {
    return m_row;
}

int AbstractFigure::column() const {
    return m_column;
}

void AbstractFigure::setRow(int row) {
    m_row = row;
    emit rowChanged();
}

void AbstractFigure::setColumn(int column) {
    m_column = column;
    emit columnChanged();
}

AbstractFigure::Side AbstractFigure::side() {
    return m_side;
}

AbstractFigure::Figure AbstractFigure::figure() {
    return m_figure;
}

// 1 king, 1 queen, 2 rook, 2 bishop, 2 knight, 8 pawn
void AbstractFigure::init()
{
    if(m_row == 0 || m_row == 1)
        m_side = Side::Black;
    else if(m_row == MAX_ROWS - 1 || m_row == MAX_ROWS - 2)
        m_side = Side::White;
    else return;

    if(m_row == 1 || m_row == MAX_ROWS - 2)
        m_figure = Figure::Pawn;
    else {
        if(m_column == 0 || m_column == MAX_COLUMNS - 1)
            m_figure = Figure::Rook;
        else if(m_column == 1 || m_column == MAX_COLUMNS - 2)
            m_figure = Figure::Knight;
        else if(m_column == 2 || m_column == MAX_COLUMNS - 3)
            m_figure = Figure::Bishop;
        else if(m_column == 3)
            m_figure = Figure::Queen;
        else if(m_column == 4)
            m_figure = Figure::King;
        else return;
    }
}
