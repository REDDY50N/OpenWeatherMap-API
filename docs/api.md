# One Call API 2.5

Make just one API call and get all your essential weather data for a specific location with our new OpenWeather One Call API 2.5. Easy migration from the Dark Sky API.

The One Call API 2.5 provides the following weather data for any geographical coordinates:

- Current weather
- Minute forecast for 1 hour
- Hourly forecast for 48 hours
- Daily forecast for 7 days
- National weather alerts
- Historical weather data for the previous 5 days

## Current and forecast weather data

To get access to current weather, minute forecast for 1 hour, hourly forecast for 48 hours, daily forecast for 7 days and government weather alerts, please use this section of the documentation.

If you are interested in historical weather data, please read the "Historical weather data" section.

### How to make an API call

https://api.openweathermap.org/data/2.5/onecall?lat={lat}&lon={lon}&exclude={part}&appid={API key}
Parameters
lat, lon 	required 	Geographical coordinates (latitude, longitude)
appid 	required 	Your unique API key (you can always find it on your account page under the "API key" tab)
exclude 	optional 	By using this parameter you can exclude some parts of the weather data from the API response. It should be a comma-delimited list (without spaces).

Available values:

    current
    minutely
    hourly
    daily
    alerts

units 	optional 	Units of measurement. standard, metric and imperial units are available. If you do not use the units parameter, standard units will be applied by default. Learn more
lang 	optional 	You can use the lang parameter to get the output in your language. Learn more

https://api.openweathermap.org/data/2.5/onecall?lat=33.44&lon=-94.04&exclude=hourly,daily&appid={API key}

                

{
  "lat": 33.44,
  "lon": -94.04,
  "timezone": "America/Chicago",
  "timezone_offset": -21600,
  "current": {
    "dt": 1618317040,
    "sunrise": 1618282134,
    "sunset": 1618333901,
    "temp": 284.07,
    "feels_like": 282.84,
    "pressure": 1019,
    "humidity": 62,
    "dew_point": 277.08,
    "uvi": 0.89,
    "clouds": 0,
    "visibility": 10000,
    "wind_speed": 6,
    "wind_deg": 300,
    "weather": [
      {
        "id": 500,
        "main": "Rain",
        "description": "light rain",
        "icon": "10d"
      }
    ],
    "rain": {
      "1h": 0.21
    }
  },
    "minutely": [
    {
      "dt": 1618317060,
      "precipitation": 0.205
    },
    ...
  },
    "hourly": [
    {
      "dt": 1618315200,
      "temp": 282.58,
      "feels_like": 280.4,
      "pressure": 1019,
      "humidity": 68,
      "dew_point": 276.98,
      "uvi": 1.4,
      "clouds": 19,
      "visibility": 306,
      "wind_speed": 4.12,
      "wind_deg": 296,
      "wind_gust": 7.33,
      "weather": [
        {
          "id": 801,
          "main": "Clouds",
          "description": "few clouds",
          "icon": "02d"
        }
      ],
      "pop": 0
    },
    ...
  }
    "daily": [
    {
      "dt": 1618308000,
      "sunrise": 1618282134,
      "sunset": 1618333901,
      "moonrise": 1618284960,
      "moonset": 1618339740,
      "moon_phase": 0.04,
      "temp": {
        "day": 279.79,
        "min": 275.09,
        "max": 284.07,
        "night": 275.09,
        "eve": 279.21,
        "morn": 278.49
      },
      "feels_like": {
        "day": 277.59,
        "night": 276.27,
        "eve": 276.49,
        "morn": 276.27
      },
      "pressure": 1020,
      "humidity": 81,
      "dew_point": 276.77,
      "wind_speed": 3.06,
      "wind_deg": 294,
      "weather": [
        {
          "id": 500,
          "main": "Rain",
          "description": "light rain",
          "icon": "10d"
        }
      ],
      "clouds": 56,
      "pop": 0.2,
      "rain": 0.62,
      "uvi": 1.93
    },
    ...
    },
    "alerts": [
    {
      "sender_name": "NWS Tulsa",
      "event": "Heat Advisory",
      "start": 1597341600,
      "end": 1597366800,
      "description": "...HEAT ADVISORY REMAINS IN EFFECT FROM 1 PM THIS AFTERNOON TO\n8 PM CDT THIS EVENING...\n* WHAT...Heat index values of 105 to 109 degrees expected.\n* WHERE...Creek, Okfuskee, Okmulgee, McIntosh, Pittsburg,\nLatimer, Pushmataha, and Choctaw Counties.\n* WHEN...From 1 PM to 8 PM CDT Thursday.\n* IMPACTS...The combination of hot temperatures and high\nhumidity will combine to create a dangerous situation in which\nheat illnesses are possible.",
      "tags": [
        "Extreme temperature value"
        ]
    },
    ...
  ]
                

              

    lat Geographical coordinates of the location (latitude)
    lon Geographical coordinates of the location (longitude)
    timezone Timezone name for the requested location
    timezone_offset Shift in seconds from UTC
    current Current weather data API response
        current.dt Current time, Unix, UTC
        current.sunrise Sunrise time, Unix, UTC
        current.sunset Sunset time, Unix, UTC
        current.temp Temperature. Units - default: kelvin, metric: Celsius, imperial: Fahrenheit. How to change units used
        current.feels_like Temperature. This temperature parameter accounts for the human perception of weather. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit.
        current.pressure Atmospheric pressure on the sea level, hPa
        current.humidity Humidity, %
        current.dew_point Atmospheric temperature (varying according to pressure and humidity) below which water droplets begin to condense and dew can form. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit.
        current.clouds Cloudiness, %
        current.uvi Current UV index
        current.visibility Average visibility, metres. The maximum value of the visibility is 10km
        current.wind_speed Wind speed. Wind speed. Units – default: metre/sec, metric: metre/sec, imperial: miles/hour. How to change units used
        current.wind_gust (where available) Wind gust. Units – default: metre/sec, metric: metre/sec, imperial: miles/hour. How to change units used
        current.wind_deg Wind direction, degrees (meteorological)
        current.rain
            current.rain.1h (where available) Rain, mm/h
        current.snow
            current.snow.1h (where available) Precipitation, mm/h
        current.weather
            current.weather.id Weather condition id
            current.weather.main Group of weather parameters (Rain, Snow, Extreme etc.)
            current.weather.description Weather condition within the group (full list of weather conditions). Get the output in your language
            current.weather.icon Weather icon id. How to get icons
    minutely Minute forecast weather data API response
        minutely.dt Time of the forecasted data, unix, UTC
        minutely.precipitation Precipitation, mm/h
    hourly Hourly forecast weather data API response
        hourly.dt Time of the forecasted data, Unix, UTC
        hourly.temp Temperature. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit. How to change units used
        hourly.feels_like Temperature. This accounts for the human perception of weather. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit.
        hourly.pressure Atmospheric pressure on the sea level, hPa
        hourly.humidity Humidity, %
        hourly.dew_point Atmospheric temperature (varying according to pressure and humidity) below which water droplets begin to condense and dew can form. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit.
        hourly.uvi UV index
        hourly.clouds Cloudiness, %
        hourly.visibility Average visibility, metres. The maximum value of the visibility is 10km
        hourly.wind_speed Wind speed. Units – default: metre/sec, metric: metre/sec, imperial: miles/hour.How to change units used
        hourly.wind_gust (where available) Wind gust. Units – default: metre/sec, metric: metre/sec, imperial: miles/hour. How to change units used
        chourly.wind_deg Wind direction, degrees (meteorological)
        hourly.pop Probability of precipitation. The values of the parameter vary between 0 and 1, where 0 is equal to 0%, 1 is equal to 100%
        hourly.rain
            hourly.rain.1h (where available) Rain, mm/h
        hourly.snow
            hourly.snow.1h (where available) Precipitation, mm/h
        hourly.weather
            hourly.weather.id Weather condition id
            hourly.weather.main Group of weather parameters (Rain, Snow, Extreme etc.)
            hourly.weather.description Weather condition within the group (full list of weather conditions). Get the output in your language
            hourly.weather.icon Weather icon id. How to get icons
    daily Daily forecast weather data API response
        daily.dt Time of the forecasted data, Unix, UTC
        daily.sunrise Sunrise time, Unix, UTC
        daily.sunset Sunset time, Unix, UTC
        daily.moonrise The time of when the moon rises for this day, Unix, UTC
        daily.moonset The time of when the moon sets for this day, Unix, UTC
        daily.moon_phase Moon phase. 0 and 1 are 'new moon', 0.25 is 'first quarter moon', 0.5 is 'full moon' and 0.75 is 'last quarter moon'. The periods in between are called 'waxing crescent', 'waxing gibous', 'waning gibous', and 'waning crescent', respectively.
        daily.temp Units – default: kelvin, metric: Celsius, imperial: Fahrenheit. How to change units used
            daily.temp.morn Morning temperature.
            daily.temp.day Day temperature.
            daily.temp.eve Evening temperature.
            daily.temp.night Night temperature.
            daily.temp.min Min daily temperature.
            daily.temp.max Max daily temperature.
        daily.feels_like This accounts for the human perception of weather. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit. How to change units used
            daily.feels_like.morn Morning temperature.
            daily.feels_like.day Day temperature.
            daily.feels_like.eve Evening temperature.
            daily.feels_like.night Night temperature.
        daily.pressure Atmospheric pressure on the sea level, hPa
        daily.humidity Humidity, %
        daily.dew_point Atmospheric temperature (varying according to pressure and humidity) below which water droplets begin to condense and dew can form. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit.
        daily.wind_speed Wind speed. Units – default: metre/sec, metric: metre/sec, imperial: miles/hour. How to change units used
        daily.wind_gust (where available) Wind gust. Units – default: metre/sec, metric: metre/sec, imperial: miles/hour. How to change units used
        daily.wind_deg Wind direction, degrees (meteorological)
        daily.clouds Cloudiness, %
        daily.uvi The maximum value of UV index for the day
        daily.pop Probability of precipitation. The values of the parameter vary between 0 and 1, where 0 is equal to 0%, 1 is equal to 100%
        daily.rain (where available) Rain volume, mm
        daily.snow (where available) Snow volume, mm
        daily.weather
            daily.weather.id Weather condition id
            daily.weather.main Group of weather parameters (Rain, Snow, Extreme etc.)
            daily.weather.description Weather condition within the group (full list of weather conditions). Get the output in your language
            daily.weather.icon Weather icon id. How to get icons
    alerts National weather alerts data from major national weather warning systems
        alerts.sender_name Name of the alert source. Please read here the full list of alert sources
        alerts.event Alert event name
        alerts.start Date and time of the start of the alert, Unix, UTC
        alerts.end Date and time of the end of the alert, Unix, UTC
        alerts.description Description of the alert
        alerts.tags Type of severe weather

National weather alerts are provided in English by default.
Please note that some agencies provide the alert’s description only in a local language.
Historical weather data

To learn about how get access to historical weather data for the previous 5 days, please use this section of the documentation.

If you are interested in current weather data, forecasts and weather alerts please read the "Current and forecast weather data" section.
How to make an API call

https://api.openweathermap.org/data/2.5/onecall/timemachine?lat={lat}&lon={lon}&dt={time}&appid={API key}
Parameters
lat, lon 	required 	Geographical coordinates (latitude, longitude)
dt 	required 	Date from the previous five days (Unix time, UTC time zone), e.g. dt=1586468027
appid 	required 	Your unique API key (you can always find it on your account page under the "API key" tab)
only_current 	optional 	By using this parameter you can exclude full historical weather data for the specified day, but received the data for only the specified timestamp. If the user specifies this parameter, then the API response will contain only the current section.

To activate this option, please use default value only_current = {true}.
Please find the example of the API call below.
units 	optional 	Units of measurement. standard, metric and imperial units are available. If you do not use the units parameter, standard units will be applied by default. Learn more
lang 	optional 	You can use the lang parameter to get the output in your language. Learn more

Please note that in order to get historical data for the last five days, you need to make five API calls (one call for each day).

In case you need historical data only for the specified timestamp (not the whole day), we strongly recommend you to use the parameter only_current={true}.

Example of the API call to get all historical weather data for a day, covered by specified timestamp:

http://api.openweathermap.org/data/2.5/onecall/timemachine?lat=60.99&lon=30.9&dt=1586468027&appid={API key}

Example of the API call to get historical weather data only for the specified timestamp:

https://api.openweathermap.org/data/2.5/onecall/timemachine?lat=60&lon=30&dt=1650445666&appid={API key}&only_current={true}

                   

  {
  "lat": 60,
  "lon": 30,
  "timezone": "Europe/Moscow",
  "timezone_offset": 10800,
  "current": {
    "dt": 1650445666,
    "sunrise": 1650421749,
    "sunset": 1650475701,
    "temp": 281.26,
    "feels_like": 278.73,
    "pressure": 1026,
    "humidity": 65,
    "dew_point": 275.08,
    "uvi": 2.83,
    "clouds": 99,
    "visibility": 10000,
    "wind_speed": 4.21,
    "wind_deg": 80,
    "wind_gust": 7.81,
    "weather": [
      {
        "id": 804,
        "main": "Clouds",
        "description": "overcast clouds",
        "icon": "04d"
      }
    ]
  }
}
                   

                 

                   

  {
    "lat": 60.99,
    "lon": 30.9,
    "timezone": "Europe/Moscow",
    "timezone_offset": 10800"
    "current": {
      "dt": 1586468027,
      "sunrise": 1586487424,
      "sunset": 1586538297,
      "temp": 274.31,
      "feels_like": 269.79,
      "pressure": 1006,
      "humidity": 72,
      "dew_point": 270.21,
      "clouds": 0,
      "visibility": 10000,
      "wind_speed": 3,
      "wind_deg": 260,
      "weather": [
        {
          "id": 800,
          "main": "Clear",
          "description": "clear sky",
          "icon": "01n"
        }
      ]
    },
    "hourly": [
      {
        "dt": 1586390400,
        "temp": 278.41,
        "feels_like": 269.43,
        "pressure": 1006,
        "humidity": 65,
        "dew_point": 272.46,
        "clouds": 0,
        "wind_speed": 9.83,
        "wind_deg": 60,
        "wind_gust": 15.65,
        "weather": [
          {
            "id": 800,
            "main": "Clear",
            "description": "clear sky",
            "icon": "01n"
          }
        ]
      },
      ...
    }
                   

                 

    lat Geographical coordinates of the location (latitude)
    lon Geographical coordinates of the location (longitude)
    timezone Timezone name for the requested location
    timezone_offset Shift in seconds from UTC
    current Data point dt refers to the requested time, rather than the current time
        current.dt Requested time, Unix, UTC
        current.sunrise Sunrise time, Unix, UTC
        current.sunset Sunset time, Unix, UTC
        current.temp Temperature. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit. How to change units used
        current.feels_like Temperature. This accounts for the human perception of weather. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit.
        current.pressure Atmospheric pressure on the sea level, hPa
        current.humidity Humidity, %
        current.dew_point Atmospheric temperature (varying according to pressure and humidity) below which water droplets begin to condense and dew can form. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit.
        current.clouds Cloudiness, %
        current.uvi Midday UV index
        current.visibility Average visibility, metres. The maximum value of the visibility is 10km
        current.wind_speed Wind speed. Units – default: metre/sec, metric: metre/sec, imperial: miles/hour. How to change units used
        current.wind_gust (where available) Wind gust. Wind speed. Units – default: metre/sec, metric: metre/sec, imperial: miles/hour. How to change units used
        current.wind_deg Wind direction, degrees (meteorological)
        current.rain (where available) Precipitation, mm/h
        current.snow (where available) Precipitation, mm/h
        current.weather
            current.weather.id Weather condition id
            current.weather.main Group of weather parameters (Rain, Snow, Extreme etc.)
            current.weather.description Weather condition within the group (full list of weather conditions). Get the output in your language
            current.weather.icon Weather icon id. How to get icons
    hourly Data block contains hourly historical data starting at 00:00 on the requested day and continues until 23:59 on the same day (UTC time)
        hourly.dt Time of historical data, Unix, UTC
        hourly.temp Temperature. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit. How to change units used
        hourly.feels_like Temperature. This accounts for the human perception of weather. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit.
        hourly.pressure Atmospheric pressure on the sea level, hPa
        hourly.humidity Humidity, %
        hourly.dew_point Atmospheric temperature (varying according to pressure and humidity) below which water droplets begin to condense and dew can form. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit.
        hourly.clouds Cloudiness, %
        hourly.visibility Average visibility, metres. The maximum value of the visibility is 10km
        hourly.wind_speed Wind speed. Wind speed. Units – default: metre/sec, metric: metre/sec, imperial: miles/hour. How to change units used
        hourly.wind_gust (where available) Wind gust. Units – default: metre/sec, metric: metre/sec, imperial: miles/hour. How to change units used
        chourly.wind_deg Wind direction, degrees (meteorological)
        hourly.rain (where available) Precipitation, mm/h
        hourly.snow (where available) Precipitation, mm/h
        hourly.weather
            hourly.weather.id Weather condition id
            hourly.weather.main Group of weather parameters (Rain, Snow, Extreme etc.)
            hourly.weather.description Weather condition within the group (full list of weather conditions). Get the output in your language
            hourly.weather.icon Weather icon id. How to get icons

List of weather condition codes

List of weather condition codes with icons (range of thunderstorm, drizzle, rain, snow, clouds, atmosphere including extreme conditions like tornado, hurricane etc.)
Other features
Units of measurement

standard, metric and imperial units are available.
Alerts
Parameter 	Description 	Standard 	Metric 	Imperial
lat 	City geo location, latitude 	- 	- 	-
lon 	City geo location, longitude 	- 	- 	-
timezone 	Timezone name for the requested location 	- 	- 	-
timezone_offset 	Shift in seconds from UTC 	- 	- 	-
Current weather
current.dt 	Current time 	unix, UTC 	unix, UTC 	unix, UTC
current.sunrise 	Sunrise time 	unix, UTC 	unix, UTC 	unix, UTC
current.sunset 	Sunset time 	unix, UTC 	unix, UTC 	unix, UTC
current.temp 	Temperature 	Kelvin 	Celsius 	Fahrenheit
current.feels_like 	Feels like temperature 	Kelvin 	Celsius 	Fahrenheit
current.humidity 	Humidity 	% 	% 	%
current.pressure 	Atmospheric pressure on the sea level 	hPa 	hPa 	hPa
current.dew_point 	Atmospheric temperature below which water droplets begin to condense and dew can form 	Kelvin 	Celsius 	Fahrenheit
current.clouds 	Cloudiness 	% 	% 	%
current.uvi 	UV index 	- 	- 	-
current.visibility 	Average visibility 	Metres 	Metres 	Metres
current.wind_speed 	Wind speed 	metre/sec 	metre/sec 	miles/hour
current.wind_gust 	Wind gust 	metre/sec 	metre/sec 	miles/hour
current.wind_deg 	Wind direction 	degrees (meteorological) 	degrees (meteorological) 	degrees (meteorological)
current.rain.1h 	Rain 	mm/h 	mm/h 	mm/h
current.snow.1h 	Snow 	mm/h 	mm/h 	mm/h
current.weather (more info Weather condition codes)
current.weather.id 	Weather condition id 	- 	- 	-
current.weather.main 	Group of weather parameters (Rain, Snow, Extreme etc.) 	- 	- 	-
current.weather.description 	Weather condition within the group 	- 	- 	-
current.weather.icon 	Weather icon id 	- 	- 	-
Minute forecast
minutely.dt 	Current time 	unix, UTC 	unix, UTC 	unix, UTC
minutely.precipitation 	Precipitation 	mm/h 	mm/h 	mm/h
Hourly forecast
hourly.dt 	Time of the forecasted data 	unix, UTC 	unix, UTC 	unix, UTC
hourly.temp 	Temperature 	Kelvin 	Celsius 	Fahrenheit
hourly.feels_like 	Feels like temperature 	Kelvin 	Celsius 	Fahrenheit
hourly.pressure 	Atmospheric pressure on the sea level 	hPa 	hPa 	hPa
hourly.humidity 	Humidity 	% 	% 	%
hourly.dew_point 	Atmospheric temperature below which water droplets begin to condense and dew can form 	Kelvin 	Celsius 	Fahrenheit
hourly.clouds 	Cloudiness 	% 	% 	%
hourly.uvi 	UV index 	- 	- 	-
hourly.visibility 	Average visibility 	Metres 	Metres 	Metres
hourly.wind_speed 	Wind speed 	metre/sec 	metre/sec 	miles/hour
hourly.wind_gust 	Wind gust 	metre/sec 	metre/sec 	miles/hour
hourly.wind_deg 	Wind direction 	degrees (meteorological) 	degrees (meteorological) 	degrees (meteorological)
hourly.pop 	Probability of precipitation 	% 	% 	%
hourly.rain.1h 	Rain 	mm/h 	mm/h 	mm/h
hourly.snow.1h 	Snow 	mm/h 	mm/h 	mm/h
hourly.weather (more info Weather condition codes)
hourly.weather.id 	Weather condition id 	- 	- 	-
hourly.weather.main 	Group of weather parameters (Rain, Snow, Extreme etc.) 	- 	- 	-
hourly.weather.description 	Weather condition within the group 	- 	- 	-
hourly.weather.icon 	Weather icon id 	- 	- 	-
Daily forecast
daily.dt 	Time of the forecasted data 	unix, UTC 	unix, UTC 	unix, UTC
daily.sunrise 	Sunrise time 	unix, UTC 	unix, UTC 	unix, UTC
daily.sunset 	Sunset time 	unix, UTC 	unix, UTC 	unix, UTC
daily.moonrise 	The time of when the moon rises for this day 	unix, UTC 	unix, UTC 	unix, UTC
daily.moonset 	The time of when the moon sets for this day 	unix, UTC 	unix, UTC 	unix, UTC
daily.moon_phase 	Moon phase 	- 	- 	-
daily.temp
daily.temp.morn 	Morning temperature 	Kelvin 	Celsius 	Fahrenheit
daily.temp.day 	Day temperature 	Kelvin 	Celsius 	Fahrenheit
daily.temp.eve 	Evening temperature 	Kelvin 	Celsius 	Fahrenheit
daily.temp.night 	Night temperature 	Kelvin 	Celsius 	Fahrenheit
daily.temp.min 	Min daily temperature 	Kelvin 	Celsius 	Fahrenheit
daily.temp.max 	Max daily temperature 	Kelvin 	Celsius 	Fahrenheit
daily.feels_like
daily.temp.feels_like 	Morning temperature 	Kelvin 	Celsius 	Fahrenheit
daily.temp.feels_like 	Day temperature 	Kelvin 	Celsius 	Fahrenheit
daily.temp.feels_like 	Evening temperature 	Kelvin 	Celsius 	Fahrenheit
daily.temp.feels_like 	Night temperature 	Kelvin 	Celsius 	Fahrenheit
daily.pressure 	Atmospheric pressure on the sea level 	hPa 	hPa 	hPa
daily.humidity 	Humidity 	% 	% 	%
daily.dew_point 	Atmospheric temperature below which water droplets begin to condense and dew can form 	Kelvin 	Celsius 	Fahrenheit
daily.clouds 	Cloudiness 	% 	% 	%
daily.uvi 	UV index 	- 	- 	-
daily.visibility 	Average visibility 	Metres 	Metres 	Metres
daily.wind_speed 	Wind speed 	metre/sec 	metre/sec 	miles/hour
daily.wind_gust 	Wind gust 	metre/sec 	metre/sec 	miles/hour
daily.wind_deg 	Wind direction 	degrees (meteorological) 	degrees (meteorological) 	degrees (meteorological)
daily.pop 	Probability of precipitation 	% 	% 	%
daily.rain 	Rain 	mm 	mm 	mm
daily.snow 	Snow 	mm 	mm 	mm
daily.weather (more info Weather condition codes)
daily.weather.id 	Weather condition id 	- 	- 	-
daily.weather.main 	Group of weather parameters (Rain, Snow, Extreme etc.) 	- 	- 	-
daily.weather.description 	Weather condition within the group 	- 	- 	-
daily.weather.icon 	Weather icon id 	- 	- 	-
alerts.sender_name 	Name of the alert source 	- 	- 	-
alerts.event 	Alert event name 	- 	- 	-
alerts.start 	Date and time of the start of the alert 	unix, UTC 	unix, UTC 	unix, UTC
alerts.end 	Date and time of the end of the alert 	unix, UTC 	unix, UTC 	unix, UTC
alerts.description 	Description of the alert 	- 	- 	-
alerts.tags 	Type of severe weather 	- 	- 	-

http://api.openweathermap.org/data/2.5/onecall?lat={lat}&lon={lon}&units={units}
Parameters
units 	optional 	Units of measurement. standard, metric and imperial units are available. If you do not use the units parameter, standard units will be applied by default.

Temperature is available in Fahrenheit, Celsius and Kelvin units.

Wind speed is available in miles/hour and metre/sec.

    For temperature in Fahrenheit and wind speed in miles/hour, use units=imperial
    For temperature in Celsius and wind speed in metre/sec, use units=metric
    Temperature in Kelvin and wind speed in metre/sec is used by default, so there is no need to use the units parameter in the API call if you want this

Standard (default)

api.openweathermap.org/data/2.5/onecall?lat=30.489772&lon=-99.771335

Metric

api.openweathermap.org/data/2.5/onecall?lat=30.489772&lon=-99.771335&units=metric

Imperial

api.openweathermap.org/data/2.5/onecall?lat=30.489772&lon=-99.771335&units=imperial
Multilingual support

You can use lang parameter to get the output in your language.

The contents of the description field will be translated.

http://api.openweathermap.org/data/2.5/onecall?lat={lat}&lon={lon}&lang={lang}
Parameters
lang 	optional 	You can use the lang parameter to get the output in your language.

http://api.openweathermap.org/data/2.5/onecall?lat=30.489772&lon=-99.771335&lang=zh_cn

We support the following languages. To select one, you can use the corresponding language code:

    af Afrikaans
    al Albanian
    ar Arabic
    az Azerbaijani
    bg Bulgarian
    ca Catalan
    cz Czech
    da Danish
    de German
    el Greek
    en English
    eu Basque
    fa Persian (Farsi)
    fi Finnish
    fr French
    gl Galician
    he Hebrew
    hi Hindi
    hr Croatian
    hu Hungarian
    id Indonesian
    it Italian
    ja Japanese
    kr Korean
    la Latvian
    lt Lithuanian
    mk Macedonian
    no Norwegian
    nl Dutch
    pl Polish
    pt Portuguese
    pt_br Português Brasil
    ro Romanian
    ru Russian
    sv, se	Swedish
    sk Slovak
    sl Slovenian
    sp, es	Spanish
    sr Serbian
    th Thai
    tr Turkish
    ua, uk Ukrainian
    vi Vietnamese
    zh_cn Chinese Simplified
    zh_tw Chinese Traditional
    zu Zulu

List of national weather alerts sources
Country 	Agency
Afghanistan 	National Disaster Management Authority
Albania 	Institute of GeoSciences, Energy, Water and Environment
Algeria 	National Meteorological Office
Anguilla 	Disaster Management Anguilla
Antigua and Barbuda 	Meteorological Services
Argentina 	Servicio Meteorologico Nacional
Aruba 	Meteorological Department of Aruba
Austria 	
Central Institute for Meteorology and Geodynamics
Water Balance Department
Barbados 	Department of Emergency Management
Belgium 	Royal Meteorological Institute
Bosnia and Herzegovin 	
Federal Hydrometeorological Institute of BiH
Republic Hydrometeorological Institute
Botswana 	Department of Meteorological Services
Brazil 	National Meteorological Institute - INMET
Bulgaria 	National Institute of Meteorology and Hydrology - Plovdiv branch
Canada 	
Alberta Emergency Management Agency (Government of Alberta, Ministry of Municipal Affairs)
Meteorological Service of Canada
Quebec Ministry of Public Safety
Colombia 	UNGRD (National Unit for Disaster Risk Management)
Croatia 	State Hydrometeorological Institute (DHMZ)
Cyprus 	Meteorological Service
Czech Republic 	Czech Hydrometeorological Institute
Denmark 	Danmarks Meteorologiske Instituts
Estonia 	State Weather Service
Federated States of Micronesia 	
Weather Service Office Chuuk
Weather Service Office Pohnpei
Weather Service Office Yap
Finland 	Finnish Meteorological Institute
France 	Meteo-France
Germany 	German Meteorological Office
Greece 	Hellenic National Meteorological Service
Guyana 	Hydrometeorological Service
Hungary 	Hungarian Meteorological Service
Iceland 	Icelandic Meteorological Office
India 	Meteorological Department
Indonesia 	
Agency for Meteorology Climatology and Geophysics of Republic Indonesia (BMKG)
InaTEWS BMKG, Earthquake with magnitude 5.0 above
Ireland 	Met Eireann - Irish Meteorological Service
Israel 	Meteorological Service
Italy 	National Center of Meteorology and Aeronautical Climatology (CNMCA)
Jamaica 	Meteorological Service
Kenya 	Meteorological Department
Kuwait 	Meteorological Department
Latvia 	Latvian Environment, Geology and Meteorology Center
Lithuania 	Lithuanian Hydrometeorological Service
Luxembourg 	Luxembourg Airport Administration
Madagascar 	Operational Meteorology
Malawi 	Meteorological Services
Malta 	Meteorological Office
Marshall Islands 	Majuro Weather Service Office
Mexico 	CONAGUA - National Meteorological Service of Mexico
Moldova 	State Hydrometeorological Service
Mongolia 	National Agency for Meteorology and Environmental Monitoring
Montenegro 	Institute of Hydrometeorology and Seismology
Myanmar 	Department of Meteorology and Hydrology
Netherlands 	Royal Netherlands Meteorological Institute
New Zealand 	
GNS Science
MetService
National Emergency Management Agency
North Macedonia 	Republic Hydrometeorological Organization
Norway 	
Norwegian Meteorological Institute
Norwegian Water Resources and Energy Directorate
Oman 	Directorate General of Meteorology
Palau 	Weather Service Office
Papua New Guinea 	Papua New Guinea Meteorological Service
Paraguay 	Directorate of Meteorology and Hydrology
Philippines 	Philippine Atmospheric Geophysical and Astronomical Services Administration
Poland 	Institute of Meteorology and Water Management
Portugal 	Portuguese Institute of Sea and Atmosphere, I.P.
Romania 	National Meteorological Administration
Russia 	Russian Federal Service for Hydrometeorology and Environmental Monitoring
Saint Lucia 	Meteorological Services
Saint Vincent and the Grenadines 	Meteorological Services
Samoa 	Meteorology Division
Senegal 	National Agency of Civil Aviation and Meteorology
Serbia 	Republic Hydrometeorological Institute
Slovakia 	Slovak Hydrometeorological Institute
Slovenia 	National Meteorological Service
Solomon Islands 	Meteorological Service
South Africa 	South Africa Weather Service
Spain 	Meteorology Statal Agency
Suriname 	Suriname Meteorological Service
Sweden 	Swedish Meteorological and Hydrological Institute
Switzerland 	MeteoSwiss, Bundesamt für Meteorologie und Klimatologie
Tanzania 	Meteorological Authority
Thailand 	Thai Meteorological Department
Tonga 	Tonga Meteorological Service
Trinidad and Tobago 	Trinidad and Tobago Meteorological Service
United Kingdom of Great Britain and Northern Ireland 	Met Office
United States 	
Environmental Protection Agency (EPA), Air Quality Alerts
Integrated Public Alerrt and Warning System (IPAWS)
National Oceanic and Atmospheric Administration (NOAA), National Tsunami Warning Center
National Oceanic and Atmospheric Administration (NOAA), National Weather Service
National Oceanic and Atmospheric Administration (NOAA), National Weather Service - Marine Zones
U.S. Geological Survey (USGS), Volcano Hazard Program
Vanuatu 	Meteorological Services
Zimbabwe 	Meteorological Services Department

Please note that some agencies from the list may cease to provide us the weather alert information.
In case you don’t receive alerts from any agency, please contact us.
We constantly work on our product’s improvement and keep expanding the list of partner agencies.
Call back function for JavaScript code

To use JavaScript code you can transfer callback functionName to JSONP callback.

api.openweathermap.org/data/2.5/onecall?lat=38.8&lon=12.09&callback=test

                           

test({
  "lat": 40.12,
  "lon": -96.66,
  "timezone": "America/Chicago",
  "timezone_offset": -18000,
  "current": {
    "dt": 1595243443,
    "sunrise": 1595243663,
    "sunset": 1595296278,
    "temp": 293.28,
    "feels_like": 293.82,
    "pressure": 1016,
    "humidity": 100,
    "dew_point": 293.28,
    "uvi": 10.64,
    "clouds": 90,
    "visibility": 10000,
    "wind_speed": 4.6,
    "wind_deg": 310,
    "weather": [
      {
        "id": 501,
        "main": "Rain",
        "description": "moderate rain",
        "icon": "10n"
      },
      {
        "id": 201,
        "main": "Thunderstorm",
        "description": "thunderstorm with rain",
        "icon": "11n"
      }
    ],
    "rain": {
      "1h": 2.93
    }
  },
  "minutely": [
    {
      "dt": 1595243460,
      "precipitation": 2.928
    },
    ...
  },
    "hourly": [
    {
      "dt": 1595242800,
      "temp": 293.28,
      "feels_like": 293.82,
      "pressure": 1016,
      "humidity": 100,
      "dew_point": 293.28,
      "clouds": 90,
      "visibility": 10000,
      "wind_speed": 4.6,
      "wind_deg": 123,
      "weather": [
        {
          "id": 501,
          "main": "Rain",
          "description": "moderate rain",
          "icon": "10n"
        }
      ],
      "pop": 0.99,
      "rain": {
        "1h": 2.46
      }
    },
    ...
  }
"daily": [
    {
      "dt": 1595268000,
      "sunrise": 1595243663,
      "sunset": 1595296278,
      "temp": {
        "day": 298.82,
        "min": 293.25,
        "max": 301.9,
        "night": 293.25,
        "eve": 299.72,
        "morn": 293.48
      },
      "feels_like": {
        "day": 300.06,
        "night": 292.46,
        "eve": 300.87,
        "morn": 293.75
      },
      "pressure": 1014,
      "humidity": 82,
      "dew_point": 295.52,
      "wind_speed": 5.22,
      "wind_deg": 146,
      "weather": [
        {
          "id": 502,
          "main": "Rain",
          "description": "heavy intensity rain",
          "icon": "10d"
        }
      ],
      "clouds": 97,
      "pop": 1,
      "rain": 12.57,
      "uvi": 10.64
    },
    ...
    },
"alerts": [
    {
      "sender_name": "NWS Tulsa (Eastern Oklahoma)",
      "event": "Heat Advisory",
      "start": 1597341600,
      "end": 1597366800,
      "description": "...HEAT ADVISORY REMAINS IN EFFECT FROM 1 PM THIS AFTERNOON TO\n8 PM CDT THIS EVENING...\n* WHAT...Heat index values of 105 to 109 degrees expected.\n* WHERE...Creek, Okfuskee, Okmulgee, McIntosh, Pittsburg,\nLatimer, Pushmataha, and Choctaw Counties.\n* WHEN...From 1 PM to 8 PM CDT Thursday.\n* IMPACTS...The combination of hot temperatures and high\nhumidity will combine to create a dangerous situation in which\nheat illnesses are possible."
    },
    ...
  ]
  })
                           

                        

