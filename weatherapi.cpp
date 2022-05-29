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


/*

jsonResponse:
 QJsonDocument({"base":"stations","clouds":{"all":75},"cod":200,"coord":{"lat":50.05,"lon":8.7},"dt":1653639765,"id":2864820,"main":{"feels_like":16.39,"humidity":65,"pressure":1021,"temp":16.94,"temp_max":18.2,"temp_min":14.88},"name":"Neu Isenburg","sys":{"country":"DE","id":2005640,"sunrise":1653621920,"sunset":1653679181,"type":2},"timezone":7200,"visibility":10000,"weather":[{"description":"broken clouds","icon":"04d","id":803,"main":"Clouds"}],"wind":{"deg":240,"speed":6.17}})

rootObj:
 QJsonObject({"base":"stations","clouds":{"all":75},"cod":200,"coord":{"lat":50.05,"lon":8.7},"dt":1653639765,"id":2864820,"main":{"feels_like":16.39,"humidity":65,"pressure":1021,"temp":16.94,"temp_max":18.2,"temp_min":14.88},"name":"Neu Isenburg","sys":{"country":"DE","id":2005640,"sunrise":1653621920,"sunset":1653679181,"type":2},"timezone":7200,"visibility":10000,"weather":[{"description":"broken clouds","icon":"04d","id":803,"main":"Clouds"}],"wind":{"deg":240,"speed":6.17}})

current:
 QJsonValue(object, QJsonObject({"feels_like":16.39,"humidity":65,"pressure":1021,"temp":16.94,"temp_max":18.2,"temp_min":14.88}))

currentObj
 QJsonObject({"feels_like":16.39,"humidity":65,"pressure":1021,"temp":16.94,"temp_max":18.2,"temp_min":14.88})
Temperatur:  16.94 °C

  */


/*


    int m_feels_like = 0;
    int m_temp = 0;
    int m_visibility = 0;

    QString data = getWeatherData( city, country_code);
    qDebug() << "Daten:" << data;


    // Way 2 - not work like this
    QJsonDocument document = QJsonDocument::fromJson( data );
    QJsonObject object = document.object();

    QJsonValue value = object.value("main");
    QJsonArray array = value.toArray();
    foreach (const QJsonValue & v, array)
        qDebug() << "\n\n Way 2:" << v.toObject().value("temp").toInt();






    // get the root object
    QJsonDocument jsonDoc_owmOneCallData = QJsonDocument::fromJson( data.toLocal8Bit() );
    QJsonObject owmRootObj = jsonDoc_owmOneCallData.object();

    // get the response object
    QJsonValue owmCurrent = owmRootObj.value("current");
        QJsonObject owmCurrentObj = owmCurrent.toObject();

    // Temperatur
    if (owmCurrentObj.contains("temp") && owmCurrentObj["temp"].isDouble())
        m_temp = owmCurrentObj["temp"].toDouble()-273.15;
    qDebug() << "Temperatur: " << m_temp << "°C";

    if (owmCurrentObj.contains("feels_like") && owmCurrentObj["feels_like"].isDouble())
        m_feels_like = owmCurrentObj["feels_like"].toDouble()-273.15;
    qDebug() << "Gefühlte Temperatur: " << m_feels_like << "°C";

    // Sichtweite
    if (owmCurrentObj.contains("visibility") && owmCurrentObj["visibility"].isDouble())
        m_visibility = owmCurrentObj["visibility"].toDouble();
    qDebug() << "Sichtweite: " << m_visibility/1000 << "km";


    qDebug() << "==================================================================";




    // ===================================================================
    // OWM DATEN by WeatherUpdate
    // ===================================================================

    qDebug() << "\nOWM WETTER DATEN by WEATHER UPDATE";
    qDebug() << "==================================================================";

    // Temperatur
    QString weather_info = (QString)reply->readAll(); // Read OWM Data
    QJsonDocument weather_doc = QJsonDocument::fromJson(weather_info.toUtf8()); // create JSON Document
    QJsonObject weather_obj = weather_doc.object(); // create JSON Object
    QJsonObject main_obj = weather_obj.value("main").toObject();//access to object main nested in json

    //date-hour-temperature-pressure-humidity-weather_description
    QJsonObject weather_description = weather_obj.value("weather").toArray().first().toObject();
    QVariantList weather_list;

    weather_list << QDate::currentDate() << QTime::currentTime() << main_obj.value("temp").toDouble() << main_obj.value("pressure").toDouble()
                 << main_obj.value("humidity").toInt() << weather_description.value("description").toString();


    qDebug() << "Weather List: " << weather_list;
    qDebug() << weather_list.at(0).toDateTime();
    qDebug() << weather_list.at(0).toDate();
    qDebug() << weather_list.at(1).toTime();

    qDebug() << "==================================================================";


//    // ===================================================================
//    // OWM ALERTS
//    // ===================================================================


    qDebug() << "\nOWM WETTER FORECAST";
    qDebug() << "==================================================================";

    QJsonValue owmDailyForecast = owmRootObj.value("hourly");
    QJsonObject owmDailyForecastObj = owmDailyForecast.toObject();

    QStringList keysAlerts = owmDailyForecastObj.keys();
    foreach(QString key, keysAlerts)
    {
         qDebug() << key;
    }

    // Temperatur
    if (owmDailyForecastObj.contains("1") && owmDailyForecastObj["1"].isDouble())
        m_temp = owmDailyForecastObj["1"].toDouble()-273.15;
    qDebug() << "Temperatur: " << m_temp << "°C";



//    qDebug() << "==================================================================";


//       KEYS CURRENT WEATHER OBJECT:

        "clouds"
        "dew_point"
        "dt"
        "feels_like"
        "humidity"
        "pressure"
        "sunrise"
        "sunset"
        "temp"
        "uvi"
        "visibility"
        "weather"
        "wind_deg"
        "wind_speed"



        KEYS ROOT OBJECT:

        "alerts"
        "current"
        "daily"
        "hourly"
        "lat"
        "lon"
        "minutely"
        "timezone"
        "timezone_offset"



        QStringList keysRoot = owmRootObj.keys();
        foreach(QString key, keysRoot)
        {
           // qDebug() << key;
        }

        // DEBUG TO GET KEYS
        QStringList keysCurrent = owmCurrentObj.keys();
        foreach(QString key, keysCurrent)
        {
            // qDebug() << key;
        }

*/
















