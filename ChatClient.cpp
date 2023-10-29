//
// Created by asd on 28-Oct-23.
//

#include "ChatClient.h"

ChatClient::ChatClient() : socket(new QSslSocket){
    ConfigureSocketForSsl();

    QObject::connect(socket, &QSslSocket::sslErrors, this, &ChatClient::SslErrors);
    QObject::connect(socket, &QSslSocket::readyRead, this, &ChatClient::DoRead);
    QObject::connect(socket, &QSslSocket::encrypted, this, &ChatClient::DebugHandshake);
    QObject::connect(socket, &QSslSocket::bytesWritten, this, &ChatClient::DebugWrittenBytes);
}


void ChatClient::Connect(const QString &ip, int port) {
    qDebug() << "Attemnt connect";
    socket->connectToHostEncrypted(ip, port);
}

void ChatClient::SslErrors(const QList<QSslError> &errors) {
    qDebug() << errors;
}

void ChatClient::DebugWrittenBytes(qint64 bytes) {
    qDebug() << "Bytes written: " << bytes;
}

void ChatClient::DebugHandshake() {
    qDebug() << "Handshake successful";
}

void ChatClient::Write(const QString &msg) {
    socket->write(msg.toLocal8Bit());
}

void ChatClient::DoRead() {
    QString str = socket->readLine();
    emit MessageReceived(str);
}


void ChatClient::ConfigureSocketForSsl() {
    qDebug() << "Ver: " <<  QSslSocket::sslLibraryBuildVersionString();

    QSslConfiguration cfg = socket->sslConfiguration();
    cfg.setProtocol(QSsl::TlsV1_3OrLater);
    cfg.addCaCertificates("../ssl/rootca.crt", QSsl::Pem);
    socket->setSslConfiguration(cfg);
    socket->setPeerVerifyName("usr"); //verify cert CN
    socket->setPeerVerifyMode(QSslSocket::VerifyPeer); //verify server cert is valid loaded CA
}
