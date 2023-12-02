/*! @brief Handle the http request and response. */


#ifndef OWM_API_HTTPREQUEST_H
#define OWM_API_HTTPREQUEST_H

#include <QString>

namespace Request {

    class HttpRequest {

        QString m_url = "https://api.openweathermap.org/data/2.5/onecall?lat={lat}&lon={lon}&exclude={part}&appid={API key}";
        //QString

    };

} // Request

#endif //OWM_API_HTTPREQUEST_H
