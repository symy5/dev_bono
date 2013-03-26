#ifndef __NODE_PORT_ITEM_H__
#define __NODE_PORT_ITEM_H__

#include "use_spec.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>


class NodeLine;
class NodeLineManager;

class NodePortOut :public QGraphicsEllipseItem
{
public:
	NodePortOut(QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);
	~NodePortOut();
	QRectF boundingRect() const;
	int type() const
	{ return Type_NodePortOut; }

protected: /* override */
	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	QPainterPath shape() const;

private:
	bool _checkConnectPort();

public:
	NodeLineManager* m_pNodeLineManager;

private:
	NodeLine* _pTmpNodeLine;
	bool m_pressed;
	QColor _colorSelected;
	QColor _colorOuterConnected;
	QColor _colorOuter;

};

#endif /* __NODE_PORT_ITEM_H__ */
