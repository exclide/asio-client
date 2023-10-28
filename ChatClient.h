//
// Created by asd on 28-Oct-23.
//


#ifndef ASIO_CLIENT_CCLIENT_H
#define ASIO_CLIENT_CCLIENT_H

#include <QSslSocket>
#include <QSslConfiguration>
#include <QObject>

class ChatClient : public QObject {
Q_OBJECT

public:
    ChatClient();

    void Connect(const QString& ip, int port);

    void Write(const QString& msg);

    void DoRead();


private:
    void ConfigureSocketForSsl();

    QSslSocket* socket;

signals:
    void MessageReceived(const QString& msg);

private slots:
    void SslErrors(const QList<QSslError> &errors);
    void DebugWrittenBytes(qint64 bytes);
    void DebugHandshake();
};


#endif //ASIO_CLIENT_CCLIENT_H
