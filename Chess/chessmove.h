#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include "model/abstractfigure.h"

#include <QObject>

class ChessMove : public QObject
{
    Q_OBJECT
public:
    explicit ChessMove(QObject *parent = 0) : QObject(parent) {
        clear();
    }

    Q_PROPERTY(int rowTo READ rowTo WRITE setRowTo NOTIFY rowToChanged)
    Q_PROPERTY(int columnTo READ columnTo WRITE setColumnTo NOTIFY columnToChanged)
    Q_PROPERTY(int rowFrom READ rowFrom WRITE setRowFrom NOTIFY rowFromChanged)
    Q_PROPERTY(int columnFrom READ columnFrom WRITE setColumnFrom NOTIFY columnFromChanged)
    Q_PROPERTY(int side READ side WRITE setSide NOTIFY figureChanged)
    Q_PROPERTY(int figure READ figure WRITE setFigure NOTIFY sideChanged)

    enum Direction {Top, Bottom, Right, Left, TopRight, TopLeft, BottomRight, BottomLeft};

signals:
    void rowToChanged();
    void columnToChanged();
    void rowFromChanged();
    void columnFromChanged();
    void figureChanged();
    void sideChanged();

public slots:
    int rowTo();
    int rowFrom();
    int columnTo();
    int columnFrom();
    int figure();
    int side();

    void setRowTo(int rowTo);
    void setRowFrom(int rowFrom);
    void setColumnTo(int columnTo);
    void setColumnFrom(int columnFrom);
    void setFigure(int figure);
    void setSide(int side);

    bool invalid();
    void clear();
    bool moved();
    bool allowed();

private:
    int m_rowFrom;
    int m_columnFrom;
    int m_rowTo;
    int m_columnTo;
    int m_figure;
    int m_side;

    int distance(Direction direction);
};

#endif // CHESSMOVE_H
