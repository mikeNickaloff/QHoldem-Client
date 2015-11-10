/********************************************************************************
** Form generated from reading UI file 'betcontrols.ui'
**
** Created: Thu Nov 28 12:44:43 2013
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BETCONTROLS_H
#define UI_BETCONTROLS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BetControls
{
public:
    QPushButton *button_check;
    QPushButton *button_bet;
    QPushButton *button_fold;
    QCheckBox *checkbox_autocheck;

    void setupUi(QWidget *BetControls)
    {
        if (BetControls->objectName().isEmpty())
            BetControls->setObjectName(QString::fromUtf8("BetControls"));
        BetControls->resize(759, 53);
        button_check = new QPushButton(BetControls);
        button_check->setObjectName(QString::fromUtf8("button_check"));
        button_check->setGeometry(QRect(580, 10, 161, 34));
        button_bet = new QPushButton(BetControls);
        button_bet->setObjectName(QString::fromUtf8("button_bet"));
        button_bet->setGeometry(QRect(410, 10, 161, 34));
        button_fold = new QPushButton(BetControls);
        button_fold->setObjectName(QString::fromUtf8("button_fold"));
        button_fold->setGeometry(QRect(240, 10, 161, 34));
        checkbox_autocheck = new QCheckBox(BetControls);
        checkbox_autocheck->setObjectName(QString::fromUtf8("checkbox_autocheck"));
        checkbox_autocheck->setGeometry(QRect(20, 10, 141, 29));
        checkbox_autocheck->setChecked(true);

        retranslateUi(BetControls);

        QMetaObject::connectSlotsByName(BetControls);
    } // setupUi

    void retranslateUi(QWidget *BetControls)
    {
        BetControls->setWindowTitle(QApplication::translate("BetControls", "Form", 0, QApplication::UnicodeUTF8));
        button_check->setText(QApplication::translate("BetControls", "Check", 0, QApplication::UnicodeUTF8));
        button_bet->setText(QApplication::translate("BetControls", "Bet", 0, QApplication::UnicodeUTF8));
        button_fold->setText(QApplication::translate("BetControls", "Fold", 0, QApplication::UnicodeUTF8));
        checkbox_autocheck->setText(QApplication::translate("BetControls", "Auto - Check", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BetControls: public Ui_BetControls {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BETCONTROLS_H
