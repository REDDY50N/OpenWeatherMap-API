# OpenWeatherMap-API
API to download and analyze weather data in Qt. Can be used as a library in other projects or standalone.

## Usage
- Copy your OpenWeatherMap API-Key into $PWD/bin as apikey.txt (TODO: implement QSettings)
- Run as single Project with owm-api.pro
- Or include this API into another qt project as submodule and include the .pri file

## OWM API Key

add your api key to your environment vars .i.e. in ~/.profile
`export OWM_API_KEY="12344567889011121314"`

## Version

change `VERSION` file