//
// Created by w on 04.12.23.
//

#ifndef ASIO_CLIENT_UILOGINWINDOW_H
#define ASIO_CLIENT_UILOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class UiLoginWindow
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *line_login;
    QLineEdit *line_password;
    QHBoxLayout *horizontalLayout;
    QPushButton *button_login;
    QPushButton *button_register;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(342, 165);
        gridLayout_2 = new QGridLayout(LoginWindow);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        line_login = new QLineEdit(LoginWindow);
        line_login->setObjectName("line_login");

        verticalLayout->addWidget(line_login);

        line_password = new QLineEdit(LoginWindow);
        line_password->setObjectName("line_password");
        line_password->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(line_password);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        button_login = new QPushButton(LoginWindow);
        button_login->setObjectName("button_login");

        horizontalLayout->addWidget(button_login);

        button_register = new QPushButton(LoginWindow);
        button_register->setObjectName("button_register");

        horizontalLayout->addWidget(button_register);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "LoginWindow", nullptr));
        line_login->setPlaceholderText(QCoreApplication::translate("LoginWindow", "username", nullptr));
        line_password->setPlaceholderText(QCoreApplication::translate("LoginWindow", "password", nullptr));
        button_login->setText(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        button_register->setText(QCoreApplication::translate("LoginWindow", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public UiLoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif //ASIO_CLIENT_UILOGINWINDOW_H
