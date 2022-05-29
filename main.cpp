// Qt
#include <QCoreApplication>
#include <QDebug>
#include <QCommandLineParser>
#include <memory>

// API
#include "weatherapi.h"




int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("OpenWheaterMap-API-Test");
    QCoreApplication::setApplicationVersion("1.0.0");

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

    return app.exec();
}
