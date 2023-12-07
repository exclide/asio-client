//
// Created by w on 07.12.23.
//

#ifndef ASIO_CLIENT_TABWIDGET_H
#define ASIO_CLIENT_TABWIDGET_H

#include <QApplication>
#include <QStyleOptionTab>
#include <QStylePainter>
#include <QTabBar>
#include <QTabWidget>
#include "TabBar.h"

class TabWidget : public QTabWidget
{
public:
    explicit TabWidget(QWidget *parent = nullptr) : QTabWidget(parent) {
        setTabBar(new TabBar);
        setTabPosition(QTabWidget::West);
        setStyleSheet("QTabBar::tab {height: 150px; width: 50px; color: #ffffff; font-family: JetBrains Mono; font-size: 15px;}\n"
                      "QTabBar::tab:selected {color: red; }"
                      "QTabBar::tab:hover {font-weight: bold; }");

    }
};

#endif //ASIO_CLIENT_TABWIDGET_H
