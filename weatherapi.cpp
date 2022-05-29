#include "weatherapi.h"

// Qt
#include <QTypeInfo>

// Network
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

// JSON
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>
#include <QEventLoop>

// Files & Directories
#include <QFile>
#include <QDir>

#include <QObject>



// ==============================================
// CTOR
// ==============================================
WeatherAPI::WeatherAPI()
{
    loadApiKey();
}
// ==============================================
// DTOR
// ==============================================
WeatherAPI::~WeatherAPI()
{

}

// ==============================================
// INITIALIZE
// ==============================================
QString WeatherAPI::loadApiKey()
{
    QByteArray apikey;

    // Note:
    // read api-key from textfile in bin/ (where the executeable is located)
    // cuz we don't have QSettings implemented yet
    QString filepath = QDir::currentPath().append("/apikey.txt");

    QFile file( filepath );
    qDebug() << filepath;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "API-Key file not open or wrong format!";

    while ( !file.atEnd() )
    {
        apikey = file.readLine().data();
        qDebug() << "API-Key:" << apikey.simplified();
    }
    m_apiKey = QString( apikey.simplified() );

return apikey;
}

// ==============================================
// DATA REQUEST
// ==============================================
/*
 *      Call Weather Data only with City
 *      http://api.openweathermap.org/data/2.5/weather?q=Neu-Isenburg,DE&APPID=<api-key>&lang=german
 *      @param: city + city_code i.e. "Neu-Isenburg","DE"
 */
QByteArray WeatherAPI::getWeatherData( QString city, QString country_code )
{
    QUrl weatherCall = QUrl( "http://api.openweathermap.org/data/2.5/weather?q="+city+","+country_code+"&APPID="+m_apiKey+"&lang="+m_language+"&units="+m_units );
    QNetworkRequest request( weatherCall );

    QByteArray data;
    QEventLoop eventLoop; // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager qnam;
    QObject::connect( &qnam, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()) );
    QNetworkReply *reply = qnam.get( request );
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError)
    {
        data = reply->readAll();
        //delete reply;
        reply->deleteLater();
    }
    else
    {
        qDebug() << "Reply failed: " <<reply->errorString();
        delete reply;
    }

    return data;
}

/*
 *      Get whole data in one call (incl. forecast) with Latitude & Longitude
 *      "https://api.openweathermap.org/data/2.5/onecall?lat=50.13489&lon=8.45121&appid=<api-key>"
 */
QString WeatherAPI::getOneCallData( QString latitude, QString longitude )
{
    QUrl onecall_url = QUrl("https://api.openweathermap.org/data/2.5/onecall?lat="+latitude+"&"+longitude+"&appid="+m_apiKey+"&lang="+m_language+"&units="+m_units );
    QNetworkRequest request( onecall_url );

    QString data;
    QEventLoop eventLoop; // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager qnam;
    QObject::connect( &qnam, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()) );
    QNetworkReply *reply = qnam.get( request );
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError)
    {
        data = (QString)reply->readAll();
        delete reply;
    }
    else
    {
        qDebug() << "Reply failed: " <<reply->errorString();
        delete reply;
    }
    return data;
}


// ==============================================
// PARSE JSON
// ==============================================
double WeatherAPI::analyzeData( QByteArray data, QString rootkey, QString subkey )
{
    double value = 0;

    // json
    QJsonDocument jsonData = QJsonDocument::fromJson ( data );
    QJsonObject root = jsonData.object();
    QJsonValue subVal = root.value( rootkey );
    QJsonObject subObj = subVal.toObject();

    // value
    if ( subObj.contains( subkey ) && subObj[ subkey ].isDouble() )
        value = subObj[ subkey ].toDouble();
    else
        qDebug() << "No valid data!";

    return value;
}

// ==============================================
// GET SINGLE VALUES
// ==============================================
double WeatherAPI::getTemperature(QString city, QString country_code)
{
    QByteArray data = getWeatherData( city, country_code );
    m_temp = analyzeData( data, "main", "temp" );
    qDebug() << "Temperatur: " << m_temp << "°C";
    return m_temp;
}

double WeatherAPI::getTempMin(QString city, QString country_code)
{
    QByteArray data = getWeatherData( city, country_code );
    m_tempMin = analyzeData( data, "main", "temp_min" );
    qDebug() << "Temperatur (min): " << m_tempMin << "°C";
    return m_tempMin;
}

double WeatherAPI::getTempMax(QString city, QString country_code)
{
    QByteArray data = getWeatherData( city, country_code );
    m_tempMax = analyzeData( data, "main", "temp_max" );
    qDebug() << "Temperatur (max): " << m_tempMax << "°C";
    return m_tempMax;
}

double WeatherAPI::getFeelsLike(QString city, QString country_code)
{
    QByteArray data = getWeatherData( city, country_code );
    m_feelslike = analyzeData( data, "main", "feels_like" );
    qDebug() << "Temperatur (gefühlt): " << m_feelslike << "°C";
    return m_feelslike;
}

double WeatherAPI::getHumidity(QString city, QString country_code)
{
    QByteArray data = getWeatherData( city, country_code );
    m_humidity = analyzeData( data, "main", "humidity" );
    qDebug() << "Luftfeuchte: " << m_humidity << "%";
    return m_humidity;
}

int WeatherAPI::getPressure(QString city, QString country_code)
{
    QByteArray data = getWeatherData( city, country_code );
    m_pressure = analyzeData( data, "main", "pressure" );
    qDebug() << "Luftdruck: " << m_pressure << "°";
    return m_pressure;
}

int WeatherAPI::getWindSpeed(QString city, QString country_code)
{
    QByteArray data = getWeatherData( city, country_code );
    m_windspeed = analyzeData( data, "wind", "speed" );
    qDebug() << "Windgeschwindigkeit: " << m_windspeed << "m/s";
    return m_windspeed;
}

int WeatherAPI::getWindDeg(QString city, QString country_code)
{
    QByteArray data = getWeatherData( city, country_code );
    m_winddeg = analyzeData( data, "wind", "deg" );
    qDebug() << "Windrichtung: " << m_winddeg << "°";
    return m_winddeg;
}


int WeatherAPI::getSunriseTime(QString city, QString country_code)
{
    QByteArray data = getWeatherData( city, country_code );
    m_sunrise = analyzeData( data, "sys", "sunrise" );
    qDebug() << "Sonnenaufgang: " << m_sunrise << "°";
    return m_sunrise;
}

double WeatherAPI::getWeatherStatus(QString city, QString country_code)
{    QByteArray data = getWeatherData( city, country_code );
     m_status = analyzeData( data, "weather", "main" );
     qDebug() << "Status: " << m_status << QString(u8"\u2614") << QString(u8"\u2601") << QString(u8"\u2600") << QChar(0x4FF0) << "🌑" << "";
     return m_status;

     // https://unicode-table.com/en/emoji/travel-and-places/sky-and-weather/
}

int WeatherAPI::getCloudCoverage(QString city, QString country_code)
{    QByteArray data = getWeatherData( city, country_code );
     m_clouds = analyzeData( data, "clouds", "all" );
     qDebug() << "Clouds: " << m_clouds << "%";
     return m_clouds;
}


















