#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include "defines.h"
#include "model/abstractfigure.h"
#include "model/chessmove.h"

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
    explicit LogicController(QObject *parent = 0);

signals:
    void chessmanChanged();

public slots:
    QList<QObject*> chessman();

    bool allowed(QObject *move);
    void initChessman();
    void setCurrentMove(QObject *move);
    void clear();
    void processNextMove(bool fast = false);
    void processPrevMove();
    void saveGame();
    void loadGame();

private:
    QList<QObject*> m_chessman;
    QList<ChessMove*> m_chessmoves;
    int m_currentMove = 0;

    int index(const int row, const int column);
    int findChessman(const int row, const int column);
    bool isValidMove(ChessMove *move);
    bool isValidTrace(ChessMove *move);
    bool validateTrace(ChessMove *move);
    bool checkMoveParity(int side);

    void moveNext(ChessMove *move, bool fast = false);
    void movePrev(ChessMove *move);

    const QString m_gamesave
        = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/gamesave.hss";
};

#endif // LOGICCONTROLLER_H
