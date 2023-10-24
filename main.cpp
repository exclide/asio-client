#include <QApplication>
#include <QPushButton>
#include "ChatWindow.h"
#include "Asio.h"

int main(int argc, char *argv[]) {
    io_context ioc;
    auto workGuard = boost::asio::make_work_guard(ioc);
    std::thread{[&ioc] { ioc.run(); }}.detach();

    QApplication app{argc, argv};
    ChatWindow chatWindow{new ChatClient{ioc}};
    chatWindow.show();

    return QApplication::exec();
}
