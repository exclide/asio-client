//
// Created by asd on 23-Oct-23.
//

#include "ChatClient.h"

ChatClient::ChatClient(io_context &ioc, tcp::endpoint &endpoint) : socket(ioc) {
    DoConnect(endpoint);
}

void ChatClient::Write(const std::string &msg) {
    auto ss = std::make_shared<std::string>(msg);

    boost::asio::post(socket.get_executor(), [this, ss]() {
        DoWrite(ss);
    });
}

void ChatClient::DoWrite(const std::shared_ptr<std::string> &ss) {
    boost::asio::async_write(socket, boost::asio::buffer(*ss),
                             [ss] (error_code err, size_t bytes) {});
}

void ChatClient::DoConnect(tcp::endpoint &endpoint) {
    socket.async_connect(endpoint, [this](error_code ec) {
        DoRead();
    });
}

void ChatClient::DoRead() {
    boost::asio::async_read_until(
            socket,
            boost::asio::dynamic_buffer(data),
            "\n",
            [this] (error_code ec, std::size_t bytes) {
                std::cout << data;
                data.clear();
                DoRead();
            });
}
