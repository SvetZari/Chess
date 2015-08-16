#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include "model/defines.h"
#include "model/abstractfigure.h"
#include "chessmove.h"

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
    QList<QObject*> chessman();
    QObject* currentmove();

    bool allowed(QObject *move);
    void initChessman();
    void setCurrentMove(QObject *move);
    void clear();

    void saveGame(QString path)
    {

    }

    void loadGame(QString path)
    {

    }

private:
    QList<QObject*> m_chessman;
    ChessMove* m_currentmove;
    QList<ChessMove*> m_chessmoves;

    int index(const int row, const int column);
    int findChessMan(const int row, const int column);
    void moveChessMan();
};

#endif // LOGICCONTROLLER_H
