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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QApplication>
#include <QtGui>
class GraphicsScene;
class View;
class CardPixmap;
class CheckerThread;
class NetworkThread;
class BetControls;
class TextItem;
class GfxRectItem;
class MainWindow : public QMainWindow
   {
      Q_OBJECT
      
   public:
      MainWindow(QWidget *parent = 0);
      ~MainWindow();
      GraphicsScene* m_scene;
      View* m_view;
      QHash<int, CardPixmap*> m_cards;
      CardPixmap* new_cardpixmap;
      CheckerThread* m_checker;
      QHash<int, QList<CardPixmap*> > m_game_cards;
      QTimer* m_timer_randomize;
      NetworkThread* m_network;
      BetControls* m_bet_controls;
      TextItem* new_textItem;
      GfxRectItem* new_rectItem;
      QHash<int, TextItem*> m_nameTextItems;
      QHash<int, TextItem*> m_chipTextItems;
      QHash<int, GfxRectItem*> m_turnRectItems;
   signals:
      void signal_send_invalid_index(int entry_number);
   public slots:
      void slot_receive_index_change(int entry_number, int index_number);
      void slot_randomize_all();
      void slot_write_cardpos_to_xml(int entry_number, qreal posX, qreal posY);
      void slot_populate_seat(int seat_num, QString nickname, int chip_count);
      void slot_update_current_turn(int current_turn);

   private slots:
         void iconActivated(QSystemTrayIcon::ActivationReason reason);
      private:
         void createActions();
         void createTrayIcon();
         QAction *minimizeAction;
         QAction *maximizeAction;
         QAction *restoreAction;
         QAction *quitAction;

         QSystemTrayIcon *trayIcon;
         QMenu *trayIconMenu;
   protected:
         void closeEvent(QCloseEvent *event);

   };

#endif // MAINWINDOW_H
