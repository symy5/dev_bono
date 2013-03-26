#include "form_property_widget_impl.h"


FormPropertyWidgetImpl::FormPropertyWidgetImpl(QWidget* pInner /* = 0 */, QWidget* parent /* = 0 */) : QWidget(parent)
{
	m_vForm.setupUi(this);

	this->setInnerWidget(pInner);
}


FormPropertyWidgetImpl::~FormPropertyWidgetImpl()
{
}


void FormPropertyWidgetImpl::showEvent(QShowEvent* pEvent)
{
	return;
}

void FormPropertyWidgetImpl::setInnerWidget(QWidget* pInner)
{
	m_pInner = pInner;
	if (m_pInner) {
		m_vForm.scrollAreaProperty->setWidget(m_pInner);
	}

	return;
}


void FormPropertyWidgetImpl::slot_pushButtonClose()
{
	close();
}


void FormPropertyWidgetImpl::slot_pushButtonReset()
{
	/* TBD */
}


void FormPropertyWidgetImpl::slot_pushButtonSave()
{
	/* TBD */
}

