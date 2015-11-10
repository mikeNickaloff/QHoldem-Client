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

#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QGraphicsTextItem>
class GraphicsScene;
class TextItem : public QGraphicsTextItem
   {
      Q_OBJECT
   public:
       TextItem(QString i_text = QString(""), QGraphicsScene* i_scene = 0);
      
   signals:
      
   public slots:
   protected:
       void mousePressEvent(QGraphicsSceneMouseEvent *event);
       void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
       void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
   private:
       QGraphicsScene* _scene;
       QPointF _design_mouse_press_pos;
       QPointF _design_item_pos;
       QPointF _design_mouse_delta(QPointF eventCurrentPos) {

             QPointF rv = QPointF(eventCurrentPos - _design_mouse_press_pos);
             return rv;
          }
   };

#endif // TEXTITEM_H
