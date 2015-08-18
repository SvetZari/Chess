#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include "model/defines.h"
#include "model/abstractfigure.h"
#include "chessmove.h"

#include <QDebug>
#include <QObject>
#include <QFile>
#include <QStandardPaths>
#include <QQmlEngine>
#include <QQmlListProperty>

class LogicController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject*> chessman READ chessman NOTIFY chessmanChanged)

public:
    explicit LogicController(QObject *parent = 0)
        : QObject(parent) {
        initChessman();
    }

signals:
    void chessmanChanged();

public slots:
    QList<QObject*> chessman();

    bool allowed(QObject *move);
    void initChessman();
    void setCurrentMove(QObject *move);
    void clear();
    void processNextMove();
    void processPrevMove();
    void saveGame();
    void loadGame();

private:
    QList<QObject*> m_chessman;
    QList<ChessMove*> m_chessmoves;
    int m_currentMove = 0;

    int index(const int row, const int column);
    int findChessMan(const int row, const int column);
    bool checkMove(int from, int to);
    void moveChessNext(ChessMove *move);
    void moveChessPrev(ChessMove *move);

    const QString m_gamesave
        = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/gamesave.hss";
};

#endif // LOGICCONTROLLER_H
