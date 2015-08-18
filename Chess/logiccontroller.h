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
        if(m_chessmoves.count() > m_currentMove) {
            moveChessNext(m_chessmoves.at(m_currentMove));
            m_currentMove++;
        }
    }

    void processPrevMove() {
        if(m_currentMove > 0) {
            m_currentMove--;
            moveChessPrev(m_chessmoves.at(m_currentMove));
        }
    }

    void saveGame();
    void loadGame();

private:
    QList<QObject*> m_chessman;
    QList<ChessMove*> m_chessmoves;
    int m_currentMove = 0;

    int index(const int row, const int column);
    int findChessMan(const int row, const int column);
    void moveChessNext(ChessMove *move)
    {
        auto from = findChessMan(move->rowFrom(), move->columnFrom());
        auto to = findChessMan(move->rowTo(), move->columnTo());

        qDebug() << "from " << from << "to" << to;

        if(from == to) return;

        AbstractFigure *figureTo = qobject_cast<AbstractFigure*>(m_chessman[to]);
        if(figureTo == 0) return;

        AbstractFigure *figureFrom = qobject_cast<AbstractFigure*>(m_chessman[from]);
        if(figureFrom == 0) return;

        if(figureFrom->side() == figureTo->side())
            return;

        m_chessman[to] = new AbstractFigure(move->rowTo(), move->columnTo(), (t_Side)move->side(), (t_Figure)move->figure());
        m_chessman[from] = new AbstractFigure(move->rowFrom(), move->columnFrom());

        emit chessmanChanged();
    }

    void moveChessPrev(ChessMove *move)
    {
        auto to = findChessMan(move->rowFrom(), move->columnFrom());
        auto from = findChessMan(move->rowTo(), move->columnTo());

        qDebug() << "from " << from << "to" << to;

        if(from == to) return;

        AbstractFigure *figureTo = qobject_cast<AbstractFigure*>(m_chessman[to]);
        if(figureTo == 0) return;

        AbstractFigure *figureFrom = qobject_cast<AbstractFigure*>(m_chessman[from]);
        if(figureFrom == 0) return;

        if(figureFrom->side() == figureTo->side())
            return;

        m_chessman[to] = new AbstractFigure(move->rowFrom(), move->columnFrom(), (t_Side)move->side(), (t_Figure)move->figure());
        m_chessman[from] = new AbstractFigure(move->rowTo(), move->columnTo());

        emit chessmanChanged();
    }

    const QString m_gamesave
        = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/gamesave.hss";
};

#endif // LOGICCONTROLLER_H
