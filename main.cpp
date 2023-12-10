#include <QApplication>
#include "LoginWindow.h"
#include "ChatWindow.h"

int main(int argc, char *argv[]) {
    QSettings settings("HostInfo.ini", QSettings::IniFormat);
    QString host = settings.value("HostInfo/host", "127.0.0.1").toString();
    int port = settings.value("HostInfo/port", 1234).toInt();
    HostInfo hostInfo{host, port};

    QApplication app{argc, argv};
    LoginWindow loginWindow{hostInfo};
    loginWindow.show();
    ChatWindow chatWindow;

    QObject::connect(&loginWindow, &LoginWindow::LoginSuccess, &chatWindow, &ChatWindow::Init);
    QObject::connect(&chatWindow, &ChatWindow::ConnectionLost, &loginWindow, &LoginWindow::OnConnectionLost);

    return QApplication::exec();
}
