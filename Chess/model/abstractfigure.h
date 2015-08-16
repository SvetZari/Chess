#ifndef ABSTRACTFIGURE_H
#define ABSTRACTFIGURE_H

#include "model/defines.h"

#include <QObject>
#include <QDebug>

class AbstractFigure : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int row READ row WRITE setRow NOTIFY rowChanged)
    Q_PROPERTY(int column READ column WRITE setColumn NOTIFY columnChanged)
    Q_PROPERTY(int side READ side NOTIFY sideChanged)
    Q_PROPERTY(int figure READ figure NOTIFY figureChanged)

    Q_ENUMS(Figure)
    Q_ENUMS(Side)
public:
    explicit AbstractFigure() {
        m_row = -1;
        m_column = -1;
        m_side = None;
        m_figure = Empty;
    }

    explicit AbstractFigure(int row, int column, bool newGame = false) {
        m_row = row;
        m_column = column;
        m_side = None;
        m_figure = Empty;
        if(newGame) init();
    }

    enum Figure { Empty = -1, King, Queen, Rook, Bishop, Knight, Pawn };
    enum Side { None = -1, White, Black };

signals:
    void columnChanged();
    void rowChanged();
    void sideChanged();
    void figureChanged();

public slots:

    int row() const {
        return m_row;
    }

    int column() const {
        return m_column;
    }

    void setRow(int row) {
        m_row = row;
        emit rowChanged();
    }

    void setColumn(int column) {
       m_column = column;
       emit columnChanged();
    }

    Side side() {
        return m_side;
    }

    Figure figure() {
        return m_figure;
    }

    // 1 king, 1 queen, 2 rook, 2 bishop, 2 knight, 8 pawn
    void init() {
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

private:
    Side m_side;
    Figure m_figure;
    int m_row;
    int m_column;
};

typedef AbstractFigure::Side t_Side;
typedef AbstractFigure::Figure t_Figure;

#endif // ABSTRACTFIGURE_H
