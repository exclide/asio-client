//
// Created by w on 02.12.23.
//

#ifndef ASIO_CLIENT_LOGINWINDOW_H
#define ASIO_CLIENT_LOGINWINDOW_H

#include <QWidget>
#include <QNetworkAccessManager>
#include "HostInfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QWidget {
Q_OBJECT

public:
    explicit LoginWindow(HostInfo hostInfo, QWidget *parent = nullptr);

    ~LoginWindow() override;

private:
    Ui::LoginWindow* ui;
    QNetworkAccessManager* network = new QNetworkAccessManager();
    QNetworkRequest req;
    QNetworkReply* loginReply = nullptr;
    QNetworkReply* registerReply = nullptr;
    QUrl url;
    HostInfo hostInfo;

    void ConfigureSsl();

signals:
    void LoginSuccess(QNetworkRequest req, QString login);

public slots:
    void OnConnectionLost();

private slots:
    void Login();
    void Register();
    void OnLoginFinished();
    void OnRegisterFinished();
};


#endif //ASIO_CLIENT_LOGINWINDOW_H
