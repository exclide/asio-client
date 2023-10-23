//
// Created by asd on 23-Oct-23.
//

#include "ChatClient.h"

ChatClient::ChatClient(io_context &ioc, tcp::endpoint &endpoint) : socket(ioc) {
    DoConnect(endpoint);
}

void ChatClient::Write(const std::string &msg) {
    boost::asio::post(socket.get_executor(), [this, msg]() {
        sendq.push(msg);
        //нужна очередь, чтобы избежать вызовов async_write до завершения предыдущих записей
        if (sendq.size() == 1) {
            DoWrite();
        }
    });
}

void ChatClient::DoWrite() {
    boost::asio::async_write(
            socket,
            boost::asio::buffer(sendq.front()),
            [this] (error_code err, size_t bytes) {
                sendq.pop();

                if (!sendq.empty()) {
                    DoWrite();
                }
            });
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
