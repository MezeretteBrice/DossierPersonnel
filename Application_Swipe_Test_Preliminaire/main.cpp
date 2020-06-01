#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlEngine>
#include <QtQuick/QQuickView>
#include <QQmlContext>
#include "basebdd.h"
int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("Application_Swipe");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QIcon::setThemeName("Application_Swipe");
    QQmlApplicationEngine engine;
    BaseBDD * releve = new BaseBDD();

    engine.rootContext()->setContextProperty("BaseBDD", releve);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();

    /*QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
    QGuiApplication application(argc, argv);
       QQuickView view;
       view.setSource(QUrl("qrc:/corkboards.qml"));
       view.setResizeMode(QQuickView::SizeRootObjectToView);
       view.show();
       return application.exec();*/
}
