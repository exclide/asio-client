//
// Created by w on 02.12.23.
//

#ifndef ASIO_CLIENT_LOGINWINDOW_H
#define ASIO_CLIENT_LOGINWINDOW_H

#include <QWidget>
#include <QNetworkAccessManager>


QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QWidget {
Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

    ~LoginWindow() override;

private:
    Ui::LoginWindow* ui;
    QNetworkAccessManager* network = new QNetworkAccessManager();
    QNetworkRequest req;
    QNetworkReply* loginReply;
    QNetworkReply* registerReply;
    QUrl url;

    void ConfigureSsl();

signals:
    void LoginSuccess(QNetworkRequest req);

private slots:
    void Login();
    void Register();
    void OnLoginFinished();
    void OnRegisterFinished();
};


#endif //ASIO_CLIENT_LOGINWINDOW_H
