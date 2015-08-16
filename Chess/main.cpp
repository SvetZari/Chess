#include "logiccontroller.h"
#include "model/abstractfigure.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QtQml>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("controller", &controller);
    engine.load(QUrl(QStringLiteral("qrc:/chess.qml")));

    return app.exec();
}
