#include "node_graphics_view.h"
#include "def_data.h"
#include "node_item.h"
#include "node_port_in.h"
#include "node_diagram_scene.h"

#include <QtGui>
#include <QApplication>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QPushButton>
#include <QComboBox>



NodeGraphicsView::NodeGraphicsView(QWidget* parent) :
QGraphicsView(parent)
{
	m_pScene = NULL;

	setAcceptDrops(true);
	connect(this, SIGNAL(dropEvent()), this, SLOT(myDropEvent()));

	_isMouseTranslate = false;
}


NodeGraphicsView::~NodeGraphicsView()
{
}


int NodeGraphicsView::init()
{
#if 0
	 /* 以下、テストコード */
	/* Rect1 */
	QGraphicsRectItem *apRect1 = new QGraphicsRectItem(QRectF(-50, -25, 100, 50));
	apRect1->setBrush(Qt::cyan);
	
	apRect1->setPos(0, 0);
	apRect1->setFlags(QGraphicsItem::ItemIsMovable);
	//apRect1->setZValue(-1);

	NodePortIn* portLeft1 = new NodePortIn(apRect1);
	portLeft1->setPos(0, 0);

	{
		QGraphicsTextItem *text = new QGraphicsTextItem(apRect1);
		text->setPlainText("koko");

		QGraphicsEllipseItem *portN = new QGraphicsEllipseItem(QRectF(-5, -5, 10, 10), apRect1);
		portN->setPos(0, -25);
		QGraphicsEllipseItem *portS = new QGraphicsEllipseItem(QRectF(-5, -5, 10, 10), apRect1);
		portS->setPos(0, 25);
	}

	/* Rect2 */
	QGraphicsRectItem *apRect2 = new QGraphicsRectItem(QRectF(-50, -25, 100, 50));
	{
		apRect2->setBrush(Qt::green);
		apRect2->setPos(150, 50);
		apRect2->setFlags(QGraphicsItem::ItemIsMovable);

		NodePortIn* portLeft2 = new NodePortIn(apRect2);
		portLeft2->setPos(-50, 20);

		NodePortIn* portLeft3 = new NodePortIn(apRect2);
		portLeft3->setPos(-50, -20);
	}
	NodeItem* apNodeItem = new NodeItem(NodeItem::StartEnd);
	apNodeItem->setPos(-80, 0);
	apNodeItem->addNodePort(QString("Hello1"));
	apNodeItem->addNodePort(QString("Hello2"));


	/* シーンに追加 */
	m_pScene = new NodeDiagramScene(this);

	m_pScene->addItem(apRect1);
	m_pScene->addItem(apRect2);

	m_pScene->addItem(apNodeItem);

	this->setScene(m_pScene);

	/* 背景色設定 */
	this->setStyleSheet(DEF_COLOR_STYLE_GRAPHICS_VIEW);
#else
	m_pScene = new NodeDiagramScene(this);
	this->setScene(m_pScene);
#endif

	return 0;
}


void NodeGraphicsView::fin()
{
	if (m_pScene) {
		delete m_pScene;
		m_pScene = NULL;
	}
}


void NodeGraphicsView::_putNodeItem(const QString& fName, const QPoint& pos)
{
	static const QStringList s_listName = QStringList() << "NodeItem1" << "NodeItem2" << "NodeItem3";

	NodeItem* apNodeItem = new NodeItem(NodeItem::StartEnd);
	int nScnX, nScnY;
	QPointF posf = this->mapToScene(pos);

	apNodeItem->setPos(posf.x(), posf.y());
	m_pScene->addItem(apNodeItem);

	apNodeItem->addNodePort(QString("Hello1"));
	if (fName == s_listName[0])	{
		return;
	}

	apNodeItem->addNodePort(QString("Hello2"));
	if (fName == s_listName[1]) {
		return;
	}

	apNodeItem->addNodePort(QString("Hello3"));
	if (fName == s_listName[2]) {
		return;
	}

	return;
}

void NodeGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
	if (! event->mimeData()->hasUrls()) {
		return;
	}

	qDebug() << "Enter";

	//	event->accept();
	event->acceptProposedAction();
}


void NodeGraphicsView::dropEvent(QDropEvent *event)
{
	if (! event->mimeData()->hasUrls()) {
		return;
	}

	QList<QUrl> urlList;
	QString fName;

	urlList = event->mimeData()->urls(); // retrieve list of urls

	foreach(QUrl url, urlList) // iterate over list
	{
		fName = url.toLocalFile();
		qDebug() << "fName = " << fName;
		_putNodeItem(fName, event->pos());
	}
    event->acceptProposedAction();
}


void NodeGraphicsView::dragMoveEvent(QDragMoveEvent* event)
{
	// if not left button - return
	//if (!(event->button() & Qt::LeftButton)) return;
 
//	qDebug() << "dragMoveEvent" << event->pos();
}


void NodeGraphicsView::mousePressEvent(QMouseEvent* event)
{
	Qt::MouseButton qBtn = event->button();

	if (!_isMouseTranslate && qBtn & Qt::MidButton) {
		_nPressMouseX = event->x();
		_nPressMouseY = event->y();
		_isMouseTranslate = true;
	}

	QGraphicsView::mousePressEvent(event);
}


/* [NOTE] (代替手段) QGraphicsScene 内で保持しているアイテムを各自移動させる。*/
void NodeGraphicsView::_translateSceneItem(int nMouseX, int nMouseY)
{
	QList<QGraphicsItem*> listItems = m_pScene->items();
	foreach(QGraphicsItem* item, listItems) {
		if (item->type() == Type_NodeItem) {
			item->moveBy(nMouseX, nMouseY);
		}
	}
}


void NodeGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
	if (_isMouseTranslate) {
		int nMouseX, nMouseY;
		nMouseX = event->x() - _nPressMouseX;
		nMouseY = event->y() - _nPressMouseY;
#if 0
		/* [NOTE] Qt Bug ? 
			QGraphicsView::translate() が機能しないため別手段で行う。
		*/
		this->translate(nMouseX, nMouseY);
#else
		/* [NOTE] (代替手段) QGraphicsScene 内で保持しているアイテムを各自移動させる。*/
		_translateSceneItem(nMouseX, nMouseY);
		_nPressMouseX = event->x();
		_nPressMouseY = event->y();
#endif
	}

	QGraphicsView::mouseMoveEvent(event);
}


void NodeGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
	QGraphicsView::mouseReleaseEvent(event);

	if (_isMouseTranslate) {
		_isMouseTranslate = false;
	}
}


void NodeGraphicsView::wheelEvent(QWheelEvent* event)
{
	int zoom = event->delta();

	if (zoom > 0) {
		this->scale(SPEC_VIEW_SCALE_VACTOR, SPEC_VIEW_SCALE_VACTOR);
	} else {
		this->scale(1.0f / SPEC_VIEW_SCALE_VACTOR, 1.0f / SPEC_VIEW_SCALE_VACTOR);
	}
}
