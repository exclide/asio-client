//
// Created by w on 02.12.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoginWindow.h" resolved

#include "LoginWindow.h"
#include "UiLoginWindow.h"
#include "ChatClient.h"
#include "HostInfo.h"
#include "User.h"

LoginWindow::LoginWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::LoginWindow) {
    ui->setupUi(this);

    connect(ui->button_login, &QPushButton::clicked, this, &LoginWindow::Login);
    connect(ui->button_register, &QPushButton::clicked, this, &LoginWindow::Register);

    ConfigureSsl();
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::Login() {
    auto login = ui->line_login->text();
    auto pass = ui->line_password->text();

    auto data = User{login, pass}.ToJsonByteArray();

    url.setPath("/api/login");
    req.setUrl(url);
    req.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    //req.setRawHeader("Connection", "Keep-Alive");
    loginReply = network->post(req, data);
    connect(loginReply, &QNetworkReply::finished, this, &LoginWindow::OnLoginFinished);
}


void LoginWindow::Register() {
    auto login = ui->line_login->text();
    auto pass = ui->line_password->text();

    auto data = User{login, pass}.ToJsonByteArray();

    url.setPath("/api/users");
    req.setUrl(url);
    req.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    registerReply = network->post(req, data);
    connect(registerReply, &QNetworkReply::finished, this, &LoginWindow::OnRegisterFinished);
}

void LoginWindow::ConfigureSsl() {
    QSslConfiguration cfg = req.sslConfiguration();
    cfg.setProtocol(QSsl::TlsV1_3OrLater);
    cfg.addCaCertificates("../ssl/rootca.crt", QSsl::Pem);
    cfg.setPeerVerifyMode(QSslSocket::VerifyPeer);
    req.setSslConfiguration(cfg);
    req.setPeerVerifyName("usr"); //verify cert CN

    url.setScheme("https");
    url.setHost(HostInfo::ip);
    url.setPort(HostInfo::port);

}


void LoginWindow::OnRegisterFinished() {
    if (registerReply->error() == QNetworkReply::NoError) {
        QVariant statusCode = registerReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        int status = statusCode.toInt();
        if (status == 200) {

        } else {

        }

        QByteArray responseData = registerReply->readAll();
        qDebug() << responseData;
    } else {
        qDebug() << "Network request error:" << registerReply->errorString();
    }
}

void LoginWindow::OnLoginFinished() {
    if (loginReply->error() == QNetworkReply::NoError) {
        QVariant statusCode = loginReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        int status = statusCode.toInt();

        QByteArray responseData = loginReply->readAll();
        qDebug() << responseData;
        QJsonDocument doc = QJsonDocument::fromJson(responseData);
        QJsonObject json = doc.object();

        if (status == 200) { //if login successful send websocket upgrade request
            url.setScheme("wss");
            url.setPath("/");
            req.setUrl(url);
            req.setRawHeader("Upgrade", "websocket");
            req.setRawHeader("Connection", "upgrade");
            req.setRawHeader("Sec-WebSocket-Key", "123456789");
            req.setRawHeader("Sec-WebSocket-Version", "13");
            //set jwt token
            req.setRawHeader("Authorization", json.value("Token").toString().toLocal8Bit());

            emit LoginSuccess(req, json.value("login").toString());
            this->close();
        }
    } else {
        qDebug() << "Network request error:" << loginReply->errorString();
    }
}

