#ifndef __FORM_NODE_DATA_LIST_IMPL_H__
#define __FORM_NODE_DATA_LIST_IMPL_H__

#include "ui_form_node_data_list.h"
#include <QtGui>
#include <QStringList>

class ListWidgetDragDrop;

class FormNodeDataListImpl : public QWidget
{
	Q_OBJECT
public:
	FormNodeDataListImpl(QWidget* parent = 0);
	int init();
	void fin();

protected: /* override */
	void dragEnterEvent(QDragEnterEvent* pEvent);
	void dropEvent(QDropEvent* pEvent);

public:
	Ui_FormNodeDataList m_vForm;

private:
	QStringList _listNodeNames;
	ListWidgetDragDrop* _apListNodeNames;

};

#endif /* __FORM_NODE_DATA_LIST_IMPL_H__ */
