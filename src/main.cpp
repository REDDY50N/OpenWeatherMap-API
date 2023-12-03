// Qt
#include <QCoreApplication>
#include <QDebug>
#include <QCommandLineParser>
#include <QProcessEnvironment>
#include <memory>

// API
#include "weatherapi.h"
#include "SysTray.h"

#include <QApplication>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QMessageBox>
#include "ExperimentalSysTray.h"
#include "weatherapi.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(systray);

    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(nullptr, QObject::tr("Warning"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    WeatherAPI owm;
    owm.printApiKey();
    owm.printJsonDataWeather("Feankfurt", "DE");


    ExperimentalSysTray test_tray;
    test_tray.show();
    return app.exec();
}

#else

#include <QLabel>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString text("QSystemTrayIcon is not supported on this platform");

    QLabel *label = new QLabel(text);
    label->setWordWrap(true);

    label->show();
    qDebug() << text;

    app.exec();
}

#endif


/*
int main(int argc, char *argv[])
{
    //QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("OpenWheaterMap-API-Test");
    QCoreApplication::setApplicationVersion("1.0.0");

    SysTray app(argc, argv);
    app.runLoop();

    return QCoreApplication::exec();
}
*/