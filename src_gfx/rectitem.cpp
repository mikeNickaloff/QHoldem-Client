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

#include "gfx.h"
#include <QtGui>
GfxRectItem::GfxRectItem(qreal x, qreal y, qreal w, qreal h, QGraphicsScene* _scene) :
   QObject(), _boundingRect(x, y, w, h), m_scene(_scene)
   {
      this->m_item = m_scene->addRect(_boundingRect, QPen(QColor(Qt::green)), QBrush(QColor(Qt::yellow)));

   }
void GfxRectItem::mousePressEvent(QMouseEvent *event) {
      if (event->button() == Qt::LeftButton) {
            this->_design_mouse_press_pos = event->pos();
           // qDebug() << "PRESS @" << this->_design_mouse_press_pos;
            this->_design_item_pos = this->m_item->scenePos();
         }
   }

void GfxRectItem::mouseMoveEvent(QMouseEvent *event) {
      this->m_item->setPos(QPointF(_design_item_pos + this->_design_mouse_delta(event->pos())));
   }

void GfxRectItem::mouseReleaseEvent(QMouseEvent *event) {
      if (event->button() == Qt::LeftButton) {
            //this->_design_mouse_press_pos = event->scenePos();
            //qDebug() << "RELEASE @" << this->_design_mouse_delta(event->scenePos());
            qDebug() << " << " << event->pos();
            //emit this->signal_write_cardpos_to_xml(this->entry_number(), this->scenePos().x(), this->scenePos().y());
         }
   }
