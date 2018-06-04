/********************************************************************************
** Form generated from reading UI file 'bro.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BRO_H
#define UI_BRO_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bro
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWebView *webView;

    void setupUi(QMainWindow *bro)
    {
        if (bro->objectName().isEmpty())
            bro->setObjectName(QStringLiteral("bro"));
        bro->resize(1024, 768);
        centralWidget = new QWidget(bro);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        webView = new QWebView(centralWidget);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));

        gridLayout->addWidget(webView, 0, 0, 1, 1);

        bro->setCentralWidget(centralWidget);

        retranslateUi(bro);

        QMetaObject::connectSlotsByName(bro);
    } // setupUi

    void retranslateUi(QMainWindow *bro)
    {
        bro->setWindowTitle(QApplication::translate("bro", "bro", 0));
    } // retranslateUi

};

namespace Ui {
    class bro: public Ui_bro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BRO_H
