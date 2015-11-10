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

#ifndef RECTITEM_H
#define RECTITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QtGui>
class GraphicsScene;
class GfxRectItem : public QObject
   {
      Q_OBJECT
   public:
      GfxRectItem(qreal x, qreal y, qreal w, qreal h, QGraphicsScene* _scene = 0);
      QGraphicsRectItem* m_item;
       QGraphicsScene* m_scene;
       QRectF _boundingRect;
   signals:

   public slots:
   protected:
      QRectF boundingRect() {
            return _boundingRect;
         }
       void mousePressEvent(QMouseEvent *event);
       void mouseMoveEvent(QMouseEvent *event);
       void mouseReleaseEvent(QMouseEvent *event);
   private:

       QPointF _design_mouse_press_pos;
       QPointF _design_item_pos;
       QPointF _design_mouse_delta(QPointF eventCurrentPos) {

             QPointF rv = QPointF(eventCurrentPos - _design_mouse_press_pos);
             return rv;
          }

   };

#endif // RECTITEM_H
