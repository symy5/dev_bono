#ifndef __FORM_NODE_SIDE_IMPL_H__
#define __FORM_NODE_SIDE_IMPL_H__

#include "ui_form_node_side.h"
#include <QtGui>
#include <QStringList>

class FormNodeSideImpl : public QWidget
{
	Q_OBJECT
public:
	FormNodeSideImpl(QWidget* parent = 0);
	int init();
	void fin();

public:
	Ui_FormNodeSide m_vForm;

private:
};

#endif /* __FORM_NODE_SIDE_IMPL_H__ */
