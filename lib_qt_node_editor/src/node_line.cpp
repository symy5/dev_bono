#include "node_line.h"
#include "def_data.h"
#include "node_port_in.h"
#include "node_port_out.h"


#include <QPainter>
#include <QPaintEvent>
#include <QPainterPathStroker>
#include <QPainterPath>
#include <QBrush>
#include <QFileDialog>
#include <QPen>
#include <QMessageBox>
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <QtDebug>
#include <math.h>

static const int pointSize = 5;

NodeLine::NodeLine(NodePortOut* pNodePortSrc) : QGraphicsPathItem(pNodePortSrc)
{
	m_pNodeSrcPort = pNodePortSrc;
	m_pNodeDstPort = NULL;

	m_myPen = QPen(QColor(DEF_COLOR_NODE_LINE), 2);
	m_cpOne = QPointF(0, 0);
	m_cpTwo = QPointF(0, 0);
	m_cpThree = QPointF(0, 0);
	m_cpFour = QPointF(0, 0);

	/* 一番下に持ってくる */
	this->setZValue(SPEC_ZVALUE_NODE_LINE);
}


NodeLine::~NodeLine()
{
}

/* override */
QRectF NodeLine::boundingRect() const
{
	QRectF newRect = QGraphicsPathItem::boundingRect();
	return newRect;
}


bool NodeLine::checkConnect()
{
	QList<QGraphicsItem*> collidingWithList = this->collidingItems(Qt::IntersectsItemShape);

	int nCnt = collidingWithList.size();
	if ( nCnt <= 0) {
		return false;
	}

	for (int i = 0; i < nCnt; i++) {
		if (Type_NodePortIn == collidingWithList[i]->type()) {

			NodePortIn* pConnectDstPort = (NodePortIn*)(collidingWithList[i]);

			/* スタートポートが OUTER の場合は、INNER のみ接続 */
			if (pConnectDstPort->type() != Type_NodePortIn) {
				/* NG */
				continue;
			}

			if (pConnectDstPort->m_pConnectedOutPort) {
				/* 既に接続済みの場合 */
				/* NG */
				continue;
			}

			/* OK */
			m_pNodeDstPort = pConnectDstPort;
			m_pNodeDstPort->setConnectSource(m_pNodeSrcPort);

			return true;
		}
	}

	return false;
}


/* override */
bool NodeLine::contains(const QPointF& point) const
{
	bool retBool = QGraphicsPathItem::contains(point);
	return retBool;
}


/* override */
bool NodeLine::isObscuredBy(const QGraphicsItem* item) const
{
	bool retBool = QGraphicsPathItem::isObscuredBy(item);
	return retBool;
}


/* override */
QPainterPath NodeLine::opaqueArea() const
{
	QPainterPath retPath = QGraphicsPathItem::opaqueArea();
	return retPath;
}


/* override */
/* [NOTE] マウスが領域に入ると呼ばれる */
QPainterPath NodeLine::shape() const
{
	QPainterPath retPath = QGraphicsPathItem::shape();
	return retPath;
}


/* override */
void NodeLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->save();

	if (m_pNodeDstPort) {
		//
		/* [TBD]
			現在のところ、updatePosition()の第一パラメータはシーン座標系の値をパラメータとするため、
			m_pNodeDstPort の位置をシーン座標系に変換している。
			ローカル座標(mapFromItem)→シーン座標(mapToScene)
		*/
		updatePosition(this->mapToScene(mapFromItem(m_pNodeDstPort, 0, 0)));
	}

	painter->setRenderHint(QPainter::Antialiasing);
	QPainterPath path(m_cpOne);
	path.cubicTo(m_cpTwo, m_cpThree, m_cpFour);
	painter->strokePath(path, m_myPen);

	this->setPath(path); /* [NOTE] これを入れないと、boundingRect()が呼ばれたときに正しい値が返されず、描画が適宜うまくいかない */
	this->prepareGeometryChange();/* [NOTE] 形状が変更されたことを通知する */

	painter->restore();
}


void NodeLine::updatePosition(const QPointF& point)
{
	m_cpOne = this->mapFromItem(m_pNodeSrcPort, 0, 0);
	m_cpFour = this->mapFromScene(point);

	float fOffsetX, fOffsetY;
	if (m_cpOne.x() > m_cpFour.x()) {
		fOffsetX = (m_cpOne.x() - m_cpFour.x()) / 2;
	} else {
		fOffsetX = (m_cpFour.x() - m_cpOne.x()) / 2;
	}

	if (m_cpOne.y() > m_cpFour.y()) {
		fOffsetY = (m_cpOne.y() - m_cpFour.y()) / 2;
	} else {
		fOffsetY = (m_cpFour.y() - m_cpOne.y()) / 2;
	}

	/*
		始点 － 終点へ結ぶベジエ曲線のコントロールポイントを設定する
	*/
#if 0
	if (fOffsetX >= fOffsetY) {
		m_cpTwo.setX(m_cpOne.x());
		m_cpThree.setX(m_cpFour.x());
		m_cpTwo.setY(m_cpFour.y());
		m_cpThree.setY(m_cpOne.y());
	} else {
		/* fOffsetX < fOffsetY */
		m_cpTwo.setX(m_cpFour.x());
		m_cpThree.setX(m_cpOne.x());
		m_cpTwo.setY(m_cpOne.y());
		m_cpThree.setY(m_cpFour.y());
	}
#else
	m_cpTwo.setX(m_cpFour.x());
	m_cpThree.setX(m_cpOne.x());
	m_cpTwo.setY(m_cpOne.y());
	m_cpThree.setY(m_cpFour.y());
#endif

#if 0
	qDebug() << "1.x=" << m_cpOne.x()   << "1.y=" << m_cpOne.y();
	qDebug() << "2.x=" << m_cpTwo.x()   << "2.y=" << m_cpTwo.y();
	qDebug() << "3.x=" << m_cpThree.x() << "3.y=" << m_cpThree.y();
	qDebug() << "4.x=" << m_cpFour.x()  << "4.y=" << m_cpFour.y();
#endif
}


void NodeLine::setNodeDstPort(NodePortIn* pNodeDstPort)
{
	m_pNodeDstPort = pNodeDstPort;
}