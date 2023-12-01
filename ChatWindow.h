//
// Created by asd on 24-Oct-23.
//

#ifndef QTWIDGET_CHATWINDOW_H
#define QTWIDGET_CHATWINDOW_H

#include <QWidget>
#include <QStandardItemModel>
#include "ChatClient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChatWindow; }
QT_END_NAMESPACE

class ChatWindow : public QWidget {
Q_OBJECT

public:
    explicit ChatWindow(ChatClient* chatClient);

    ~ChatWindow() override;

private slots:
    void SendChatMessage();
    void ConnectToServer();
    void ReceiveChatMessage(const QString& msg);

private:
    Ui::ChatWindow *ui;
    QStandardItemModel *chatModel;
    ChatClient* chatClient;
};


#endif //QTWIDGET_CHATWINDOW_H
