/********************************************************************************
** Form generated from reading UI file 'mycustomwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCUSTOMWIDGET_H
#define UI_MYCUSTOMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyCustomWidget
{
public:
    QLabel *labelR;
    QLabel *labelG;
    QLabel *labelB;

    void setupUi(QWidget *MyCustomWidget)
    {
        if (MyCustomWidget->objectName().isEmpty())
            MyCustomWidget->setObjectName("MyCustomWidget");
        MyCustomWidget->resize(760, 519);
        labelR = new QLabel(MyCustomWidget);
        labelR->setObjectName("labelR");
        labelR->setGeometry(QRect(600, 180, 49, 16));
        labelG = new QLabel(MyCustomWidget);
        labelG->setObjectName("labelG");
        labelG->setGeometry(QRect(600, 210, 49, 16));
        labelB = new QLabel(MyCustomWidget);
        labelB->setObjectName("labelB");
        labelB->setGeometry(QRect(600, 250, 49, 16));

        retranslateUi(MyCustomWidget);

        QMetaObject::connectSlotsByName(MyCustomWidget);
    } // setupUi

    void retranslateUi(QWidget *MyCustomWidget)
    {
        MyCustomWidget->setWindowTitle(QCoreApplication::translate("MyCustomWidget", "Form", nullptr));
        labelR->setText(QCoreApplication::translate("MyCustomWidget", "TextLabel", nullptr));
        labelG->setText(QCoreApplication::translate("MyCustomWidget", "TextLabel", nullptr));
        labelB->setText(QCoreApplication::translate("MyCustomWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyCustomWidget: public Ui_MyCustomWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCUSTOMWIDGET_H
