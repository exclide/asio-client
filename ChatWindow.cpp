//
// Created by asd on 24-Oct-23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_test.h" resolved

#include "ChatWindow.h"
#include "ui_ChatWindow.h"


ChatWindow::ChatWindow(ChatClient* client) :
        QWidget(nullptr),
        ui(new Ui::ChatWindow),
        chatModel(new QStandardItemModel(this)),
        client(client) {
    ui->setupUi(this);

    chatModel->insertColumn(0);
    ui->list_msgbox->setModel(chatModel);

    connect(ui->button_send, &QPushButton::clicked, this, &ChatWindow::SendChatMessage);
    connect(ui->button_connect, &QPushButton::clicked, this, &ChatWindow::ConnectToServer);
    connect(ui->line_msg, &QLineEdit::returnPressed, this, &ChatWindow::SendChatMessage);
    connect(this->client, &ChatClient::MessageReceived, this, &ChatWindow::ReceiveChatMessage);
}

ChatWindow::~ChatWindow() {
    delete ui;
}

void ChatWindow::SendChatMessage() {
    std::string msg = ui->line_msg->text().toStdString();
    msg += "\n";
    ui->line_msg->clear();

    client->Write(msg);
}

void ChatWindow::ReceiveChatMessage(const std::string& msg) {
    QString qmsg = QString::fromStdString(msg);

    int newRow = chatModel->rowCount();

    chatModel->insertRow(newRow);
    chatModel->setData(chatModel->index(newRow, 0), qmsg);

    ui->list_msgbox->scrollToBottom();
}

void ChatWindow::ConnectToServer() {
    const std::string ip = ui->line_ip->text().toStdString();
    const int port = ui->line_port->text().toInt();

    client->StartConnect(tcp::endpoint(address::from_string(ip), port));
}
