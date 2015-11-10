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

#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H

#include <QThread>
#include <QtNetwork>
#include <QtGui>

class TCPSocket : public  QTcpSocket {
      Q_OBJECT
   public:
      TCPSocket(QObject* parent = 0);
   public slots:
      bool sendMessage(const QString &message);

   };
//class TCPSocket;
class NetworkThread : public QThread
   {
      Q_OBJECT
   public:
      explicit NetworkThread(QObject *parent = 0);
      ~NetworkThread();
      bool _socketConnected;
      QWaitCondition cond;
      QMutex mutex;
       bool sendMessage(const QString &message);
       TCPSocket socket;
       QString m_login;
   signals:
       void signal_index_change(int entry, int index);
       void signal_wait();
       void signal_turn(int current_bet);
       void signal_send_msg(const QString &message);
       void signal_win(int amt);
       void signal_populate_seat(int seat_num, QString nickname, int chip_count);
       void signal_my_chips(int chip_count);
       void signal_current_turn(int turn_number);
   public slots:
      void slot_parse_data(QByteArray i_data, TCPSocket &i_socket);
      void slot_send_data(QString i_data, TCPSocket &i_socket);
      void slot_send_check();
      void slot_send_fold();
      void slot_send_bet(int amt);
      void slot_send_quit();
   protected:
      void run();
   private:

      
   };


#endif // NETWORKTHREAD_H
