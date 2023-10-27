//
// Created by asd on 23-Oct-23.
//

#include "ChatClient.h"

ChatClient::ChatClient(io_context& ioc, ssl::context& ctx) : socket(ioc, ctx) {
    socket.set_verify_mode(ssl::verify_peer);
    socket.set_verify_callback(ssl::host_name_verification("usr"));

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
                if (!err) {
                    sendq.pop();
                }

                if (!sendq.empty()) {
                    DoWrite();
                }
            });
}

void ChatClient::StartConnect(const tcp::endpoint& endpoint) {
    boost::asio::post(socket.get_executor(), [this, endpoint] () {
        DoConnect(endpoint);
    });
}

void ChatClient::DoConnect(const tcp::endpoint &endpoint) {
    socket.lowest_layer().async_connect(endpoint, [this](error_code ec) {
        if (!ec) {
            DoHandshake();
        }
    });
}

void ChatClient::DoHandshake() {
    socket.async_handshake(
            boost::asio::ssl::stream_base::client,
            [this](error_code err) {
                if (!err) {
                    emit ConnectedToServer();
                    DoRead();
                }
            });
}

void ChatClient::DoRead() {
    boost::asio::async_read_until(
            socket,
            boost::asio::dynamic_buffer(data),
            "\n",
            [this] (error_code ec, std::size_t bytes) {
                if (!ec) {
                    data.pop_back();
                    emit MessageReceived(data);
                    data.clear();
                }

                DoRead();
            });
}
