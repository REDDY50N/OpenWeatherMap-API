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

## Dependencies
Qt 5.15.15
`<sudo apt install mesa-common-dev libglu1-mesa-dev`



## Troubleshooting

### SSL Error

```
qt.network.ssl: Incompatible version of OpenSSL (built with OpenSSL 1.x, runtime version is >= 3.x)
qt.network.ssl: QSslSocket::connectToHostEncrypted: TLS initialization failed
Reply failed:  "TLS initialization failed"
```

1. Install OpenSSL 1 and 3 via Qt Maintenenace Tool
2. Switch into Qt dir `~/Qt/Tools/OpenSSL/src`
3. Build and install:
    ```shell
    ./config
    make -j4
    sudo make install
    ```