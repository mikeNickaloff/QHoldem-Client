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

#include "src_headers/toplevel.h"
#include "src_gfx/gfx.h"
#include "src_threads/threads.h"
#include "src_network/network.h"
#include "src_ui/betcontrols.h"
#include <QApplication>
#include <QtGui>
#include <QtCore/qstate.h>
#include <QSignalTransition>
#include <QAbstractTransition>
#include <QObject>
#include <QXmlStreamWriter>
#include <QDomDocument>
#include <QtXml>
//#include <QtXmlPatterns>
//#include <QXmlFormatter>
MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   {
      m_scene = new GraphicsScene(-350, -350, 700, 700, 0, 0, this);
      m_view = new View(m_scene);
      m_scene->_view = m_view;
      m_view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
      m_view->setCacheMode(QGraphicsView::CacheBackground);
      m_view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
      m_view->setParent(this);
      m_view->resize(800, 450);
      m_view->show();
      this->m_network = new NetworkThread(this);
      m_checker = new CheckerThread(this);


      QDomDocument m_card_data;
      QFile file(QApplication::applicationDirPath().append("/cardPos.xml"));
      if (!file.open(QIODevice::ReadOnly))
         // return;
         qDebug() << "Cannot Open";
      if (!m_card_data.setContent(&file)) {
            qDebug() << "Cannot Load";
           // file.close();
         }
     // file.close();
      QHash<int, QPointF> design_hash;
      QDomNodeList card_data = m_card_data.elementsByTagName("card");
      for (int i = 0; i < card_data.count(); i++) {
          QDomNode _card = card_data.item(i);
          int id = _card.toElement().attribute("entry").toInt();
          qreal posX = _card.toElement().attribute("posX").toDouble();
          qreal posY = _card.toElement().attribute("posY").toDouble();
          design_hash[id] = QPointF(posX, posY);
        //  qDebug() << "Entry" << id << "Loaded as" << design_hash.value(id);
          //qDebug()  user.firstChildElement("realname").text().toAscii() << "(" << user.firstChildElement("nickname").text().toLocal8Bit() << ")" << "has" << user.firstChildElement("chips").text().toInt() << "chips!";
         }




      // this->m_checker->start(QThread::InheritPriority);
      int g_num = 1;
      int g_count = 0;
      for (int i=1; i<16; ++i) {
            int d = i;
            while (d > 52) { d -= 52; }

            QPixmap pm = makePixmap(d);
            new_cardpixmap = new CardPixmap(pm, m_scene);
            new_cardpixmap->slot_set_card_index(d);
            g_count++;
            if (g_count > 15) {
                  g_num++;
                  g_count = 1;
               }
            QList<CardPixmap*> clist;
            clist << this->m_game_cards.value(g_num, QList<CardPixmap*>());
            clist << new_cardpixmap;
            this->m_game_cards[g_num] = clist;

            new_cardpixmap->setOffset(-pm.width() / 2, -pm.height() / 2);
            new_cardpixmap->setScale(CARD_SCALE);
            // new_cardpixmap->setPos(0 + ((0 + (i + (t * CARDS_PER_REEL))) * 5), -950);
            new_cardpixmap->setPos(-350 + (((i - 1) % 15) * ((pm.width() * CARD_SCALE) / 2)), -250 + ((i - 1) / 15) * (pm.height() / 2));
            new_cardpixmap->setFlag(QGraphicsItem::ItemSendsGeometryChanges, false);
            // item->setZValue((6 * 27) - ((t * 27) + i));
            new_cardpixmap->setZValue(i);
            m_scene->addItem(new_cardpixmap);
            m_cards[i] = new_cardpixmap;

            new_cardpixmap->setEntryNumber(i);
            if (design_hash.keys().contains(i))  {
                  new_cardpixmap->setPos(design_hash.value(i));
               }
            m_checker->connect(new_cardpixmap, SIGNAL(signal_request_random_index(int)), m_checker, SLOT(slot_request_random_number(int)));
            new_cardpixmap->connect(m_checker, SIGNAL(signal_return_random_number(int,int)), new_cardpixmap, SLOT(slot_receive_random_index(int,int)));
            this->connect(new_cardpixmap, SIGNAL(signal_report_index_change(int,int)), this, SLOT(slot_receive_index_change(int,int)));
            new_cardpixmap->connect(this, SIGNAL(signal_send_invalid_index(int)), new_cardpixmap, SLOT(slot_received_invalid_index_change(int)));
            new_cardpixmap->show();
            new_cardpixmap->connect(m_network, SIGNAL(signal_index_change(int,int)), new_cardpixmap, SLOT(slot_receive_random_index(int,int)));
            // new_cardpixmap->slot_randomize();
           // this->connect(new_cardpixmap, SIGNAL(signal_write_cardpos_to_xml(int,qreal,qreal)), this, SLOT(slot_write_cardpos_to_xml(int,qreal,qreal)));


         }
      QFont font;
      font.setPointSize(20);
      QList<QPointF> pos_list;
      pos_list    <<  QPointF(389.593, -345.747)
                   <<  QPointF(375.339, 77.6018)
                  <<  QPointF(-83.9367, 128.281)
                  <<  QPointF(-584.389, 115.611)
                   <<  QPointF(-579.638, -354.416)   ;
      for (int p=1; p<6; ++p) {
            new_textItem = new TextItem(QString("player %1 name").arg(p), this->m_scene);
            new_textItem->setDefaultTextColor(QColor(Qt::white));
            m_scene->addItem(new_textItem);
            new_textItem->setPos(pos_list.at(p - 1).toPoint());
            new_textItem->setFont(font);
            this->m_nameTextItems[p] = new_textItem;
            new_textItem->show();



         }
      for (int p=1; p<6; ++p) {
            new_rectItem = new GfxRectItem(pos_list.at(p - 1).toPoint().x(), pos_list.at(p - 1).toPoint().y() + 75, 175, 100, this->m_scene);

            //m_scene->addItem(new_rectItem);
            //new_rectItem->setBrush(QBrush(QColor(Qt::red)));
          //  new_rectItem->setZValue(1);
            this->m_turnRectItems[p] = new_rectItem;
          //  new_rectItem->show();
         }
      font.setPointSize(16);
      pos_list.clear();
      pos_list <<  QPointF(380.09, -147.285)
                <<  QPointF(354.751, 118.778)
                <<  QPointF(-104.525, 175.792)
                <<  QPointF(-611.312, 163.122)
                <<  QPointF(-601.81, -158.371);

      for (int p=1; p<6; ++p) {
            new_textItem = new TextItem(QString("1000").arg(p), this->m_scene);
            new_textItem->setDefaultTextColor(QColor(Qt::white));
            m_scene->addItem(new_textItem);
            new_textItem->setPos(pos_list.at(p - 1).toPoint());
            new_textItem->setFont(font);
            this->m_chipTextItems[p] = new_textItem;
            new_textItem->show();



         }

      this->m_timer_randomize = new QTimer(this);
      m_timer_randomize->connect(m_timer_randomize, SIGNAL(timeout()), this, SLOT(slot_randomize_all()));
      // m_timer_randomize->start((99 * (g_num * 15)) + (99 + 59));

      bool ok;
         QString text = QInputDialog::getText(this, tr("Input UserName"),
                                              tr("User name [mike/1/2/3/4]:"), QLineEdit::Normal,
                                              "", &ok);
         if (ok && !text.isEmpty()) {

               m_network->m_login = text;
               this->m_network->start(QThread::InheritPriority);
            } else {
               qDebug() << "NO LOGIN";
               QApplication::quit();
            }



      this->m_bet_controls = new BetControls(this);

      m_bet_controls->move(this->m_view->geometry().bottomLeft());
      QRect bcg = QRect(m_bet_controls->geometry());
      bcg.moveRight(m_view->geometry().right());
      m_bet_controls->setGeometry(bcg);
      this->m_bet_controls->show();
      this->connect(m_network, SIGNAL(signal_wait()), m_bet_controls, SLOT(slot_wait()));
      this->connect(m_network, SIGNAL(signal_turn(int)), m_bet_controls, SLOT(slot_turn(int)));
      this->connect(m_bet_controls, SIGNAL(signal_check()), m_network, SLOT(slot_send_check()));
      this->connect(m_bet_controls, SIGNAL(signal_fold()), m_network, SLOT(slot_send_fold()));
      this->connect(m_network, SIGNAL(signal_populate_seat(int,QString,int)), this, SLOT(slot_populate_seat(int,QString,int)));
      this->connect(m_bet_controls, SIGNAL(signal_bet(int)), m_network, SLOT(slot_send_bet(int)));
      this->connect(m_network, SIGNAL(signal_my_chips(int)), m_bet_controls, SLOT(slot_chips(int)));
      this->connect(m_network, SIGNAL(signal_current_turn(int)), this, SLOT(slot_update_current_turn(int)));
      this->createActions();
      this->createTrayIcon();

      connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
              this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
      if (text != "mike") {
            this->hide();

         }
   }

MainWindow::~MainWindow()
   {

   }
void MainWindow::slot_receive_index_change(int entry_number, int index_number) {
      if (this->m_cards.keys().contains(entry_number)) {
            CardPixmap* card = this->m_cards.value(entry_number);

            QHashIterator<int, QList<CardPixmap*> > p(this->m_game_cards);
            p.toFront();
            while (p.hasNext()) {
                  p.next();
                  QList<CardPixmap*> elist;
                  elist << p.value();
                  if (elist.contains(card)) {
                        QListIterator<CardPixmap*> o(elist);
                        o.toFront();
                        bool found_invalid = false;
                        while ((o.hasNext()) && (found_invalid == false)) {
                              CardPixmap* c = o.next();
                              if (c != card) {
                                    if (c->card_index() == index_number) {
                                          emit this->signal_send_invalid_index(entry_number);
                                          found_invalid = true;
                                       }
                                 }
                           }
                        p.toBack();
                     }


               }

         }
   }

void MainWindow::slot_randomize_all() {

      QHashIterator<int, CardPixmap*> o(this->m_cards);
      o.toFront();
      while (o.hasNext()) {
            o.next();
            int i = o.key();
            CardPixmap* c = o.value();
            QTimer::singleShot(((qBound(10, QTime::currentTime().second(), 59) * i) + (qBound(10, QTime::currentTime().minute(), 59) + qBound(5, QTime::currentTime().hour(), 23))), c, SLOT(slot_randomize()));
            //  c->slot_randomize();
         }

   }
void MainWindow::slot_write_cardpos_to_xml(int entry_number, qreal posX, qreal posY) {
      QFile output(QApplication::applicationDirPath().append("/cardPos.xml"));
      output.open(QIODevice::WriteOnly);
      QTextStream stream(&output);
      stream << "<cards>" << endl;
     QHashIterator<int, CardPixmap*> o(this->m_cards);
     o.toFront();
      while (o.hasNext()) {
            o.next();
            CardPixmap* pm = o.value();

            stream << QString("<card entry=\"%1\" posX=\"%2\" posY=\"%3\"></card>").arg(pm->entry_number()).arg(pm->scenePos().x()).arg(pm->scenePos().y()) << endl;

         }
      stream << "</cards>";
   }
 void MainWindow::slot_populate_seat(int seat_num, QString nickname, int chip_count) {
       if (seat_num < 6) {
             this->m_chipTextItems.value(seat_num)->setPlainText(QString("%1").arg(chip_count));
             this->m_nameTextItems.value(seat_num)->setPlainText(nickname);

          }
    }
 void MainWindow::slot_update_current_turn(int current_turn) {
       QHashIterator<int, GfxRectItem*> o(m_turnRectItems);
       o.toFront();
       while (o.hasNext()) {
             o.next();
             if (o.key() == current_turn) {
                   o.value()->m_item->setVisible(true);
                }   else {
                   o.value()->m_item->setVisible(false);

                }
          }
//       if (this->m_turnRectItems.keys().contains(current_turn)) {
//             this->m_turnRectItems.value(current_turn)->m_item->setVisible(true);
//          }
    }

void MainWindow::closeEvent(QCloseEvent *event) {
      if (this->m_network->isRunning()) {
            this->m_network->slot_send_fold();
            this->m_network->slot_send_quit();

            this->m_network->_socketConnected = false;
            this->m_network->exit(0);
         }
   }
void MainWindow::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    QIcon icon;
    QPixmap pm = makePixmap(51);
    icon.addPixmap(pm);
    trayIcon->setIcon(icon);
    trayIcon->show();
}
//void MainWindow::closeEvent(QCloseEvent *event)
//{
//    if (trayIcon->isVisible()) {
////        QMessageBox::information(this, tr("Systray"),
////                                 tr("The program will keep running in the "
////                                    "system tray. To terminate the program, "
////                                    "choose <b>Quit</b> in the context menu "
////                                    "of the system tray entry."));
//        hide();
//        event->ignore();
//    }
//}
void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
//        iconComboBox->setCurrentIndex((iconComboBox->currentIndex() + 1)
//                                      % iconComboBox->count());
        break;
    case QSystemTrayIcon::MiddleClick:
        //showMessage();
        break;
    default:
        ;
    }
}
