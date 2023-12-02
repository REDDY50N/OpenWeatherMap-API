#ifndef OWM_API_APIKEYMANAGER_H
#define OWM_API_APIKEYMANAGER_H

#include <QString>
#include <QProcessEnvironment>

class ApiKeyManager {
    QString apiKey = QProcessEnvironment::systemEnvironment().value("API_KEY");

    if (!apiKey.isEmpty()) {
        qDebug() << "API_KEY gefunden:" << apiKey;
        // Hier kannst du den API_KEY in deiner Anwendung verwenden
    } else {
        qDebug() << "API_KEY nicht gefunden.";
        // Behandle den Fall, wenn der API_KEY nicht vorhanden ist
    }
};


#endif //OWM_API_APIKEYMANAGER_H
