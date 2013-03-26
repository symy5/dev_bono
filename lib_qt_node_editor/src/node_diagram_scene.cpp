#include "node_diagram_scene.h"
#include <QtGui>


NodeDiagramScene::NodeDiagramScene(QObject *parent)
		: QGraphicsScene(parent)
{
	_apSelectedItem = NULL;
}


/* アイテムを最前に持ってくる */
void NodeDiagramScene::_bringToFront()
{
	if (this->selectedItems().isEmpty())
		return;

	_apSelectedItem = this->selectedItems().first();
	QList<QGraphicsItem *> overlapItems = _apSelectedItem->collidingItems();

	qreal zValue = 0;
	foreach (QGraphicsItem *item, overlapItems) {
		if (item->zValue() >= zValue &&	item->type() == Type_NodeItem) {
			zValue = item->zValue() + 0.001; /* [SPEC] zValue は戻さない */
		}
	}
	_apSelectedItem->setZValue(zValue);
}


void NodeDiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	QGraphicsScene::mousePressEvent(mouseEvent);

	_bringToFront();
}


void NodeDiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	QGraphicsScene::mouseMoveEvent(mouseEvent);
}


void NodeDiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
