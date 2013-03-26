#include "form_node_editor_impl.h"
#include "node_graphics_view.h"
#include "form_node_data_list_impl.h"
#include "form_node_side_impl.h"
#include <QCloseEvent>
#include <QDockWidget>


FormNodeEditorImpl* FormNodeEditorImpl::_pThisInstance = 0;


FormNodeEditorImpl::FormNodeEditorImpl(QWidget * parent):QMainWindow (parent)
{
	m_pNodeView = NULL;
	m_pFormNodeDataListImpl = NULL;
	m_pFormNodeSideImpl = NULL;

	m_ui.setupUi(this);
	_isEnableFormDockable = true;

	_layout();
	
	_pThisInstance = this;
}

FormNodeEditorImpl::~FormNodeEditorImpl()
{
	fin();
}


void FormNodeEditorImpl::_layout()
{
	/* [NOTE]
		QMainWindow::AllowNestedDocks を設定しないと Dock の隣同士上下左右に置くことができない。
	 */
	this->setDockOptions(QMainWindow::AllowNestedDocks);
}


/*
	・ウィンドウ表示を行う
	・既に DockWidget に登録済みの場合は、一旦削除を行い表示を行う
 */
void FormNodeEditorImpl::_showForm(QWidget* pWidget, const QString& rqStr, Qt::DockWidgetAreas allowedDockArea, Qt::DockWidgetArea initDockArea)
{
	int nDockCnt = listDockWidgets.size();
	for (int i = 0; i < nDockCnt; i++) {
		QWidget* pWidgetTmp = listDockWidgets[i]->widget();
		if (pWidgetTmp == pWidget) {
			this->removeDockWidget(listDockWidgets[i]);
			listDockWidgets[i]->setWidget(NULL);
			/* [NOTE]
				一度、DockWidget化した widget を show() しても表示されない問題が発生した。
				その対処として、setParent(NULL) を明示的に行ったところ、show()にて表示できるようになった。
				現在の状態が、pWidgetTmp->isVisibleTo(listDockWidgets[i]) にて true の状態であるため、
				親値を外す必要があると思われる。
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

void FormNodeEditorImpl::closeEvent(QCloseEvent *pEvent)
{
	pEvent->accept(); // [NOTE] ignore() をすると終了しません。
}


FormNodeEditorImpl* FormNodeEditorImpl::getInstance()
{
	return _pThisInstance;
}


int FormNodeEditorImpl::init()
{
	int nRet;
	
	if (m_pNodeView) {
		return 0;
	}

	m_pNodeView = new NodeGraphicsView();
	nRet = m_pNodeView->init();
	if (nRet != 0) {
		return -1;
	}

	setCentralWidget(m_pNodeView);
	m_pNodeView->show();


	m_pFormNodeDataListImpl = new FormNodeDataListImpl(this);
	nRet = m_pFormNodeDataListImpl->init();
	if (nRet != 0) {
		return -1;
	}
	
	m_pFormNodeSideImpl = new FormNodeSideImpl(this);
	nRet = m_pFormNodeSideImpl->init();
	if (nRet != 0) {
		return -1;
	}

	_showForm(m_pFormNodeDataListImpl, tr("FormNodeDataListImpl"), Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea, Qt::LeftDockWidgetArea);
	_showForm(m_pFormNodeSideImpl, tr("FormNodeSideImpl"), Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea, Qt::RightDockWidgetArea);

	return 0;
}

void FormNodeEditorImpl::fin()
{
	if (m_pNodeView) {
		delete m_pNodeView;
		m_pNodeView = NULL;
	}

#if 0
	if (m_pFormNodeDataListImpl) {
		delete m_pFormNodeDataListImpl;
		m_pFormNodeDataListImpl = NULL;
	}
#endif
}

void FormNodeEditorImpl::keyReleaseEvent(QKeyEvent* pEvent)
{
#if 0
	if (_isEnableFormDockable) {
		_isEnableFormDockable = false;
	}
#endif
}


void FormNodeEditorImpl::keyPressEvent(QKeyEvent* pEvent)
{
#if 0
	if (pEvent->modifiers() == Qt::ControlModifier) {
		_isEnableFormDockable = true;
		setFocus(); /* [NOTE] keyReleaseEvent() がコールされるために必要 */
	}
	//pEvent->accept();
#endif
}
