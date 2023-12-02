// Qt
#include <QCoreApplication>
#include <QDebug>
#include <QCommandLineParser>
#include <QProcessEnvironment>
#include <memory>

// API
#include "weatherapi.h"
#include "SysTray.h"

int main(int argc, char *argv[])
{
    //QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("OpenWheaterMap-API-Test");
    QCoreApplication::setApplicationVersion("1.0.0");

    SysTray app(argc, argv);
    app.runLoop();


    WeatherAPI w;
    QString city = "Neu-Isenburg";
    QString country_code = "DE";

    w.getTemperature( city, country_code );
    w.getTempMin( city, country_code );
    w.getTempMax( city, country_code );
    w.getFeelsLike( city, country_code );
    w.getHumidity( city, country_code );
    w.getWindSpeed(city, country_code);
    w.getWindDeg( city, country_code );
    w.getWeatherStatus( city, country_code );
    w.getCloudCoverage( city, country_code );

    w.getSunriseTime( city, country_code );
    w.getPressure( city, country_code );

    w.getCoordLong( city, country_code );
    w.printJsonDataOneCall("50.05", "8.69");


    QString apiKey = QProcessEnvironment::systemEnvironment().value("OWM_API_KEY");

    if (!apiKey.isEmpty()) {
        qDebug() << "API_KEY gefunden:" << apiKey;
        // Hier kannst du den API_KEY in deiner Anwendung verwenden
    } else {
        qDebug() << "API_KEY nicht gefunden.";
        // Behandle den Fall, wenn der API_KEY nicht vorhanden ist
    }

    return QCoreApplication::exec();
}
