#include <QApplication>
#include "ChatWindow.h"
#include "ChatClient.h"
#include "LoginWindow.h"
#include "Test.h"

int main(int argc, char *argv[]) {
    QApplication app{argc, argv};
    LoginWindow loginWindow;
    loginWindow.show();
    //ChatWindow chatWindow{new ChatClient()};
    Test test;

    QObject::connect(&loginWindow, &LoginWindow::LoginSuccess, &test, &Test::Init);


    return QApplication::exec();
}
