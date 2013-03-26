#include "view_main.h"
#include "view_splitter.h"
#include "view_widget.h"
#include "view_frame.h"

#include <QApplication>
#include <QLabel>
#include <QLayout>
#include <QKeyEvent>

#define TEST_ONE_WIDGET

ViewMain::ViewMain(QWidget* parent /* = 0*/)
		: QWidget(parent)
{
	m_pWidgetLeftUp = new ViewWidget("leftup", this);
	m_pWidgetLeftDown = new ViewWidget("leftdown", this);
	m_pWidgetRightUp = new ViewWidget("rightup", this);
	m_pWidgetRightDown = new ViewWidget("rightdown", this);
#if 0
	m_pWidgetLeftUp = new ViewWidget("A", this);
#ifdef TEST_ONE_WIDGET
	m_pWidgetLeftDown = new QWidget(this);
	m_pWidgetRightUp = new QWidget(this);
	m_pWidgetRightDown = new QWidget(this);
#else
	m_pWidgetLeftDown = new ViewWidget("B", this);
	m_pWidgetRightUp = new ViewWidget("C", this);
	m_pWidgetRightDown = new ViewWidget("D", this);
#endif
#endif
	m_pSplitterH = 0;
	m_pSplitterV1 = 0;
	m_pSplitterV2 = 0;

	_setupSplit4();

	QVBoxLayout* pLayout = new QVBoxLayout(this);
	this->setLayout(pLayout);
	this->layout()->addWidget(m_pSplitterH);
	m_pWidgetLeftDown->setFocus(); /* default */

	m_isSplite = true;

	this->autoFillBackground();
}


void ViewMain::_setupSplit4()
{
	if (m_pSplitterH) {
		/* m_pSplitterH を削除するため、親と切り離す必要がある */
		m_pWidgetLeftDown->setParent(0);
		m_pWidgetLeftUp->setParent(0);
		m_pWidgetRightDown->setParent(0);
		m_pWidgetRightUp->setParent(0);

		delete m_pSplitterH; /* [NOTE] m_pSplitterV1 と m_pSplitterV2 もこのタイミングでファイナライザ(削除)される */ 
	}
	m_pSplitterH = new Splitter(Qt::Horizontal, this);
	m_pSplitterV1 = new Splitter(Qt::Vertical, m_pSplitterH);
	m_pSplitterV2 = new Splitter(Qt::Vertical, m_pSplitterH);

	/* left pain up and down */
	
	m_pSplitterV1->addWidget(m_pWidgetLeftDown);
	m_pSplitterV1->addWidget(m_pWidgetLeftUp);
	/* right pain up and down */
	m_pSplitterV2->addWidget(m_pWidgetRightDown);
	m_pSplitterV2->addWidget(m_pWidgetRightUp);
}


void ViewMain::keyPressEvent(QKeyEvent* e)
{
	QWidget::keyPressEvent(e);
}


void ViewMain::keyReleaseEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key_Space) {

		if (m_isSplite) {
			m_pCurrentWidget = QApplication::focusWidget();
			if (m_pCurrentWidget) {
				/* backup */
				{
					m_listHSizes = m_pSplitterH->sizes();
					m_listV1Sizes = m_pSplitterV1->sizes();
					m_listV2Sizes = m_pSplitterV2->sizes();
				}
				m_pSplitterH->hide();
				this->layout()->removeWidget(m_pSplitterH);
				this->layout()->addWidget(m_pCurrentWidget);
				m_pCurrentWidget->setFocus();
			}
			m_isSplite = false;
		} else {
			if (m_pCurrentWidget) {
				_setupSplit4();
				/* reset */
				{
					m_pSplitterV1->setSizes(m_listV1Sizes);
					m_pSplitterV2->setSizes(m_listV2Sizes);
					m_pSplitterH->setSizes(m_listHSizes);
				}

				this->layout()->addWidget(m_pSplitterH);
				m_pSplitterH->show();
				m_pCurrentWidget->setFocus();
				m_pCurrentWidget = NULL; // init
			}
			m_isSplite = true;
		}
	}

	QWidget::keyReleaseEvent(e);
}


void ViewMain::setView(int viewPos, QWidget* pWidget)
{
	if (! pWidget) {
		/* nothing to do. */
		return;
	}

	ViewWidget* pViewWidget = 0;
	
	if (viewPos == VIEW_POS_LEFT_UP) {
		pViewWidget = m_pWidgetLeftUp;
	} else if (viewPos == VIEW_POS_LEFT_DOWN) {
		pViewWidget = m_pWidgetLeftDown;
	} else if (viewPos == VIEW_POS_RIGHT_UP) {
		pViewWidget = m_pWidgetRightUp;
	} else if (viewPos == VIEW_POS_RIGHT_DOWN) {
		pViewWidget = m_pWidgetRightDown;
	}

	if (pViewWidget == 0) {
		/* nothing to do. */
		return;
	}

	pViewWidget->m_pFrame->layout()->addWidget(pWidget);
}
