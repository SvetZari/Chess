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
        qDebug() << "cur" << m_current;
        for (int i = 0; i < m_chessmoves.count(); i++) {
           qDebug() << "next move" << m_chessmoves[i]->rowFrom()
                    << m_chessmoves[i]->rowTo()
                    << m_chessmoves[i]->columnFrom()
                    << m_chessmoves[i]->columnTo();
        }

        }
    }



    {





            return;










        emit chessmanChanged();
    }

    const QString m_gamesave
        = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/gamesave.hss";
};

#endif // LOGICCONTROLLER_H
