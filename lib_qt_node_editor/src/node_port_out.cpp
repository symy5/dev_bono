#include "node_port_out.h"
#include "node_line.h"
#include "node_line_manager.h"


NodePortOut::NodePortOut(QGraphicsItem* parent, QGraphicsScene* scene)
		: QGraphicsEllipseItem(QRectF(-5, -5, 10, 10), parent, scene)
{
	m_pNodeLineManager = new NodeLineManager(this);

	// set color
	_colorOuter = Qt::white;
	_colorOuterConnected = Qt::green;
	_colorSelected = Qt::magenta;

	// set press state
	m_pressed = false;
}


NodePortOut::~NodePortOut()
{
	delete m_pNodeLineManager;
	m_pNodeLineManager = NULL;
}


/* override */
QRectF NodePortOut::boundingRect() const
{
	return QGraphicsEllipseItem::boundingRect();
}


/* override */
void NodePortOut::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (! m_pressed) {
		return;
	}

	_pTmpNodeLine->updatePosition(mouseEvent->scenePos());
}


/* override */
void NodePortOut::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	m_pressed = true;
	/* 
		OUTER ‚Ìê‡‚ÍAü•`‰æˆ—
	*/
	_pTmpNodeLine = new NodeLine(this);
	_pTmpNodeLine->updatePosition(mouseEvent->scenePos());
}


/* override */
void NodePortOut::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (! m_pressed) {
		return;
	}

	_pTmpNodeLine->updatePosition(mouseEvent->scenePos());
	if (_pTmpNodeLine->checkConnect() == false) {
		delete _pTmpNodeLine;
	} else {
		if (m_pNodeLineManager->addNodeLine(_pTmpNodeLine) == false) {
			/* ’Ç‰Á‚Å‚«‚È‚¢ê‡‚ÍAíœ */
			delete _pTmpNodeLine;
		}
	}
	_pTmpNodeLine = NULL;

	m_pressed = false;
}


/* override */
void NodePortOut::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (m_pressed) {
		this->setBrush(_colorSelected);
	} else {
		if (m_pNodeLineManager->isConnect()) {
			/* connect */
			this->setBrush(_colorOuterConnected);
		} else {
			this->setBrush(_colorOuter);
		}
	}

	QGraphicsEllipseItem::paint(painter, option, widget);
}


/* override */
QPainterPath NodePortOut::shape() const
{
	return QGraphicsEllipseItem::shape();
}
