#include "view_widget.h"
#include "view_frame.h"
#include <QApplication>
#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QAction>


ViewWidget::ViewWidget(QString name, QWidget* parent)
		: QWidget(parent)
{
	m_name = name;

	QVBoxLayout *pLayoutMain = new QVBoxLayout;

	m_pFrame = new ViewFrame(this);
	{
		QVBoxLayout *pLayout = new QVBoxLayout(this);
//		pLayout->addWidget(new ColladaWidget(this));
		m_pFrame->setLayout(pLayout);
	}
    pLayoutMain->addWidget(m_pFrame);

	this->setLayout(pLayoutMain);
	this->autoFillBackground();
	this->setFocusPolicy(Qt::ClickFocus);

	_setupMenu();
}


void ViewWidget::_setupMenu()
{
	QLayout* pLayout = this->layout();
	QAction *action;

	QMenuBar *bar = new QMenuBar();

	/* Display */
	{
		m_pMenuDisplay = bar->addMenu(tr("Display"));
		connect(m_pMenuDisplay, SIGNAL(triggered(QAction *)), this, SLOT(slot_onMenuDisplay(QAction*)));

		action = new QAction(tr("Test1"), this);
		m_pMenuDisplay->addAction(action);

		m_pMenuDisplay->addSeparator();

		action = new QAction(tr("Test2"), this);
		m_pMenuDisplay->addAction(action);
	}

	/* Panel */
	{
		m_pMenuPanel = bar->addMenu(tr("Panel"));
		connect(m_pMenuPanel, SIGNAL(triggered(QAction *)), this, SLOT(slot_onShowPanel(QAction*)));

		action = new QAction(tr("All"), this);
		m_pMenuPanel->addAction(action);
	}

	/* Camera */
	{
		m_pMenuCamera = bar->addMenu(tr("[Pespective]"));
		connect(m_pMenuCamera, SIGNAL(triggered(QAction *)), this, SLOT(slot_onMenuCamera(QAction*)));

		action = new QAction(tr("[Left]"), this);
		m_pMenuCamera->addAction(action);

		action = new QAction(tr("[Right]"), this);
		m_pMenuCamera->addAction(action);

		action = new QAction(tr("[Top]"), this);
		m_pMenuCamera->addAction(action);

		action = new QAction(tr("[bottom]"), this);
		m_pMenuCamera->addAction(action);
	}


	pLayout->setMenuBar(bar);
}

void ViewWidget::keyPressEvent(QKeyEvent* e)
{
	QWidget::keyPressEvent(e);
}


void ViewWidget::keyReleaseEvent(QKeyEvent* e)
{
	QWidget::keyReleaseEvent(e);
}


void ViewWidget::slot_onMenuCamera(QAction *action)
{
	m_pMenuCamera->setTitle(action->text());
}

void ViewWidget::slot_onMenuDisplay(QAction *action)
{
}


void ViewWidget::slot_onShowPanel(QAction *action)
{
}
