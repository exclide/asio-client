//
// Created by w on 03.12.23.
//

#ifndef ASIO_CLIENT_TEST_H
#define ASIO_CLIENT_TEST_H

#include <QWidget>
#include <QStandardItemModel>
#include "ChatClient.h"
#include "DbMessage.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Test; }
QT_END_NAMESPACE

class Test : public QWidget {
Q_OBJECT

public:
    explicit Test(QWidget *parent = nullptr);
    ~Test() override;
    void Init(QNetworkRequest req);
    void AddDbMessage(const DbMessage &msg);

private slots:
    void HandleJsonData(const QString& jsonData);
    void ReceiveMessage(const QString& msg);
    void SendChatMessage();

private:
    Ui::Test *ui;
    ChatClient* chatClient = new ChatClient();
    std::unordered_map<QString, QStandardItemModel*> modelMap;

    void AddTextToModel(const QString& text, const QString& sender, Qt::Alignment alignment = Qt::AlignLeft) ;
};


#endif //ASIO_CLIENT_TEST_H
