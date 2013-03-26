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
		QMainWindow::AllowNestedDocks ��ݒ肵�Ȃ��� Dock �̗ד��m�㉺���E�ɒu�����Ƃ��ł��Ȃ��B
	 */
	this->setDockOptions(QMainWindow::AllowNestedDocks);
}


/*
	�E�E�B���h�E�\�����s��
	�E���� DockWidget �ɓo�^�ς݂̏ꍇ�́A��U�폜���s���\�����s��
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

void FormNodeEditorImpl::closeEvent(QCloseEvent *pEvent)
{
	pEvent->accept(); // [NOTE] ignore() ������ƏI�����܂���B
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
		setFocus(); /* [NOTE] keyReleaseEvent() ���R�[������邽�߂ɕK�v */
	}
	//pEvent->accept();
#endif
}
