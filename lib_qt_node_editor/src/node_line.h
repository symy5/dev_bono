#ifndef __NODE_LINE_H__
#define __NODE_LINE_H__


/*
  Bezier ã»ê¸ÇégópÇ∑ÇÈ
 */

#include "use_spec.h"
#include <QPointF>
#include <QGraphicsPathItem>
#include <QMouseEvent>
#include <QPen>


class NodePortIn;
class NodePortOut;

class NodeLine : public QGraphicsPathItem
{
public:
	NodeLine(NodePortOut* pNodePortSrc);
	~NodeLine();
	void updatePosition(const QPointF& point);
	bool checkConnect();
	void setNodeDstPort(NodePortIn* pNodeDstPort);

protected: /* override */
	QRectF boundingRect() const;
	bool contains(const QPointF& point) const;
	bool isObscuredBy(const QGraphicsItem* item) const;
	QPainterPath opaqueArea() const;
	QPainterPath shape() const;
	int type () const
	{ return Type_NodeLine; }
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	
public:
	NodePortOut* m_pNodeSrcPort;
	NodePortIn* m_pNodeDstPort;

private:
	QPointF m_cpOne, m_cpTwo, m_cpThree, m_cpFour;
	QPen m_myPen;
};

#endif /* __NODE_LINE_H__ */
