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

    // DebugPrints
    void printJsonDataWeather( QString city, QString country_code );
    void printJsonDataOneCall( QString latitude, QString longitude );

    // analyze JSON
    auto analyzeData1st( QByteArray data, QString rootkey );
    auto analyzeData( QByteArray data, QString rootkey, QString subkey );


    // single data values
    double getCoordLong( QString city, QString country_code );
    double getCoordLat( QString city, QString country_code );

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

    void printApiKey();

private:
    // member var's
    QNetworkAccessManager m_qnam;
    QUrl m_requestURL;
    QString m_apiKey;
    QString m_language = "german";
    QString m_units = "metric";
    QString m_longitude = "50.0522076"; // Längengrad
    QString m_latitude = "8.6952638";  // Breitengrad
    QString m_city = "Neu-Isenburg";
    QString m_countryCode = "DE";

    QString lat = "50.3245";
    QString lon = "8.3245";



    /*!
     * Call current weather data
     * https://openweathermap.org/current
     *
     * Parameter:
     * lat 	    required 	Latitude. If you need the geocoder to automatic convert city names and zip-codes to geo coordinates and the other way around, please use our Geocoding API
     * lon 	    required 	Longitude. If you need the geocoder to automatic convert city names and zip-codes to geo coordinates and the other way around, please use our Geocoding API
     * appid 	required 	API key
     * mode 	optional 	Response format: XML, HTML, JSON (default)
     * units 	optional 	Units of measurement. standard, metric and imperial units are available.
     * lang 	optional 	output in your language */
    //QUrl currentWeatherDataByCoord = QUrl("https://api.openweathermap.org/data/2.5/weather?lat={lat}&lon={lon}&appid={API key}");
    QUrl m_currentWeatherDataByCoord = QUrl("https://api.openweathermap.org/data/2.5/weather?lat=" + m_latitude + "&lon=" + m_longitude + "&appid=" + m_apiKey);


    /*!
     *  Call current weather data (geocoding api)
     *  https://openweathermap.org/api/geocoding-api
     *
     * Parameter:
     * q 	    required 	City name, state code (only for the US) and country code divided by comma. Please use ISO 3166 country codes.
     * appid 	required 	API key
     * limit 	optional 	Number of the locations in the API response (up to 5 results can be returned in the API response)  */
    //QUrl m_currentWeatherDataByCity = QUrl("http://api.openweathermap.org/geo/1.0/direct?q={city name},{state code},{country code}&limit={limit}&appid={API key}");
    QUrl m_currentWeatherDataByCity = QUrl("http://api.openweathermap.org/data/2.5/weather?q=" + m_city + "," + m_countryCode + "&APPID=" + m_apiKey + "&lang=" + m_language + "&units=" + m_units);

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
