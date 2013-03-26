#include "node_item.h"
#include "def_data.h"
#include "node_line.h"
#include "node_port_in.h"
#include "node_port_out.h"


#include <QtGui>

#define ITEM_HEIHGT_UNIT	20
#define PORT_STR_POS_X		0
#define PORT_STR_POS_Y		20

NodeItem::NodeItem(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent, QGraphicsScene *scene)
		: QGraphicsPolygonItem(parent, scene)
{
	this->setBrush(QColor(DEF_COLOR_NODE_ITEM_BACKGROUND)); // background color

	myDiagramType = diagramType;
	myContextMenu = contextMenu;

	/* 形状の設定 */
	QPainterPath path;
	int nItemH = ITEM_HEIHGT_UNIT * 2;
	switch (myDiagramType) {
	case StartEnd:
		path.moveTo(150, nItemH); // 最初の位置の指定
		// void QPainterPath::arcTo ( qreal x, qreal y, qreal width, qreal height, qreal startAngle, qreal sweepLength )
		path.arcTo(100, 0, 50, 50, 0, 90);
		path.arcTo(0,   0, 50, 50, 90, 90);
		path.arcTo(0,   nItemH, 50, 50, 180, 90);
		path.arcTo(100, nItemH, 50, 50, 270, 90);
		path.lineTo(150, nItemH); // 残りとして最初の位置まで線を描画
		m_myPolygon = path.toFillPolygon();

		/* background */
		{
			QPainterPath path2;
			int nOffset = 3;
			path2.moveTo(150 - nOffset, nItemH - nOffset);
			path2.arcTo(100  - nOffset, 0      + nOffset, 50, 50, 0, 90);
			path2.arcTo(0    + nOffset, 0      + nOffset, 50, 50, 90, 90);
			path2.arcTo(0    + nOffset, nItemH - nOffset, 50, 50, 180, 90);
			path2.arcTo(100  - nOffset, nItemH - nOffset, 50, 50, 270, 90);
			path2.lineTo(150 - nOffset, nItemH - nOffset);
			m_myPolygonInner = path2.toFillPolygon();
		}

		break;
	case Conditional:
		m_myPolygon << QPointF(-100, 0) << QPointF(0, 100)
			<< QPointF(100, 0) << QPointF(0, -100)
				<< QPointF(-100, 0);
		break;
	case Step:
#if 1
#define D_NUM 50
		m_myPolygon
			<< QPointF(-D_NUM, -D_NUM)
			<< QPointF( D_NUM, -D_NUM)
			<< QPointF( D_NUM,  D_NUM)
			<< QPointF(-D_NUM,  D_NUM)
			<< QPointF(-D_NUM, -D_NUM);
#else
		m_myPolygon << QPointF(-100, -100) << QPointF(100, -100)
			<< QPointF(100, 100) << QPointF(-100, 100)
				<< QPointF(-100, -100);
#endif
		break;
	default:
		m_myPolygon << QPointF(-120, -80) << QPointF(-70, 80)
			<< QPointF(120, 80) << QPointF(70, -80)
				<< QPointF(-120, -80);
		break;
	}
	setPolygon(m_myPolygon);
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);

	_nFontWidth = 10;
	_nFontHeight = 20;

	this->setZValue(SPEC_ZVALUE_NODE_ITEM);

	/* 結果出力ポート配置 */
	_addOutNodePort();
}


void NodeItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	if (myContextMenu) {
		scene()->clearSelection();
		setSelected(true);
		myContextMenu->exec(event->screenPos());
	}
}


void NodeItem::_setFont(const QFont& font)
{
	QFontMetrics fm(font);
	_nFontWidth = fm.width('A');
	_nFontHeight = fm.height();
}


int NodeItem::_getFontStringWidth(QString* pStr)
{
	int nWidth = pStr->length() * _nFontWidth;
	return nWidth;
}


int NodeItem::_getFontStringHeight(QString* pStr)
{
	return _nFontHeight;
}


void NodeItem::_addOutNodePort()
{
	int nSize = 0;
	QRectF rectThis = this->boundingRect();
	_apOutPort = new NodePortOut(this);
	QRectF rectPort = _apOutPort->boundingRect();

	int nStrH = _getFontStringHeight(0);
	int nY;
	nY = nStrH * nSize + (rectPort.height() / 2); // ポート配置位置を中心に持ってくる
	_apOutPort->setPos(rectThis.x() + rectThis.width(), PORT_STR_POS_Y + rectThis.y() + nY);
}


void NodeItem::addNodePort(const QString& portName)
{
	int nSize = _listNodePort.count();
	for (int i = 0; i < nSize; i++) {
		QString& str = _listNodePort[i]->getPortName();
		if (portName == str) {
			/* already stored. */
			return;
		}
	}

	QRectF rectThis = this->boundingRect();
	NodePortIn* apPort = new NodePortIn(this);
	apPort->setPortName(portName);
	QRectF rectPort = apPort->boundingRect();

	int nStrH = _getFontStringHeight(0);
	int nY;
	nY = nStrH * nSize + (rectPort.height() / 2); // ポート配置位置を中心に持ってくる
	apPort->setPos(rectThis.x(), PORT_STR_POS_Y + rectThis.y() + nY);

	_listNodePort.push_back(apPort);
}


/* override */
void NodeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setRenderHint(QPainter::Antialiasing); // アンチエイリアシングを有効！

	/* paint the background. */
	QGraphicsPolygonItem::paint(painter, option, widget);

	/* paint the inner. */
	{
		QBrush brushOld = painter->brush();

		QBrush brush(QColor(DEF_COLOR_NODE_ITEM_INNER));
		painter->setBrush(brush); 
		painter->drawPolygon(m_myPolygonInner);

		painter->setBrush(brushOld); 
	}

	/* TBD */
	if (_nFontWidth == 0 && _nFontHeight == 0) {
		_setFont(painter->font());
	}

	QRectF rect = this->boundingRect();
	QFont font = painter->font();
	int nStrH = _getFontStringHeight(0);

	int nHeight = 0; /* offset */
	int nSize = _listNodePort.count();

	rect.translate(10, PORT_STR_POS_Y);

	for (int i = 0; i < nSize; i++) {
		QString& strBuf = _listNodePort[i]->getPortName();

		painter->drawText(rect, Qt::AlignLeft, strBuf);
		rect.translate(0, nStrH);
	}

}
