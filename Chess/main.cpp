#include "logiccontroller.h"
#include "model/chessmove.h"
#include "model/abstractfigure.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QtQml>

void initQmlTypes()
{
    qmlRegisterType<LogicController>("Chess.Logic", 1, 0, "Logic");
    qmlRegisterType<AbstractFigure>("Chess.Figure", 1, 0, "Figure");
    qmlRegisterType<ChessMove>("Chess.Move", 1, 0, "Move");
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    initQmlTypes();
    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();

    LogicController controller;
    ctx->setContextProperty("controller", &controller);
    engine.load(QUrl(QStringLiteral("qrc:/qml/ui/chess.qml")));

    return app.exec();
}
