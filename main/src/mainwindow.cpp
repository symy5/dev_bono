#include "mainwindow.h"
#include "app_qt_data.h"
#include "form_log_window_impl.h"
#include "form_node_editor_impl.h"
#include "panel_time_line_widget.h"
#include "view_main.h"
#include <QCloseEvent>

#define APP_GL_WINDOW_MIN_SIZE_W	100
#define APP_GL_WINDOW_MIN_SIZE_H	100

MainWindow* MainWindow::_pThisInstance = 0;


MainWindow::MainWindow(QWidget * parent):QMainWindow (parent)
{
	m_ui.setupUi (this);
	_isEnableFormDockable = true;

	_pFormLogWindowImpl = new FormLogWindowImpl();
	m_pFormNodeEditorImpl = new FormNodeEditorImpl(this);
	m_pTimeLineWidget = new PanelTimeLineWidget(this);

	
	/* view */
	m_pViewMain = new ViewMain();
	m_ui.glFrameLayout->addWidget(m_pViewMain);

	_layout();

	_pThisInstance = this;
}

MainWindow::~MainWindow()
{
	//delete m_pFormColladaDataToolImpl;
	/* view */
	delete m_pViewMain;
	// m_pTimeLineWidget will free by Qt System(beacause of using 'this' parameter).

	delete _pFormLogWindowImpl;
}


void MainWindow::_initGLWidget(QWidget* pGLWidget)
{
	pGLWidget->setMinimumSize(QSize(APP_GL_WINDOW_MIN_SIZE_W, APP_GL_WINDOW_MIN_SIZE_H));
	pGLWidget->setAutoFillBackground(true);
	pGLWidget->hide();
	m_pViewMain->setView(ViewMain::VIEW_POS_LEFT_DOWN, pGLWidget);
#if 0
	m_pViewMain->setView(ViewMain::VIEW_POS_LEFT_DOWN, pGLWidget);
	m_pViewMain->setView(ViewMain::VIEW_POS_RIGHT_UP, pGLWidget);
	m_pViewMain->setView(ViewMain::VIEW_POS_RIGHT_DOWN, pGLWidget);
#endif
}


void MainWindow::_layout()
{
	/* [NOTE]
		QMainWindow::AllowNestedDocks ��ݒ肵�Ȃ��� Dock �̗ד��m�㉺���E�ɒu�����Ƃ��ł��Ȃ��B
	 */
	this->setDockOptions(QMainWindow::AllowNestedDocks);

	slot_showTimeLine();
	slot_showFormLogWindow();
	slot_showFormColladaDataTool();
}


/*
	�E�E�B���h�E�\�����s��
	�E���� DockWidget �ɓo�^�ς݂̏ꍇ�́A��U�폜���s���\�����s��
 */
void MainWindow::_showForm(QWidget* pWidget, const QString& rqStr, Qt::DockWidgetAreas allowedDockArea, Qt::DockWidgetArea initDockArea)
{
	int nDockCnt = listDockWidgets.size();
	for (int i = 0; i < nDockCnt; i++) {
		QWidget* pWidgetTmp = listDockWidgets[i]->widget();
		if (pWidgetTmp == pWidget) {
			this->removeDockWidget(listDockWidgets[i]);
			listDockWidgets[i]->setWidget(NULL);
			/* [NOTE]
				��x�ADockWidget������ widget �� show() ���Ă��\������Ȃ���肪���������B
				���̑Ώ��Ƃ��āAsetParent(NULL) �𖾎��I�ɍs�����Ƃ���Ashow()�ɂĕ\���ł���悤�ɂȂ����B
				���݂̏�Ԃ��ApWidgetTmp->isVisibleTo(listDockWidgets[i]) �ɂ� true �̏�Ԃł��邽�߁A
				�e�l���O���K�v������Ǝv����B
			 */
			pWidgetTmp->setParent(NULL);
			listDockWidgets.removeAt(i);
			break;
		}
	}

	if (_isEnableFormDockable) {

		QDockWidget* pDock = new QDockWidget(rqStr, this);

		pDock->setWidget(pWidget);
		pDock->setAllowedAreas(allowedDockArea);
		addDockWidget(initDockArea, pDock, Qt::Horizontal);
		pDock->show();

		listDockWidgets.push_back(pDock);

	} else {
		pWidget->show();
	}
}

void MainWindow::closeEvent(QCloseEvent *pEvent)
{
	pEvent->accept(); // [NOTE] ignore() ������ƏI�����܂���B
}


MainWindow* MainWindow::getInstance()
{
	return _pThisInstance;
}


void MainWindow::init()
{
}


void MainWindow::_showGLWidget()
{
}


void MainWindow::startGL()
{
	_showGLWidget();
}


void MainWindow::keyReleaseEvent(QKeyEvent* pEvent)
{
#if 0
	if (_isEnableFormDockable) {
		_isEnableFormDockable = false;
	}
#endif
}


void MainWindow::keyPressEvent(QKeyEvent* pEvent)
{
#if 0
	if (pEvent->modifiers() == Qt::ControlModifier) {
		_isEnableFormDockable = true;
		setFocus(); /* [NOTE] keyReleaseEvent() ���R�[������邽�߂ɕK�v */
	}
	//pEvent->accept();
#endif
}

void MainWindow::logout(const QString& rqStr)
{
	_pFormLogWindowImpl->logout(rqStr);
}


void MainWindow::slot_showFormColladaDataTool()
{
}


void MainWindow::slot_showFormLogWindow()
{
	if (! m_pTimeLineWidget->isVisible()) {
		QDockWidget* apDockLogWindow = new QDockWidget(tr("DockLogWindow"), this);
		apDockLogWindow->setWidget(_pFormLogWindowImpl);
		apDockLogWindow->setAllowedAreas(AppQtData::AreaDefaultLandscape);
		addDockWidget(Qt::BottomDockWidgetArea, apDockLogWindow, Qt::Vertical);
	}
}


void MainWindow::slot_showFormNodeEditor()
{
	logout(QString("[TEST] show NodeEditor"));
	if (! m_pFormNodeEditorImpl->isVisible()) {
		//_showForm(m_pFormNodeEditorImpl, tr("FormNodeEditor"), AppQtData::AreaDefaultTool, Qt::LeftDockWidgetArea);
		m_pFormNodeEditorImpl->init();
		m_pFormNodeEditorImpl->show();
	}
}


void MainWindow::slot_showTimeLine()
{
	if (! m_pTimeLineWidget->isVisible()) {
		m_pTimeLineWidget->setAllowedAreas(AppQtData::AreaDefaultLandscape);
		addDockWidget(Qt::BottomDockWidgetArea, m_pTimeLineWidget, Qt::Vertical);
		m_pTimeLineWidget->show();
	}
}

