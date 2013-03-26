#ifndef __NODE_ITEM_H__
#define __NODE_ITEM_H__

#include "use_spec.h"
#include <QGraphicsPixmapItem>
#include <QList>

class QPixmap;
class QGraphicsItem;
class QGraphicsScene;
class QTextEdit;
class QGraphicsSceneMouseEvent;
class QMenu;
class QGraphicsSceneContextMenuEvent;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QPolygonF;


class NodeLine;
class NodePortIn;
class NodePortOut;

class NodeItem : public QGraphicsPolygonItem
{
public:

	enum DiagramType {
		Step, Conditional, StartEnd, Io
	};

	NodeItem(DiagramType diagramType, QMenu *contextMenu = 0, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

	DiagramType diagramType() const
	{ return myDiagramType; }
	QPolygonF polygon() const
	{ return m_myPolygon; }

	int type() const
	{ return Type_NodeItem;}

	void addNodePort(const QString& portName);


protected: /* override */
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
	void _addOutNodePort();
	int _getFontStringWidth(QString* pStr);
	int _getFontStringHeight(QString* pStr);
	void _setFont(const QFont& font);


private:
	DiagramType myDiagramType;
	QPolygonF m_myPolygon;
	QPolygonF m_myPolygonInner;
	QMenu *myContextMenu;
	int _nFontWidth;
	int _nFontHeight;
	QList<NodePortIn*> _listNodePort;
	NodePortOut* _apOutPort;
};


#endif /* __NODE_ITEM_H__ */
