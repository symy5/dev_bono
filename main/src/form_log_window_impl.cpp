#include "form_log_window_impl.h"


FormLogWindowImpl::FormLogWindowImpl(QWidget* parent /*= 0*/)
	: QWidget(parent)
{
	m_vForm.setupUi(this);

	_createContextMenu();
}


void FormLogWindowImpl::_createContextMenu()
{
	_pqContextMenu = new QMenu(this);

	_pqActionCopy = new QAction(tr("Copy"), this);
	connect(_pqActionCopy, SIGNAL(triggered()), this, SLOT(slot_action_copy()));
	_pqContextMenu->addAction(_pqActionCopy);
	_pqContextMenu->addSeparator(); 

	/* �R���e�L�X�g���j���[�̐ݒ� */
	m_vForm.listWidgetLogWindow->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(m_vForm.listWidgetLogWindow, SIGNAL(customContextMenuRequested(const QPoint&)),
			this, SLOT(slot_showContextMenu(const QPoint&)));
}


void FormLogWindowImpl::settings(QSettings* pqSettings, bool isWrite)
{
	if (isWrite) {
		/* �Z�b�e�B���O��ۑ� */
	} else {
		/* �Z�b�e�B���O��ǂݍ��� */
	}
}


void FormLogWindowImpl::logout(const QString& rqStr)
{
	/* [NOTE]
		���X�g�ɒǉ����ꂽ�ۂɁA�t�H�[�J�X�ʒu��ǉ����ꂽ�ʒu�ɂ��邽�߁A
		�J�����g�ʒu��ύX����B
	*/
	int nCnt = m_vForm.listWidgetLogWindow->count();
	m_vForm.listWidgetLogWindow->addItem(rqStr);
	m_vForm.listWidgetLogWindow->setCurrentRow(nCnt);
	QModelIndex index = m_vForm.listWidgetLogWindow->currentIndex();
	m_vForm.listWidgetLogWindow->scrollTo(index, QAbstractItemView::EnsureVisible);
}


void FormLogWindowImpl::slot_action_copy()
{
	QAbstractItemModel* qModel = m_vForm.listWidgetLogWindow->model(); // ���f���̎擾�B
	if (qModel == 0) {
		return;
	}

	QModelIndex qIndex = m_vForm.listWidgetLogWindow->currentIndex();
	QVariant qVariant = qModel->data(qIndex); // �J�����g�ʒu����l�̎擾�B�l��QVariant�^�B
	QString qStr = qVariant.toString(); // QString�ɕϊ��B

	/* [NOTE]
	  ��̃A�v���P�[�V�����ɂ� QClipboard �͈�������݂��A
	  QApplication::clipboard() ���g���� QClipboard �I�u�W�F�N�g��
	  �A�N�Z�X���邱�Ƃ��ł���B 
	 */
	QClipboard *qClip = QApplication::clipboard();
	qClip->setText(qStr);
}


void FormLogWindowImpl::slot_pushButtonClear()
{
	m_vForm.listWidgetLogWindow->clear();
}


void FormLogWindowImpl::slot_showContextMenu(const QPoint& rqPoint)
{
	_pqContextMenu->exec(mapToGlobal(rqPoint));
}
