#include <QApplication>
#include "LoginWindow.h"
#include "ChatWindow.h"

int main(int argc, char *argv[]) {
    QApplication app{argc, argv};
    LoginWindow loginWindow;
    loginWindow.show();
    ChatWindow chatWindow;

    QObject::connect(&loginWindow, &LoginWindow::LoginSuccess, &chatWindow, &ChatWindow::Init);
    QObject::connect(&chatWindow, &ChatWindow::ConnectionLost, &loginWindow, &LoginWindow::OnConnectionLost);

    return QApplication::exec();
}
