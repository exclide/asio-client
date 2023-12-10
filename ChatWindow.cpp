//
// Created by w on 03.12.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Test.h" resolved

#include "ChatWindow.h"

#include <utility>
#include "UiChatWindow.h"
#include "User.h"


ChatWindow::ChatWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::ChatWindow) {
    ui->setupUi(this);
}

ChatWindow::~ChatWindow() {
    delete ui;
}

void ChatWindow::Init(QNetworkRequest req, QString login) {
    ui->clearTabs();
    selfLogin = std::move(login);
    chatClient->Connect(req);
    connect(this->chatClient, &ChatClient::MessageReceived, this, &ChatWindow::HandleJsonData);
    connect(this->chatClient, &ChatClient::ConnectionLost, this, &ChatWindow::OnConnectionLost);

    this->show();
}

void ChatWindow::HandleJsonData(const QString& jsonData) {
    QByteArray responseData = jsonData.toLocal8Bit();
    qDebug() << responseData;
    QJsonDocument doc = QJsonDocument::fromJson(responseData);
    QJsonObject json = doc.object();

    auto usersJson = json.value("users").toArray();
    auto msgsJson = json.value("messages").toArray();

    std::vector<User> users;
    std::vector<DbMessage> msgs;

    for (auto e : usersJson) {
        User user;
        user.FromJsonObject(e.toObject());
        users.push_back(user);
    }

    for (auto e : msgsJson) {
        DbMessage msg;
        msg.FromJsonObject(e.toObject());
        msgs.push_back(msg);
    }

    for (auto& e : users) {
        qDebug() << e.login;
        ui->addNewTab(e.login);

        auto tab = ui->tabMap[e.login];
        auto model = modelMap[e.login] = new QStandardItemModel(tab);
        model->insertColumn(0);
        auto msgBox = tab->findChild<QListView*>(e.login + "msgbox");
        msgBox->setModel(model);

        auto pushButton = tab->findChild<QPushButton*>(e.login + "button");
        auto lineEdit = tab->findChild<QLineEdit*>(e.login + "line");
        connect(pushButton, &QPushButton::clicked, this, &ChatWindow::SendChatMessage);
        connect(lineEdit, &QLineEdit::returnPressed, this, &ChatWindow::SendChatMessage);
    }

    for (auto& e : msgs) {
        qDebug() << e.text;
        AddDbMessage(e);
    }


    disconnect(this->chatClient, &ChatClient::MessageReceived, this, &ChatWindow::HandleJsonData);
    connect(this->chatClient, &ChatClient::MessageReceived, this, &ChatWindow::ReceiveMessage);
}

void ChatWindow::SendChatMessage() {
    qDebug() << "SendChatMessage";
    auto login = ui->tabWidget->currentWidget()->objectName();
    auto lineEdit = ui->tabWidget->currentWidget()->findChild<QLineEdit*>(login + "line");
    auto text = lineEdit->text();
    lineEdit->clear();

    QJsonObject obj;
    obj["to"] = login;
    obj["text"] = text;

    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();

    AddTextToModel(text, login, Qt::AlignRight);

    chatClient->Write(data);
}

//sender: asd1
//receiver: asd2
//text: asd1 to asd2
//date: int

void ChatWindow::AddDbMessage(const DbMessage &msg) {
    auto targetTab = msg.sender == selfLogin ? msg.receiver : msg.sender;
    auto alignment = msg.sender == selfLogin ? Qt::AlignRight : Qt::AlignLeft;

    AddTextToModel(msg.text, targetTab, alignment);
}

void ChatWindow::AddTextToModel(const QString& text, const QString& sender, Qt::Alignment alignment) {
    auto model = modelMap[sender];

    int newRow = model->rowCount();

    auto item = new QStandardItem;
    item->setText(text);
    item->setTextAlignment(alignment);
    item->setFlags(~(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsDragEnabled));
    QFont jetbrains("Jetbrains Mono", 12);
    item->setFont(jetbrains);

    model->insertRow(newRow, item);
    auto msgBox = ui->tabMap[sender]->findChild<QListView*>(sender + "msgbox");
    msgBox->scrollToBottom();
}

void ChatWindow::ReceiveMessage(const QString &msg) {
    qDebug() << "ReceiveMessage\n" << msg;
    //add message to the model with the given login
    QJsonDocument doc = QJsonDocument::fromJson(msg.toLocal8Bit());
    QJsonObject json = doc.object();
    auto sender = json.value("sender").toString();
    //auto receiver = json.value("receiver").toString();
    auto text = json.value("text").toString();
    auto receiverWidget = ui->tabMap[sender];

    if (!receiverWidget) {
        qDebug() << "Receiver widget was null";
        return;
    }

    if (sender != selfLogin)
        AddTextToModel(text, sender);
}

void ChatWindow::OnConnectionLost() {
    this->hide();

    emit ConnectionLost();
}
