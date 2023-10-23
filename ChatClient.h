//
// Created by asd on 23-Oct-23.
//

#ifndef ASIO_CLIENT_CHATCLIENT_H
#define ASIO_CLIENT_CHATCLIENT_H

#include "Asio.h"

class ChatClient {
public:
    ChatClient(io_context& ioc, tcp::endpoint& endpoint);

    void Write(const std::string& msg);
    void DoWrite(const std::shared_ptr<std::string>& ss);
    void DoConnect(tcp::endpoint& endpoint);
    void DoRead();

private:
    tcp::socket socket;
    std::string data;
};


#endif //ASIO_CLIENT_CHATCLIENT_H
