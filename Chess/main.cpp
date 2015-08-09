#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QtQml>
#include "model/enums.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<ChessSide>("Side", 1, 0, "ChessSide");
    qmlRegisterType<ChessFigure>("Figure", 1, 0, "ChessFigure");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/chess.qml")));

    return app.exec();
}
