//
// Created by w on 04.12.23.
//

#ifndef ASIO_CLIENT_DBMESSAGE_H
#define ASIO_CLIENT_DBMESSAGE_H

#include <ctime>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

struct DbMessage {
    QString sender;
    QString receiver;
    QString text;
    std::time_t date;

    QByteArray ToJsonByteArray() const {
        QJsonObject obj;
        obj["sender"] = sender;
        obj["receiver"] = receiver;
        obj["text"] = text;
        obj["date"] = (long long)date;

        QJsonDocument doc(obj);
        QByteArray data = doc.toJson();

        return data;
    }

    void FromJsonObject(const QJsonObject& json) {
        sender = json.value("sender").toString();
        receiver = json.value("receiver").toString();
        text = json.value("text").toString();
        date = json.value("date").toInteger();
    }
};

#endif //ASIO_CLIENT_DBMESSAGE_H
