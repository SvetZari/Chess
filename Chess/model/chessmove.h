#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include "abstractfigure.h"

#include <QObject>

class ChessMove : public QObject
{
    Q_OBJECT
public:
    explicit ChessMove(QObject *parent = 0) : QObject(parent) {
        clear();
    }

    explicit ChessMove(int rowFrom, int rowTo, int columnFrom, int columnTo,
                       int figure, int side, int prevFigure, int prevSide, QObject *parent = 0) :
        m_rowFrom(rowFrom), m_rowTo(rowTo), m_columnFrom(columnFrom)
      , m_columnTo(columnTo), m_figure(figure), m_side(side)
      , m_prevFigure(prevFigure), m_prevSide(prevSide), QObject(parent) {
    }

    Q_PROPERTY(int rowTo READ rowTo WRITE setRowTo NOTIFY rowToChanged)
    Q_PROPERTY(int columnTo READ columnTo WRITE setColumnTo NOTIFY columnToChanged)
    Q_PROPERTY(int rowFrom READ rowFrom WRITE setRowFrom NOTIFY rowFromChanged)
    Q_PROPERTY(int columnFrom READ columnFrom WRITE setColumnFrom NOTIFY columnFromChanged)
    Q_PROPERTY(int side READ side WRITE setSide NOTIFY figureChanged)
    Q_PROPERTY(int figure READ figure WRITE setFigure NOTIFY sideChanged)
    Q_PROPERTY(int prevSide READ prevSide WRITE setPrevSide NOTIFY prevFigureChanged)
    Q_PROPERTY(int prevFigure READ prevFigure WRITE setPrevFigure NOTIFY prevSideChanged)

    friend QDataStream &operator<<(QDataStream &data, const ChessMove &move);
    friend QDataStream &operator>>(QDataStream &data, ChessMove &move);

signals:
    void rowToChanged();
    void columnToChanged();
    void rowFromChanged();
    void columnFromChanged();
    void figureChanged();
    void sideChanged();
    void prevFigureChanged();
    void prevSideChanged();

public slots:
    int rowTo();
    int rowFrom();
    int columnTo();
    int columnFrom();
    int figure();
    int side();
    int prevFigure();
    int prevSide();

    void setRowTo(int rowTo);
    void setRowFrom(int rowFrom);
    void setColumnTo(int columnTo);
    void setColumnFrom(int columnFrom);
    void setFigure(int figure);
    void setSide(int side);
    void setPrevFigure(int figure);
    void setPrevSide(int side);

    bool invalid();
    void clear();
    bool moved();
    bool isAllowed();

private:
    int m_rowFrom;
    int m_columnFrom;
    int m_rowTo;
    int m_columnTo;
    int m_figure;
    int m_side;
    int m_prevFigure;
    int m_prevSide;

    enum Direction {Top, Bottom, Right, Left, TopRight, TopLeft, BottomRight, BottomLeft};

    int distance(Direction direction);
};

inline QDataStream &operator<<(QDataStream &data, const ChessMove &move) {
    data << move.m_rowFrom << move.m_rowTo
         << move.m_columnFrom << move.m_columnTo
         << move.m_figure << move.m_side
         << move.m_prevFigure << move.m_prevSide;
    return data;
}

inline QDataStream &operator>>(QDataStream &data, ChessMove &move) {
    data >> move.m_rowFrom >> move.m_rowTo
            >> move.m_columnFrom >> move.m_columnTo
            >> move.m_figure >> move.m_side
            >> move.m_prevFigure >> move.m_prevSide;;
    return data;
}

#endif // CHESSMOVE_H
