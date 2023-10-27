#include <QApplication>
#include <QPushButton>
#include "ChatWindow.h"
#include "Asio.h"

int main(int argc, char *argv[]) {
    io_context ioc;
    auto workGuard = boost::asio::make_work_guard(ioc); //keep ioc running

    ssl::context ctx(ssl::context::sslv23);
    ctx.load_verify_file("../ssl/rootca.crt");

    std::thread{[&ioc] { ioc.run(); }}.detach();

    QApplication app{argc, argv};
    ChatWindow chatWindow{new ChatClient{ioc, ctx}};
    chatWindow.show();

    return QApplication::exec();
}
