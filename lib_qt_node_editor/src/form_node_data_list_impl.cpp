#include "form_node_data_list_impl.h"
#include "form_node_editor_impl.h"
#include "list_widget_drag_drop.h"



FormNodeDataListImpl::FormNodeDataListImpl(QWidget* parent/* = 0 */)
	: QWidget(parent)
{
	m_vForm.setupUi(this);
//	setAcceptDrops(true);

	/* set node names. */
	_listNodeNames << "NodeItem1" << "NodeItem2" << "NodeItem3";

	{
		_apListNodeNames = new ListWidgetDragDrop(this);
		m_vForm.layoutNodeData->addWidget(_apListNodeNames);

	}

}


int FormNodeDataListImpl::init()
{
	int nCnt = _listNodeNames.size();
	for (int i = 0; i < nCnt; i++) {
		_apListNodeNames->addItem(_listNodeNames[i]);
	}

	return 0;
}

void FormNodeDataListImpl::fin()
{
}


void FormNodeDataListImpl::dragEnterEvent(QDragEnterEvent* pEvent)
{
	// Accept file names or URLs.
	if (pEvent->mimeData()->hasFormat("text/uri-list")) {
		pEvent->acceptProposedAction();
	}
}


void FormNodeDataListImpl::dropEvent(QDropEvent* pEvent)
{
	QList<QUrl> listUrls = pEvent->mimeData()->urls();
	if (listUrls.isEmpty()) {
		return;
	}

	int nCnt = listUrls.size();
	for (int i = 0; i < nCnt; i++) {
		QUrl url = listUrls[i];
		QString path = QDir::toNativeSeparators(url.toLocalFile());
	}

	return;
}
