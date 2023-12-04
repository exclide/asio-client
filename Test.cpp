//
// Created by w on 03.12.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Test.h" resolved

#include "Test.h"
#include "uiTest2.h"
#include "User.h"


Test::Test(QWidget *parent) :
        QWidget(parent), ui(new Ui::Test) {
    ui->setupUi(this);
}

Test::~Test() {
    delete ui;
}

void Test::Init(QNetworkRequest req) {
    chatClient->Connect(req);
    connect(this->chatClient, &ChatClient::MessageReceived, this, &Test::HandleJsonData);


    this->show();
}

void Test::HandleJsonData(const QString& jsonData) {
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
        connect(pushButton, &QPushButton::clicked, this, &Test::SendChatMessage);
        connect(lineEdit, &QLineEdit::returnPressed, this, &Test::SendChatMessage);
    }

    for (auto& e : msgs) {
        qDebug() << e.text;
        AddDbMessage(e);
    }


    disconnect(this->chatClient, &ChatClient::MessageReceived, this, &Test::HandleJsonData);
    connect(this->chatClient, &ChatClient::MessageReceived, this, &Test::ReceiveMessage);
}

void Test::SendChatMessage() {
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


void Test::AddDbMessage(const DbMessage &msg) {
    msg.
}

void Test::AddTextToModel(const QString& text, const QString& sender, Qt::Alignment alignment) {
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

void Test::ReceiveMessage(const QString &msg) {
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

    AddTextToModel(text, sender);
}