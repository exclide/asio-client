#include <QApplication>
#include "ChatWindow.h"
#include "ChatClient.h"
#include "LoginWindow.h"

int main(int argc, char *argv[]) {
    QApplication app{argc, argv};
    LoginWindow loginWindow;
    loginWindow.show();
    ChatWindow chatWindow{new ChatClient()};

    QObject::connect(&loginWindow, &LoginWindow::LoginSuccess, &chatWindow, &ChatWindow::Init);

    return QApplication::exec();
}
