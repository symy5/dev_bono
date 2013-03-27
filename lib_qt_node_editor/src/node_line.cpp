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

	/* ��ԉ��Ɏ����Ă��� */
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

			/* �X�^�[�g�|�[�g�� OUTER �̏ꍇ�́AINNER �̂ݐڑ� */
			if (pConnectDstPort->type() != Type_NodePortIn) {
				/* NG */
				continue;
			}

			if (pConnectDstPort->m_pConnectedOutPort) {
				/* ���ɐڑ��ς݂̏ꍇ */
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
/* [NOTE] �}�E�X���̈�ɓ���ƌĂ΂�� */
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
			���݂̂Ƃ���AupdatePosition()�̑��p�����[�^�̓V�[�����W�n�̒l���p�����[�^�Ƃ��邽�߁A
			m_pNodeDstPort �̈ʒu���V�[�����W�n�ɕϊ����Ă���B
			���[�J�����W(mapFromItem)���V�[�����W(mapToScene)
		*/
		updatePosition(this->mapToScene(mapFromItem(m_pNodeDstPort, 0, 0)));
	}

	painter->setRenderHint(QPainter::Antialiasing);
	QPainterPath path(m_cpOne);
	path.cubicTo(m_cpTwo, m_cpThree, m_cpFour);
	painter->strokePath(path, m_myPen);

	this->setPath(path); /* [NOTE] ��������Ȃ��ƁAboundingRect()���Ă΂ꂽ�Ƃ��ɐ������l���Ԃ��ꂸ�A�`�悪�K�X���܂������Ȃ� */
	this->prepareGeometryChange();/* [NOTE] �`�󂪕ύX���ꂽ���Ƃ�ʒm���� */

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
		�n�_ �| �I�_�֌��ԃx�W�G�Ȑ��̃R���g���[���|�C���g��ݒ肷��
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