#include "form_node_side_impl.h"
#include "form_node_editor_impl.h"


FormNodeSideImpl::FormNodeSideImpl(QWidget* parent/* = 0 */)
	: QWidget(parent)
{
	m_vForm.setupUi(this);
}


int FormNodeSideImpl::init()
{
	return 0;
}


void FormNodeSideImpl::fin()
{
}
