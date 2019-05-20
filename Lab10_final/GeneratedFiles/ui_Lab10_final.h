/********************************************************************************
** Form generated from reading UI file 'Lab10_final.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB10_FINAL_H
#define UI_LAB10_FINAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lab10_finalClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lab10_finalClass)
    {
        if (Lab10_finalClass->objectName().isEmpty())
            Lab10_finalClass->setObjectName(QString::fromUtf8("Lab10_finalClass"));
        Lab10_finalClass->resize(600, 400);
        menuBar = new QMenuBar(Lab10_finalClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Lab10_finalClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lab10_finalClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Lab10_finalClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Lab10_finalClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Lab10_finalClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Lab10_finalClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Lab10_finalClass->setStatusBar(statusBar);

        retranslateUi(Lab10_finalClass);

        QMetaObject::connectSlotsByName(Lab10_finalClass);
    } // setupUi

    void retranslateUi(QMainWindow *Lab10_finalClass)
    {
        Lab10_finalClass->setWindowTitle(QApplication::translate("Lab10_finalClass", "Lab10_final", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lab10_finalClass: public Ui_Lab10_finalClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB10_FINAL_H
