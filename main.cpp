#include <QApplication>
#include <QPushButton>
#include "ChatWindow.h"
#include "ChatClient.h"

int main(int argc, char *argv[]) {
    QApplication app{argc, argv};
    ChatWindow chatWindow{new ChatClient()};
    chatWindow.show();


    return QApplication::exec();
}
