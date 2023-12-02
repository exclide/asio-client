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
    QUrl url;

    void ConfigureSsl();
    QByteArray GetJsonData(const QString& login, const QString& pass);

signals:
    void LoginSuccess();

private slots:
    void Login();
    void Register();
};


#endif //ASIO_CLIENT_LOGINWINDOW_H
