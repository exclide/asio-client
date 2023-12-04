//
// Created by w on 03.12.23.
//

#ifndef ASIO_CLIENT_CHATWINDOW_H
#define ASIO_CLIENT_CHATWINDOW_H

#include <QWidget>
#include <QStandardItemModel>
#include "ChatClient.h"
#include "DbMessage.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ChatWindow; }
QT_END_NAMESPACE

class ChatWindow : public QWidget {
Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow() override;
    void Init(QNetworkRequest req, QString login);
    void AddDbMessage(const DbMessage &msg);

private slots:
    void HandleJsonData(const QString& jsonData);
    void ReceiveMessage(const QString& msg);
    void SendChatMessage();

private:
    Ui::ChatWindow *ui;
    ChatClient* chatClient = new ChatClient();
    std::unordered_map<QString, QStandardItemModel*> modelMap;
    QString selfLogin;

    void AddTextToModel(const QString& text, const QString& sender, Qt::Alignment alignment = Qt::AlignLeft) ;
};


#endif //ASIO_CLIENT_CHATWINDOW_H
