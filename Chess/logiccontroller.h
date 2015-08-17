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

    void processNextMove() {
        if(m_chessmoves.count() >= m_current) {
            moveChessMan(m_chessmoves.at(m_current));
            m_current++;
        }
    }

    void processPrevMove() {

    }

    void saveGame()
    {
        QFile file(m_gamesave);
        auto result = file.open(QIODevice::ReadWrite);
        if(!result) {
            qDebug() << "Something wrong. Can't open file.";
            return;
        }

        file.resize(0);
        QDataStream dataStream(&file);

        int count = m_chessmoves.count();
        dataStream << count;

        foreach (const ChessMove* move, m_chessmoves)
            dataStream << *move;

        file.flush();
        file.close();
    }

    void loadGame()
    {
        QFile file(m_gamesave);
        if(!file.exists()) {
            qDebug() << "Something wrong. File doesn't exist.";
            return;
        }

        auto result = file.open(QFile::ReadOnly);
        if(!result) {
            qDebug() << "Something wrong. Can't open file.";
            return;
        }

        m_chessmoves.clear();
        m_chessman.clear();
        QDataStream dataStream(&file);

        int count;
        dataStream >> count;

        for (int i = 0; i < count; i++) {
            ChessMove move;
            dataStream >> move;
            m_chessmoves.append(&move);
        }

        file.close();

        initChessman();

        processNextMove();
    }

private:
    QList<QObject*> m_chessman;
    QList<ChessMove*> m_chessmoves;
    int m_current = 0;

    int index(const int row, const int column);
    int findChessMan(const int row, const int column);
    void moveChessMan(ChessMove *move);

    const QString m_gamesave
        = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/gamesave.hss";
};

#endif // LOGICCONTROLLER_H
