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

#ifndef BETCONTROLS_H
#define BETCONTROLS_H

#include <QtGui/QWidget>

namespace Ui {
      class BetControls;
   }

class BetControls : public QWidget
   {
      Q_OBJECT
      
   public:
      explicit BetControls(QWidget *parent = 0);
      ~BetControls();
      QTimer* m_timer_autocheck;
      int m_chips;
      int m_minimum;
   signals:
      void signal_check();
      void signal_fold();
      void signal_bet(int amt);
      
   public slots:
      void slot_wait();
      void slot_turn(int amt);
      void slot_chips(int amt);
   protected:
      void changeEvent(QEvent *e);
      
   private slots:
      void on_button_check_clicked();

      void on_button_bet_clicked();

      void on_button_fold_clicked();

   private:
      Ui::BetControls *ui;
   };

#endif // BETCONTROLS_H
