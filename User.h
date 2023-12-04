//
// Created by w on 04.12.23.
//

#ifndef ASIO_CLIENT_USER_H
#define ASIO_CLIENT_USER_H

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

struct User {
    QString login;
    QString password;

    QByteArray ToJsonByteArray() const {
        QJsonObject obj;
        obj["login"] = login;
        obj["password"] = password;

        QJsonDocument doc(obj);
        QByteArray data = doc.toJson();

        return data;
    }

    void FromJsonObject(const QJsonObject& json) {
        login = json.value("login").toString();
        password = json.value("password").toString();
    }
};

#endif //ASIO_CLIENT_USER_H
