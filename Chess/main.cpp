#include "logiccontroller.h"
#include "model/abstractfigure.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QtQml>






int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<LogicController>("Logic", 1, 0, "Logic");
    qmlRegisterType<AbstractFigure>("Figure", 1, 0, "Figure");

    QQmlApplicationEngine engine;
    LogicController controller;
    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("controller", &controller);
    engine.load(QUrl(QStringLiteral("qrc:/chess.qml")));

    return app.exec();
}
