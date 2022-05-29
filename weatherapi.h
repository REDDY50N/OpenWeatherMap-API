#ifndef WEATHERAPI_H
#define WEATHERAPI_H

// #include <QObject>
#include <QtNetwork/QNetworkAccessManager>

class WeatherAPI
{
    //Q_OBJECT
public:
    WeatherAPI();
    ~WeatherAPI();

public:
    QString loadApiKey();

    // Requests
    QByteArray getWeatherData( QString city, QString country_code );
    QString getOneCallData( QString latitude, QString longitude );

    // analyze JSON
    double analyzeData( QByteArray data, QString rootkey, QString subkey );

    // single data values
    double getTemperature( QString city, QString country_code );
    double getTempMax( QString city, QString country_code );
    double getTempMin( QString city, QString country_code );
    double getFeelsLike( QString city, QString country_code );
    double getHumidity( QString city, QString country_code );

    int getWindSpeed( QString city, QString country_code );
    int getWindDeg( QString city, QString country_code );
    int getPressure( QString city, QString country_code );

    double getWeatherStatus( QString city, QString country_code );
    int getCloudCoverage( QString city, QString country_code );

    int getSunriseTime(QString city, QString country_code);
    int getSunsetTime(QString city, QString country_code);

private:
    // member var's
    QNetworkAccessManager m_qnam;
    QUrl m_requestURL;
    QString m_apiKey;
    QString m_language = "german";
    QString m_units = "metric";

    double m_temp;
    double m_tempMin;
    double m_tempMax;
    double m_humidity;
    double m_feelslike;
    double m_visibility;
    int m_pressure;

    double m_windspeed;
    double m_winddeg;


    double m_status;
    int m_clouds;

    int m_sunrise;
    int m_sunset;

};

#endif // WEATHERAPI_H
