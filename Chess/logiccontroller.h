#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include "model/abstractfigure.h"

#include <QDebug>
#include <QObject>
#include <QQmlEngine>
#include <QQmlListProperty>

class AbstractFigure;

class LogicController : public QObject
{
    Q_OBJECT

    Q_ENUMS(Figure)
    Q_ENUMS(Side)
    Q_PROPERTY(QList<QObject*> chessman READ chessman NOTIFY chessmanChanged)

    const int MaxRow = 8;
    const int MaxColumn = 8;
    const int MaxIndex = MaxRow * MaxColumn;

public:
    enum Figure { None, King, Queen, Rook, Bishop, Knight, Pawn };
    enum Side { White, Black };

    explicit LogicController(QObject *parent = 0)
        : QObject(parent) {
        initChessman();
    }

signals:
    void chessmanChanged();

public slots:

    void logMove(int row, int column, Figure figure, Side side) {
    }

    void isAllowed(int row, int column, Figure figure, Side side) {
    }

    void initChessman()
    {
        m_chessman.clear();
        for (int column = 0; column < MaxRow; column++) {
            for (int row = 0; row < MaxColumn; row++) {
                m_chessman.append(new AbstractFigure(row,column));
            }
        }
    }


    QList<QObject*> chessman() {
        return m_chessman;
    }


private:
    QList<QObject*> m_chessman;

    int index (int row, int column) {
        return column + (row * MaxColumn);
    }
};

#endif // LOGICCONTROLLER_H
