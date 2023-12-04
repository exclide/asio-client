//
// Created by asd on 24-Oct-23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_test.h" resolved

#include "ChatWindow.h"
#include "ui_ChatWindow.h"


ChatWindow::ChatWindow(ChatClient* chatClient) :
        QWidget(nullptr),
        ui(new Ui::ChatWindow),
        chatModel(new QStandardItemModel(this)),
        chatClient(chatClient) {

    ui->setupUi(this);

    chatModel->insertColumn(0);
    ui->list_msgbox->setModel(chatModel);

    connect(ui->button_send, &QPushButton::clicked, this, &ChatWindow::SendChatMessage);
    connect(ui->line_msg, &QLineEdit::returnPressed, this, &ChatWindow::SendChatMessage);
    connect(this->chatClient, &ChatClient::MessageReceived, this, &ChatWindow::ReceiveChatMessage);
}

ChatWindow::~ChatWindow() {
    delete ui;
}

void ChatWindow::SendChatMessage() {
    qDebug() << "SendChatMessage";
    auto msg = ui->line_msg->text();
    msg += '\n';
    ui->line_msg->clear();

    chatClient->Write(msg);
}

void ChatWindow::ReceiveChatMessage(const QString& msg) {
    qDebug() << "Received message: " << msg;
    QString qmsg = msg.chopped(1);

    int newRow = chatModel->rowCount();

    chatModel->insertRow(newRow);
    chatModel->setData(chatModel->index(newRow, 0), qmsg);

    ui->list_msgbox->scrollToBottom();
}


void ChatWindow::Init(QNetworkRequest req) {

    //make http get for contacts
    //get history message for each contact
    chatClient->Connect(req);

    this->show();
}
