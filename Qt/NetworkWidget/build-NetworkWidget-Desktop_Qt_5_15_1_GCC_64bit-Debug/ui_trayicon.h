/********************************************************************************
** Form generated from reading UI file 'trayicon.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRAYICON_H
#define UI_TRAYICON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrayIcon
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TrayIcon)
    {
        if (TrayIcon->objectName().isEmpty())
            TrayIcon->setObjectName(QString::fromUtf8("TrayIcon"));
        TrayIcon->resize(800, 600);
        centralwidget = new QWidget(TrayIcon);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        TrayIcon->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TrayIcon);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        TrayIcon->setMenuBar(menubar);
        statusbar = new QStatusBar(TrayIcon);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        TrayIcon->setStatusBar(statusbar);

        retranslateUi(TrayIcon);

        QMetaObject::connectSlotsByName(TrayIcon);
    } // setupUi

    void retranslateUi(QMainWindow *TrayIcon)
    {
        TrayIcon->setWindowTitle(QCoreApplication::translate("TrayIcon", "TrayIcon", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrayIcon: public Ui_TrayIcon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAYICON_H
