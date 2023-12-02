#ifndef OWM_API_APIKEYMANAGER_H
#define OWM_API_APIKEYMANAGER_H

#include <QString>
#include <QProcessEnvironment>
#include <QDebug>

#include "weatherapi.h"

class ApiKeyManager {
private:
    QString m_apiKey = QProcessEnvironment::systemEnvironment().value("API_KEY");

public:
    void checkApiKey() {
        if (!m_apiKey.isEmpty()) {
            qDebug() << "API_KEY gefunden:" << m_apiKey;
            // Hier kannst du den API_KEY in deiner Anwendung verwenden
        } else {
            qDebug() << "API_KEY nicht gefunden.";
            // Behandle den Fall, wenn der API_KEY nicht vorhanden ist
        }
    }

    void runWeatherTestCall() {
        WeatherAPI w;
        QString city = "Neu-Isenburg";
        QString country_code = "DE";

        w.getTemperature(city, country_code);
        w.getTempMin(city, country_code);
        w.getTempMax(city, country_code);
        w.getFeelsLike(city, country_code);
        w.getHumidity(city, country_code);
        w.getWindSpeed(city, country_code);
        w.getWindDeg(city, country_code);
        w.getWeatherStatus(city, country_code);
        w.getCloudCoverage(city, country_code);

        w.getSunriseTime(city, country_code);
        w.getPressure(city, country_code);

        w.getCoordLong(city, country_code);
        w.printJsonDataOneCall("50.05", "8.69");


    }

};


#endif //OWM_API_APIKEYMANAGER_H
