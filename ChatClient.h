//
// Created by asd on 23-Oct-23.
//

#ifndef ASIO_CLIENT_CHATCLIENT_H
#define ASIO_CLIENT_CHATCLIENT_H

#include "Asio.h"
#include <queue>

class ChatClient {
public:
    ChatClient(io_context& ioc, tcp::endpoint& endpoint);

    void Write(const std::string& msg);
    void DoWrite();
    void DoConnect(tcp::endpoint& endpoint);
    void DoRead();

private:
    tcp::socket socket;
    std::string data;
    std::queue<std::string> sendq;
};


#endif //ASIO_CLIENT_CHATCLIENT_H
