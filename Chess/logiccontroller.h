#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include "model/defines.h"
#include "model/abstractfigure.h"
#include "chessmove.h"

#include <algorithm>

#include <QDebug>
#include <QObject>
#include <QQmlEngine>
#include <QQmlListProperty>

class LogicController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject*> chessman READ chessman NOTIFY chessmanChanged)
    Q_PROPERTY(QObject* currentmove READ currentmove WRITE setCurrentMove NOTIFY currentmoveChanged)

public:
    explicit LogicController(QObject *parent = 0)
        : QObject(parent) {
        initChessman();
        m_currentmove = new ChessMove();
    }

signals:
    void chessmanChanged();
    void currentmoveChanged();

public slots:
    bool allowed(QObject *move) {
        ChessMove *chessmove = qobject_cast<ChessMove*>(move);
        if(chessmove != 0) {

            return chessmove->allowed();
        }
    }

    void initChessman()
    {
        m_chessman.clear();
        for (int row = 0; row < MAX_ROWS; row++) {
            for (int column = 0; column < MAX_COLUMNS; column++) {
                m_chessman.append(new AbstractFigure(row,column,true));
            }
        }
    }


    QList<QObject*> chessman() {
        return m_chessman;
    }

    QObject* currentmove() {
        return m_currentmove;
    }

    void setCurrentMove(QObject *move) {
        ChessMove *chessmove = qobject_cast<ChessMove*>(move);
        if(chessmove != 0) {
            m_currentmove = chessmove;
            qDebug() << "new pos" << chessmove->rowTo() << chessmove->columnTo() << chessmove->figure() << chessmove->side();

            moveChessMan();

            emit currentmoveChanged();
            emit chessmanChanged();

        }
    }


private:
    QList<QObject*> m_chessman;
    ChessMove* m_currentmove;
    QList<ChessMove*> m_chessmoves;

    int index (const int row, const int column);
    int findChessMan(const int row, const int column);
    void moveChessMan();
};

#endif // LOGICCONTROLLER_H
