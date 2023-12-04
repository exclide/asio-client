#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <vector>
#include <unordered_map>

QT_BEGIN_NAMESPACE

class UiChatWindow
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;

    std::unordered_map<QString, QWidget*> tabMap;

    void setupUi(QWidget *chatWindow)
    {
        if (chatWindow->objectName().isEmpty())
            chatWindow->setObjectName("WS Chat");
        chatWindow->resize(600, 400);
        gridLayout = new QGridLayout(chatWindow);
        gridLayout->setObjectName("gridLayout");

        tabWidget = new QTabWidget(chatWindow);
        tabWidget->setObjectName("tabWidget");

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);


        chatWindow->setWindowTitle("WS Chat");

        QMetaObject::connectSlotsByName(chatWindow);
    }


    void addNewTab(const QString& login = "none") {

        auto tabNew = new QWidget();
        tabNew->setObjectName(login);

        tabWidget->addTab(tabNew, QString());
        tabWidget->setTabText(tabWidget->indexOf(tabNew), login);

        auto layout = new QGridLayout(tabNew);

        auto line = new QLineEdit(tabNew);
        line->setObjectName(login + "line");
        layout->addWidget(line, 2, 0, 1, 1);

        auto button = new QPushButton(tabNew);
        button->setObjectName(login + "button");
        button->setText("send");
        layout->addWidget(button, 2, 1, 1, 1);

        auto list = new QListView(tabNew);
        list->setObjectName(login + "msgbox");
        layout->addWidget(list, 1, 0, 1, 2);

        tabMap[login] = tabNew;

/*        auto child = tabNew->children();
        for (auto ch : child) {
            ch->objectName();
        }*/
    }

};

namespace Ui {
    class ChatWindow: public UiChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
