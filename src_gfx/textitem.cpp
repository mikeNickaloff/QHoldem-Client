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

TextItem::TextItem(QString i_text, QGraphicsScene *i_scene) :
   QGraphicsTextItem(i_text), _scene(i_scene)
   {
   }
void TextItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
      if (event->button() == Qt::LeftButton) {
            this->_design_mouse_press_pos = event->scenePos();
           // qDebug() << "PRESS @" << this->_design_mouse_press_pos;
            this->_design_item_pos = this->scenePos();
         }
   }

void TextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
      this->setPos(QPointF(_design_item_pos + this->_design_mouse_delta(event->scenePos())));
   }

void TextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
      if (event->button() == Qt::LeftButton) {
            //this->_design_mouse_press_pos = event->scenePos();
            //qDebug() << "RELEASE @" << this->_design_mouse_delta(event->scenePos());
            qDebug() << " << " << event->scenePos();
            //emit this->signal_write_cardpos_to_xml(this->entry_number(), this->scenePos().x(), this->scenePos().y());
         }
   }
