/********************************************************************************
** Form generated from reading UI file 'snipertool.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SNIPERTOOL_H
#define UI_SNIPERTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SniperToolClass
{
public:

    void setupUi(QWidget *SniperToolClass)
    {
        if (SniperToolClass->objectName().isEmpty())
            SniperToolClass->setObjectName(QStringLiteral("SniperToolClass"));
        SniperToolClass->resize(600, 400);

        retranslateUi(SniperToolClass);

        QMetaObject::connectSlotsByName(SniperToolClass);
    } // setupUi

    void retranslateUi(QWidget *SniperToolClass)
    {
        SniperToolClass->setWindowTitle(QApplication::translate("SniperToolClass", "SniperTool", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SniperToolClass: public Ui_SniperToolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SNIPERTOOL_H
