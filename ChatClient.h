//
// Created by asd on 28-Oct-23.
//


#ifndef ASIO_CLIENT_CCLIENT_H
#define ASIO_CLIENT_CCLIENT_H

#include <QSslSocket>
#include <QSslConfiguration>
#include <QObject>
#include <QtWebSockets/QtWebSockets>

class ChatClient : public QObject {
Q_OBJECT

public:
    ChatClient();
    void Connect(QNetworkRequest req);
    void Write(const QString& msg);

private:
    void ConfigureSocketForSsl();
    QWebSocket ws;
    bool pongReceived = true;
    QTimer pingTimer;
    int pingRespondTimeMsecs = 5000;

signals:
    void MessageReceived(const QString& msg);
    void ConnectionLost();

private slots:
    void SslErrors(const QList<QSslError> &errors);
    void OnMessageReceived(const QString& message);
    void Connected();
    void Disconnected();
    void ErrorOccurred(QAbstractSocket::SocketError error);
    void PongReceived(quint64 elapsedTime, const QByteArray& payload);
    void DoPing();
};


#endif //ASIO_CLIENT_CCLIENT_H
