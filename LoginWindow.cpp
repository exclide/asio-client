//
// Created by w on 02.12.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoginWindow.h" resolved

#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "ChatClient.h"
#include "ChatWindow.h"
#include "HostInfo.h"

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

    auto data = GetJsonData(login, pass);

    url.setPath("/api/login");
    req.setUrl(url);
    req.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    QNetworkReply* reply = network->post(req, data);
    //send http auth request
    if (reply->error()) {
        qDebug() << reply->errorString();
    } else {
        qDebug() << "No error";
    }
    //need http client somewhere here

    //if it returns OK, show chat window
    this->close();
    emit LoginSuccess();
}


void LoginWindow::Register() {
    auto login = ui->line_login->text();
    auto pass = ui->line_password->text();

    auto data = GetJsonData(login, pass);

    url.setPath("/api/users");
    req.setUrl(url);
    network->post(req, data);
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

QByteArray LoginWindow::GetJsonData(const QString &login, const QString &pass) {
    QJsonObject obj;
    obj["login"] = login;
    obj["password"] = pass;
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();

    return data;
}
