#include "node_port_in.h"
#include "node_port_out.h"
#include "node_line_manager.h"
#include "node_line.h"


NodePortIn::NodePortIn(QGraphicsItem* parent, QGraphicsScene* scene)
		: QGraphicsEllipseItem(QRectF(-5, -5, 10, 10), parent, scene)
{
	_pTmpNodeLine = NULL;
	m_pConnectedOutPort = NULL;
	// set color
	_colorInner = Qt::white;
	_colorInnerConnected = Qt::green;
	_colorSelected = Qt::magenta;

	// set press state
	m_pressed = false;

	this->setZValue(100);
}


NodePortIn::~NodePortIn()
{
}


void NodePortIn::setPortName(const QString& name)
{
	_portName = name;
}


QString& NodePortIn::getPortName()
{
	return _portName;
}


/* override */
QRectF NodePortIn::boundingRect() const
{
	return QGraphicsEllipseItem::boundingRect();
}


/* override */
void NodePortIn::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (! m_pressed) {
		return;
	}

	if (_pTmpNodeLine) {
		_pTmpNodeLine->updatePosition(mouseEvent->scenePos());
	}
}


/* override */
void NodePortIn::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	m_pressed = true;
	/* 
		INNER �̏ꍇ�́A��������
	*/
	if (m_pConnectedOutPort) {
		_pTmpNodeLine = m_pConnectedOutPort->m_pNodeLineManager->removeNodeLine(this);
		m_pConnectedOutPort = NULL;
		/* disconnect, will call delete or re-add after.*/
	}
}


/* override */
void NodePortIn::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (! m_pressed) {
		return;
	}

	m_pressed = false;
	bool isConnect;
	if (_pTmpNodeLine) {
		_pTmpNodeLine->updatePosition(mouseEvent->scenePos());
		isConnect = _pTmpNodeLine->checkConnect();

		if (isConnect == true && m_pConnectedOutPort) {
			/* �ēx�ڑ����ꂽ�ꍇ�́A�ꎞ NodeLine ���ēx�o�^���� */
			if (m_pConnectedOutPort->m_pNodeLineManager->addNodeLine(_pTmpNodeLine) == false) {
				/* �ǉ��ł��Ȃ��ꍇ�́A�폜 */
				delete _pTmpNodeLine;
			}
		} else {
			/* �ڑ�����Ă��Ȃ��ꍇ�́A�ꎞ NodeLine ���폜 */
			delete _pTmpNodeLine;
		}
		_pTmpNodeLine = NULL;
	}
}


/* override */
void NodePortIn::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (m_pressed) {
		this->setBrush(_colorSelected);
	} else {
		if (m_pConnectedOutPort) {
			/* connect */
			this->setBrush(_colorInnerConnected);
		} else {
			this->setBrush(_colorInner);
		}
	}

	QGraphicsEllipseItem::paint(painter, option, widget);
}


/* override */
QPainterPath NodePortIn::shape() const
{
	return QGraphicsEllipseItem::shape();
}


void NodePortIn::setConnectSource(NodePortOut* pConnectedSrcPort)
{
	m_pConnectedOutPort = pConnectedSrcPort;
}