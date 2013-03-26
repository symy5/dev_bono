#ifndef __NODE_DIAGRAM_SCENE_H__
#define __NODE_DIAGRAM_SCENE_H__

#include "use_spec.h"
#include <QGraphicsScene>
#include <QPen>


class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;


class NodeItem;

class NodeDiagramScene : public QGraphicsScene
{
	Q_OBJECT

public:
	NodeDiagramScene(QObject *parent = 0);
	int type() const
	{ return Type_NodeDiagramScene;}


signals:
	void itemInserted(NodeItem* item);
	void itemSelected(QGraphicsItem *item);

protected: /* override */
	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
	void _bringToFront();


private:
	QMenu *myItemMenu;
	bool leftButtonDown;
	QPointF startPoint;
	QGraphicsItem *_apSelectedItem; /* ZValue ‚ÅŽg—p */
};
//! [0]

#endif /* __NODE_DIAGRAM_SCENE_H__ */
