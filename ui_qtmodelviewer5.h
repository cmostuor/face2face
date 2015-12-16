/********************************************************************************
** Form generated from reading UI file 'qtmodelviewer5.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTMODELVIEWER5_H
#define UI_QTMODELVIEWER5_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtModelViewer5Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtModelViewer5Class)
    {
        if (QtModelViewer5Class->objectName().isEmpty())
            QtModelViewer5Class->setObjectName(QStringLiteral("QtModelViewer5Class"));
        QtModelViewer5Class->resize(600, 400);
        menuBar = new QMenuBar(QtModelViewer5Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QtModelViewer5Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtModelViewer5Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtModelViewer5Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtModelViewer5Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtModelViewer5Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtModelViewer5Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtModelViewer5Class->setStatusBar(statusBar);

        retranslateUi(QtModelViewer5Class);

        QMetaObject::connectSlotsByName(QtModelViewer5Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtModelViewer5Class)
    {
        QtModelViewer5Class->setWindowTitle(QApplication::translate("QtModelViewer5Class", "QtModelViewer5", 0));
    } // retranslateUi

};

namespace Ui {
    class QtModelViewer5Class: public Ui_QtModelViewer5Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTMODELVIEWER5_H
