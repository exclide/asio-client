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
    void Connect(const QString& ip, int port);
    void Write(const QString& msg);

private:
    void ConfigureSocketForSsl();

    QWebSocket ws;

signals:
    void MessageReceived(const QString& msg);

private slots:
    void SslErrors(const QList<QSslError> &errors);
    void OnMessageReceived(const QString& message);
    void Connected();
    void Disconnected();
    void ErrorOccurred(QAbstractSocket::SocketError error);
    void HandshakeInterrupted(const QSslError &error);
};


#endif //ASIO_CLIENT_CCLIENT_H
