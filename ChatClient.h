//
// Created by asd on 23-Oct-23.
//

#ifndef ASIO_CLIENT_CHATCLIENT_H
#define ASIO_CLIENT_CHATCLIENT_H

#include "Asio.h"
#include <queue>
#include <QWidget>
#include <QObject>

class ChatClient : public QObject {
Q_OBJECT
Q_DISABLE_COPY(ChatClient)

public:
    ChatClient(io_context& ioc, ssl::context& ctx);

    void Write(const std::string& msg);
    void DoWrite();
    void StartConnect(const tcp::endpoint& endpoint);
    void DoConnect(const tcp::endpoint& endpoint);
    void DoRead();
    void DoHandshake();

private:
    //tcp::socket socket;
    ssl::stream<tcp::socket> socket;
    std::string data;
    std::queue<std::string> sendq;

signals:
    void MessageReceived(std::string msg);
    void ConnectedToServer();
};


#endif //ASIO_CLIENT_CHATCLIENT_H
