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

#include "network.h"
#include <QtNetwork>
#include <QtDebug>
#include <QByteArray>
#include <QtGui>
NetworkThread::NetworkThread(QObject *parent) :
   QThread(parent)
   {
      this->_socketConnected = false;
   }
NetworkThread::~NetworkThread() {
      this->_socketConnected = false;
      terminate();
      exit(0);
   }

void NetworkThread::run() {
      // QTcpSocket socket;
      //socket.connectToHost(QHostAddress::LocalHost, 2222, QTcpSocket::ReadWrite);
      // socket.waitForConnected(999999);
      QMutex mutex;
      mutex.lock();
      QWaitCondition waitCondition;

      this->_socketConnected = true;
      //qDebug() << "Connected to host!!";
      // while (_socketConnected) {
      // socket.waitForBytesWritten(999);
      //      if (!socket.waitForReadyRead(99999))
      //         qDebug() << "Cannot Read";
      //      QDataStream in(&socket);
      // in.setVersion(QDataStream::Qt_4_0);

      //      QByteArray data = socket.readAll();

      //data = data.left(data.size() - 1);
      // if (data.size() > 0) {
      //            qDebug() << "RECEIVED ::" << data;
      //            socket.write(QByteArray().append("mike"));
      //   }

      //   }

      //  QMutex mutex;
      // mutex.lock();
      //! [4] //! [5]
      QString serverName = "127.0.0.1";
      quint16 serverPort = 2222;
      //  mutex.unlock();
      //! [5]

      // socket.abort();
      socket.connectToHost(serverName, serverPort);
      //! [6]

      const int Timeout = 9999 * 1111;
      connect(this, SIGNAL(signal_send_msg(QString)), &socket, SLOT(sendMessage(QString)));
      //            QTcpSocket socket;
      //            socket.connectToHost(serverName, serverPort);
      //! [6] //! [8]


      //! [10] //! [11]


      while (_socketConnected) {

            //            socket.waitForReadyRead(9999);
            if (!socket.waitForConnected(Timeout)) {
                  //  emit error(socket.error(), socket.errorString());
                  qDebug() << socket.errorString();
                  waitCondition.wait(&mutex, 650);
                  this->_socketConnected = false;
                  // return;
               }
            //! [8] //! [9]

            while (socket.bytesAvailable() < (int)sizeof(quint16)) {
                  if (!socket.waitForReadyRead(Timeout)) {
                        //    qDebug() << "error(" << socket.error() << socket.errorString();
                        //return;
                        waitCondition.wait(&mutex, 650);
                     }
                  //! [9] //! [10]
               }



            QByteArray data = socket.read(socket.bytesAvailable());
            // data = data.left(data.size() - 1);
            if (data.size() > 0) {
                  //qDebug() << "RECEIVED ::" << data;
                  this->slot_parse_data(data, socket);
               }


            //            bool ok = socket.waitForReadyRead(9999);
            //            quint16 blockSize;
            //            QDataStream in(&socket);
            //            in.setVersion(QDataStream::Qt_4_0);
            //           // in >> blockSize;
            //            //! [11] //! [12]

            ////            while (socket.bytesAvailable() < blockSize) {
            ////                  if (!socket.waitForReadyRead(Timeout)) {
            ////                        // emit error(socket.error(), socket.errorString());
            ////                        qDebug() << socket.errorString();
            ////                        return;
            ////                     }
            //                  //! [12] //! [13]
            //             //  }
            //            //! [13] //! [14]

            // mutex.lock();
            //            QByteArray fortune;
            //            in >> fortune;
            //            //emit newFortune(fortune);
            //            qDebug() << fortune << "received from socket" << socket.socketDescriptor();
            //            this->slot_parse_data(fortune, socket);
            // //! [7] //! [14] //! [15]
            //  TCPSocket isocket(socket);
            // socket.sendMessage("mike");
            // QByteArray block;
            //            QString text;
            //            QTextStream out(&text, QIODevice::WriteOnly);
            //           // out.setVersion(QDataStream::Qt_4_0);
            //            out << (quint16)4;
            //            out << "mike";
            //            out << endl;
            //           // out.device()->seek(0);
            //           // out << (quint16)(block.size() - sizeof(quint16));
            //            socket.write(text.toLocal8Bit());
            //socket.sendMessage("mike");
            //socket.waitForBytesWritten(9999);
            //this->_socketConnected = false;
            // socket.waitForReadyRead(9999);
            //            if (block.size() > 1) {
            //                  socket.setTextModeEnabled(true);
            //                  socket.write(block);
            //                  socket.flush();
            //                  this->_socketConnected = false;
            //                  qDebug() << "Wrote Block" << block.toPercentEncoding();
            //               }
            //            socket.waitForReadyRead(999);
            //            QByteArray block;
            //            QDataStream out(&block, QIODevice::WriteOnly);
            //            out.setVersion(QDataStream::Qt_4_0);
            //            out << (quint16)0;
            //            out << QByteArray().append("mike");
            //            out.device()->seek(0);
            //            out << (quint16)(block.size() - sizeof(quint16));
            //          //  socket.setOpenMode(QTcpSocket::WriteOnly);
            //            socket.write(block);
            //  socket.close();


            // cond.wait(&mutex);
            // serverName = "127.0.0.1";
            // serverPort = 2222;
            //mutex.unlock();
         }
      // socket.disconnectFromHost();
   }
void NetworkThread::slot_parse_data(QByteArray i_data, TCPSocket &i_socket) {
      QList<QByteArray> clist; clist << i_data.split('!');
      foreach (QByteArray s_data, clist) {
            QList<QByteArray> slist; slist << s_data.split(':');
            //qDebug() << "parsed data to" << slist;
            if (slist.first() == QByteArray().append("REQ")) {
                  if (slist.last() == QByteArray().append("Login")) {
                        this->slot_send_data(QString("!LOGIN:%1").arg(m_login), i_socket);
                     }

               }
            if (slist.first() == QByteArray().append("HELLO")) {

                  qDebug() << "SUCCESSFUL LOGIN AS" << slist.last();

               }
            if (slist.first() == QByteArray().append("INDEX CHANGE")) {
                  // qDebug() << "idx change " << slist.at(1) << slist.at(2);
                  //int i1 = slist.at(1).toInt();
                  //int i2 = slist.at(2).toInt();
                  //emit this->signal_index_change(i1, i2);
                  QListIterator<QByteArray> e(slist);
                  e.toFront();
                  QByteArray arr = e.next();
                  while (e.hasNext()) {
                        arr = e.next();
                        QList<QByteArray> elist; elist << arr.split(',');
                        int entry = elist.at(0).toInt();
                        int idx = elist.at(1).toInt();
                        emit this->signal_index_change(entry, idx);
                     }
               }
            if (slist.first() == QByteArray().append("WAIT")) {
                  emit this->signal_wait();
               }
            if (slist.first() == QByteArray().append("CURRENT_TURN")) {
                  int val = slist.at(1).toInt();
                  emit this->signal_current_turn(val);
                 // qDebug() << "CURRENT TURN IS" << val;
               }
            if (slist.first() == QByteArray().append("TURN")) {
                  int amt = slist.at(1).toInt();
                  emit this->signal_turn(amt);
               }
            if (slist.first() == QByteArray().append("WIN")) {
                  int amt = slist.at(1).toInt();
                  emit this->signal_win(amt);
//                  QMessageBox mbox;
//                  mbox.setText("YOU WIN!!");
//                  mbox.exec();

               }
            if (slist.first() == QByteArray().append("SEAT")) {
                  int seat_num = slist.at(1).toInt();
                  QString nickname = QString::fromUtf8(slist.at(2));
                  int chip_count = slist.at(3).toInt();
                  emit this->signal_populate_seat(seat_num, nickname, chip_count);
                //   emit this->signal_my_chips(chip_count);
               }
            if (slist.first() == QByteArray().append("CHIPS")) {
                  int chip_count = slist.at(1).toInt();
                  emit this->signal_my_chips(chip_count);
               }
         }
   }


void NetworkThread::slot_send_data(QString i_data, TCPSocket &i_socket) {


      i_socket.sendMessage(i_data);


   }

void NetworkThread::slot_send_check() {
      emit this->signal_send_msg("!CHECK:");
   }

void NetworkThread::slot_send_fold() {
      emit this->signal_send_msg("!FOLD:");
   }
void NetworkThread::slot_send_quit() {
      emit this->signal_send_msg("!QUIT:");
   }

void NetworkThread::slot_send_bet(int amt) {
      emit this->signal_send_msg(QString("!BET:%1:").arg(amt));
   }

bool TCPSocket::sendMessage(const QString &message)
   {
      if (message.isEmpty())
         return false;
      QString text;
      QTextStream out(&text, QIODevice::WriteOnly);
      // out.setVersion(QDataStream::Qt_4_0);
      //out << (quint16)4;
      out << message;
      out << endl;
      // out.device()->seek(0);
      // out << (quint16)(block.size() - sizeof(quint16));
      bool ok = write(text.toUtf8()) == text.size();
      this->flush();
      this->waitForBytesWritten(299);
      qDebug() << "OUT" << text.toUtf8();
      return ok;


      //    QByteArray msg = message.toUtf8();
      //    QByteArray data = "MESSAGE " + QByteArray::number(msg.size()) + ' ' + msg;
      //    return write(data) == data.size();
   }
TCPSocket::TCPSocket(QObject *parent) :
   QTcpSocket(parent)
   {

   }
