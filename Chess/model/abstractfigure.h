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
    explicit AbstractFigure();
    explicit AbstractFigure(int row, int column, bool initialize = false);

    enum Figure { Empty = -1, King, Queen, Rook, Bishop, Knight, Pawn };
    enum Side { None = -1, White, Black };

signals:
    void columnChanged();
    void rowChanged();
    void sideChanged();
    void figureChanged();

public slots:
    int row() const;
    int column() const;
    void setRow(int row);
    void setColumn(int column);
    Side side();
    Figure figure();
    void init();

private:
    Side m_side;
    Figure m_figure;
    int m_row;
    int m_column;
};

typedef AbstractFigure::Side t_Side;
typedef AbstractFigure::Figure t_Figure;

#endif // ABSTRACTFIGURE_H
