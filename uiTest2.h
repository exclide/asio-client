#ifndef UI_TEST2_H
#define UI_TEST2_H

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

class UiTest2
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;

    std::unordered_map<QString, QWidget*> tabMap;

    void setupUi(QWidget *Test)
    {
        if (Test->objectName().isEmpty())
            Test->setObjectName("WS Chat");
        Test->resize(600, 400);
        gridLayout = new QGridLayout(Test);
        gridLayout->setObjectName("gridLayout");

        tabWidget = new QTabWidget(Test);
        tabWidget->setObjectName("tabWidget");

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);


        Test->setWindowTitle("WS Chat");

        QMetaObject::connectSlotsByName(Test);
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
    class Test: public UiTest2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST2_H
