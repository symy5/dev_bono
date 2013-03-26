#ifndef __NODE_PORT_IN_H__
#define __NODE_PORT_IN_H__

#include "use_spec.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>


class NodeLine;
class NodePortOut;

class NodePortIn :public QGraphicsEllipseItem
{

public:
	NodePortIn(QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);
	~NodePortIn();
	void setPortName(const QString& name);
	QString& getPortName();
	QRectF boundingRect() const;
	void setPortRole(int nRole);
	void setConnectSource(NodePortOut* pConnectedSrcPort); /* ê⁄ë±Ç≥ÇÍÇΩå≥ÉmÅ[ÉhÇÃê›íË */
	int type() const
	{ return Type_NodePortIn; }

protected: /* override */
	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	QPainterPath shape() const;

private:
	bool _checkConnectPort();

public:
	bool _isConnect;
	NodePortOut* m_pConnectedOutPort;

private:
	NodeLine* _pTmpNodeLine;
	bool m_pressed;
	QColor _colorSelected;
	QColor _colorInnerConnected;
	QColor _colorInner;
	QString _portName;
};

#endif /* __NODE_PORT_IN_H__ */
