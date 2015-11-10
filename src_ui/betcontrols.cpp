/****************************************************************************
**
** Copyright (C) 2012 Mike Nickaloff.
** All rights reserved.
** Contact: seppfuv@gmail.com  (http://www.alamedasbestcatering.com/mike)
**
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

#include "betcontrols.h"
#include "ui_betcontrols.h"
#include <QTimer>
#include <QtGui>
BetControls::BetControls(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::BetControls)
   {
      ui->setupUi(this);
      this->m_timer_autocheck = new QTimer(this);
      m_timer_autocheck->connect(this->m_timer_autocheck, SIGNAL(timeout()), ui->button_check, SLOT(click()));
      m_timer_autocheck->setInterval(550);
      m_chips = 0;
      m_minimum = 0;
   }

BetControls::~BetControls()
   {
      delete ui;
   }

void BetControls::changeEvent(QEvent *e)
   {
      QWidget::changeEvent(e);
      switch (e->type()) {
         case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
         default:
            break;
         }
   }

void BetControls::on_button_check_clicked()
{
      if (this->m_timer_autocheck->isActive()) {
            this->m_timer_autocheck->stop();
         }
      if (ui->button_check->text() == "CHECK") {
            emit this->signal_check();
         } else {
            emit this->signal_bet(m_minimum);
         }
}

void BetControls::on_button_bet_clicked()
{
      bool ok;
        int text = QInputDialog::getInt(this, tr("Bet Amount"),
                                              tr("Input Amount to Bet"),  m_minimum, m_minimum, this->m_chips, 1, &ok);
        if (ok)
           emit this->signal_bet(text);

}

void BetControls::on_button_fold_clicked()
{
      if (this->m_timer_autocheck->isActive()) {
            this->m_timer_autocheck->stop();
         }
emit this->signal_fold();
}
void BetControls::slot_wait() {
      ui->button_bet->setEnabled(false);
      ui->button_check->setEnabled(false);
      ui->button_fold->setEnabled(false);
      this->m_timer_autocheck->stop();
   }

void BetControls::slot_turn(int amt) {
      this->m_timer_autocheck->stop();
      ui->button_bet->setEnabled(true);
      ui->button_check->setEnabled(true);
      if (amt > 0) {
            //ui->button_check->setEnabled(false);
            ui->button_check->setText("CALL");
            ui->button_bet->setText("RAISE");
         } else {
            //ui->button_check->setEnabled(true);
             ui->button_check->setText("CHECK");
             ui->button_bet->setText("BET");
         }
      this->m_minimum = amt;
      ui->button_fold->setEnabled(true);
      //if (m_minimum == 0) {
            if (ui->checkbox_autocheck->isChecked()) {

                  this->m_timer_autocheck->start();
                  //QTimer::singleShot(3000, this, SLOT(on_button_check_clicked()));
               }
        // }
   }
void BetControls::slot_chips(int amt) {
      this->m_chips = amt;
      qDebug() << "Chip Count set to " << m_chips;
   }
