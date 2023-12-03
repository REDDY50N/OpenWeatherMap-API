#include "weatherapi.h"

// Qt
#include <QTypeInfo>
#include <QProcessEnvironment>

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
#include <QSettings>


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
    /*
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
    */

    m_apiKey = QProcessEnvironment::systemEnvironment().value("OWM_API_KEY");

    if (m_apiKey.isEmpty()) {
        // API_KEY nicht in Umgebungsvariablen gefunden, versuche es in QSettings
        QSettings settings("MyCompany", "MyApp"); // Hier sollte "MyCompany" durch den Namen Ihres Unternehmens und "MyApp" durch den Namen Ihrer Anwendung ersetzt werden

        // Lese den API-Key aus den QSettings
        m_apiKey = settings.value("api_key").toString();

        if (m_apiKey.isEmpty()) {
            qDebug() << "API_KEY nicht in Umgebungsvariablen oder QSettings gefunden.";
            // Behandle den Fall, wenn der API_KEY nicht vorhanden ist
            // Hier können Sie beispielsweise eine Benutzeroberfläche öffnen, um den API-Key einzugeben und zu speichern
        } else {
            qDebug() << "API_KEY aus QSettings gefunden:" << m_apiKey;
            // Hier kannst du den API_KEY in deiner Anwendung verwenden
        }
    } else {
        qDebug() << "API_KEY aus Umgebungsvariablen gefunden:" << m_apiKey;
        // Hier kannst du den API_KEY in deiner Anwendung verwenden
    }


    m_apiKey = QProcessEnvironment::systemEnvironment().value("OWM_API_KEY");
    if (!m_apiKey.isEmpty()) {
        qDebug() << "API_KEY gefunden:" << m_apiKey;
        // Hier kannst du den API_KEY in deiner Anwendung verwenden
    } else {
        qDebug() << "API_KEY nicht gefunden.";
        // Behandle den Fall, wenn der API_KEY nicht vorhanden ist
    }

    return m_apiKey;
}

// ==============================================
// DATA REQUEST
// ==============================================
/*
 *      Call Weather Data only with City
 *      http://api.openweathermap.org/data/2.5/weather?q=Neu-Isenburg,DE&APPID=<api-key>&lang=german
 *      @param: city + city_code i.e. "Neu-Isenburg","DE"
 */
QByteArray WeatherAPI::getWeatherData(QString city, QString country_code)
{
    QNetworkRequest request(m_currentWeatherDataByCoord);
    qDebug() << "URL:" << m_currentWeatherDataByCoord;

    QByteArray data;
    QEventLoop eventLoop;
    QNetworkAccessManager qnam;

    QObject::connect(&qnam, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkReply* reply = qnam.get(request);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        data = reply->readAll();
        reply->deleteLater();
    }
    else
    {
        qDebug() << "Reply failed. Error code: " << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "Error description: " << reply->errorString();

        delete reply;
    }

    return data;
}

/*

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
*/

/*
 *      Get whole data in one call (incl. forecast) with Latitude & Longitude
 *      https://openweathermap.org/api/one-call-api
 *      https://api.openweathermap.org/data/2.5/onecall?lat={lat}&lon={lon}&exclude={part}&appid={API key}
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
// DEBUG PRINTS
// ==============================================
/*!
 *
 * @param city
 * @param country_code
 * Complete JSON data (weather): "{\"coord\":{\"lon\":50.0522,\"lat\":8.6953},\"weather\":[{\"id\":804,\"main\":\"Clouds\",\"description\":\"overcast clouds\",\"icon\":\"04d\"}],\"base\":\"stations\",\"main\":{\"temp\":301.4,\"feels_like\":300.59,\"temp_min\":301.4,\"temp_max\":301.4,\"pressure\":1014,\"humidity\":33,\"sea_level\":1014,\"grnd_level\":974},\"visibility\":10000,\"wind\":{\"speed\":9.79,\"deg\":28,\"gust\":10.45},\"clouds\":{\"all\":92},\"dt\":1701591756,\"sys\":{\"country\":\"SO\",\"sunrise\":1701571208,\"sunset\":1701613140},\"timezone\":10800,\"id\":60019,\"name\":\"Eyl\",\"cod\":200}"
 */
void  WeatherAPI::printJsonDataWeather( QString city, QString country_code )
{
    qDebug() << "Complete JSON data (weather):" << getWeatherData( city, country_code );
}

/*!
 *
 * @param latitude
 * @param longitude
 */
void WeatherAPI::printJsonDataOneCall( QString latitude, QString longitude )
{
    qDebug() << "Complete JSON data (OneCall):" << getOneCallData( latitude, longitude );
}


// ==============================================
// PARSE JSON
// ==============================================
auto WeatherAPI::analyzeData1st( QByteArray data, QString rootkey )
{
    auto value = 0;

    // json
    QJsonDocument jsonData = QJsonDocument::fromJson ( data );
    QJsonObject root = jsonData.object();
    QJsonValue subVal = root.value( rootkey );
    QJsonObject subObj = subVal.toObject();

    // value
    if ( root.contains( rootkey ) && subObj[ rootkey ].isDouble() )
        value = subObj[ rootkey ].toDouble();
    else
        qDebug() << "No valid data!";

    return value;
}

auto WeatherAPI::analyzeData( QByteArray data, QString rootkey, QString subkey )
{
    auto value = 0;
    QString str = "";


    // json
    QJsonDocument jsonData = QJsonDocument::fromJson ( data );
    QJsonObject root = jsonData.object();
    QJsonValue subVal = root.value( rootkey );
    QJsonObject subObj = subVal.toObject();

    // value
    if ( subObj.contains( subkey ) && subObj[ subkey ].isDouble() )
        value = subObj[ subkey ].toDouble();
    else if ( subObj.contains( subkey) && subObj[ subkey ].isObject() )
    {
        str = subObj[ subkey ].toString();
        qDebug() << "String" << str;
    }
    else
        qDebug() << "No valid data!";

    return value;
}

// ==============================================
// GET SINGLE VALUES
// ==============================================
double WeatherAPI::getCoordLong( QString city, QString country_code )
{
    QByteArray data = getWeatherData( city, country_code );
    double coord_long = analyzeData( data, "coord", "lon" );
    qDebug() << "Längengrad: " << coord_long << "°";
    return coord_long;
}

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

double WeatherAPI::getWeatherStatus(QString city, QString country_code) {
  QByteArray data = getWeatherData( city, country_code );
  m_status = analyzeData( data, "weather", "main" );
  //qDebug() << "Status: " << m_status << QString(u8"\u2614") << QString(u8"\u2601") << QString(u8"\u2600") << QChar(0x4FF0) << "🌑" << "";
  qDebug() << "Status:" << m_status
           << QString::fromUtf8("\u2614") << QString::fromUtf8("\u2601") << QString::fromUtf8("\u2600")
           << QChar(0x4FF0) << "🌑" << "";

    return m_status;

     // https://unicode-table.com/en/emoji/travel-and-places/sky-and-weather/
}

int WeatherAPI::getCloudCoverage(QString city, QString country_code)
{    QByteArray data = getWeatherData( city, country_code );
     m_clouds = analyzeData( data, "clouds", "all" );
     qDebug() << "Clouds: " << m_clouds << "%";
     return m_clouds;
}

void WeatherAPI::printApiKey() {
    qDebug() << "API Key:" << m_apiKey;
}


















