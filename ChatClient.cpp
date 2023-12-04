//
// Created by asd on 28-Oct-23.
//

#include "ChatClient.h"

ChatClient::ChatClient() {
    ConfigureSocketForSsl();

    connect(&ws, &QWebSocket::sslErrors, this, &ChatClient::SslErrors);
    connect(&ws, &QWebSocket::textMessageReceived, this, &ChatClient::OnMessageReceived);
    connect(&ws, &QWebSocket::connected, this, &ChatClient::Connected);
    connect(&ws, &QWebSocket::disconnected, this, &ChatClient::Disconnected);
    connect(&ws, &QWebSocket::errorOccurred, this, &ChatClient::ErrorOccurred);
}


void ChatClient::Connect(QNetworkRequest req) {
    qDebug() << "Attempt connect";

    ws.open(req);
}

void ChatClient::SslErrors(const QList<QSslError> &errors) {
    ws.ignoreSslErrors(errors); //can't set peer verify name idk
    qDebug() << errors;
}


void ChatClient::Write(const QString &msg) {
    ws.sendTextMessage(msg);
}

void ChatClient::OnMessageReceived(const QString& msg) {
    emit MessageReceived(msg);
}


void ChatClient::ConfigureSocketForSsl() {
    qDebug() << "Ver: " <<  QSslSocket::sslLibraryBuildVersionString();

    QSslConfiguration cfg = ws.sslConfiguration();
    cfg.setProtocol(QSsl::TlsV1_3OrLater);
    cfg.addCaCertificates("../ssl/rootca.crt", QSsl::Pem);
    cfg.setPeerVerifyMode(QSslSocket::VerifyPeer); //verify server cert is valid loaded CA
    ws.setSslConfiguration(cfg);
}

void ChatClient::Connected() {
    qDebug() << "Connected\n";
}

void ChatClient::Disconnected() {
    qDebug() << "Disconnected\n";
}

void ChatClient::ErrorOccurred(QAbstractSocket::SocketError error) {
    qDebug() << "Error occurred: " << error << "\n";
}
