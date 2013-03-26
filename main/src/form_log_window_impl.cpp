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

	/* コンテキストメニューの設定 */
	m_vForm.listWidgetLogWindow->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(m_vForm.listWidgetLogWindow, SIGNAL(customContextMenuRequested(const QPoint&)),
			this, SLOT(slot_showContextMenu(const QPoint&)));
}


void FormLogWindowImpl::settings(QSettings* pqSettings, bool isWrite)
{
	if (isWrite) {
		/* セッティングを保存 */
	} else {
		/* セッティングを読み込み */
	}
}


void FormLogWindowImpl::logout(const QString& rqStr)
{
	/* [NOTE]
		リストに追加された際に、フォーカス位置を追加された位置にするため、
		カレント位置を変更する。
	*/
	int nCnt = m_vForm.listWidgetLogWindow->count();
	m_vForm.listWidgetLogWindow->addItem(rqStr);
	m_vForm.listWidgetLogWindow->setCurrentRow(nCnt);
	QModelIndex index = m_vForm.listWidgetLogWindow->currentIndex();
	m_vForm.listWidgetLogWindow->scrollTo(index, QAbstractItemView::EnsureVisible);
}


void FormLogWindowImpl::slot_action_copy()
{
	QAbstractItemModel* qModel = m_vForm.listWidgetLogWindow->model(); // モデルの取得。
	if (qModel == 0) {
		return;
	}

	QModelIndex qIndex = m_vForm.listWidgetLogWindow->currentIndex();
	QVariant qVariant = qModel->data(qIndex); // カレント位置から値の取得。値はQVariant型。
	QString qStr = qVariant.toString(); // QStringに変換。

	/* [NOTE]
	  一つのアプリケーションには QClipboard は一つだけ存在し、
	  QApplication::clipboard() を使って QClipboard オブジェクトに
	  アクセスすることができる。 
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
