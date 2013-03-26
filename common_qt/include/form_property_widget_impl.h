#ifndef __FORM_PROPERTY_WIDGET_IMPL_H__
#define __FORM_PROPERTY_WIDGET_IMPL_H__

#include "ui_form_property_widget.h"
#include <QtGui>


class FormPropertyWidgetImpl : public QWidget
{
	Q_OBJECT
public:
	FormPropertyWidgetImpl(QWidget* pInner = 0, QWidget* parent = 0);
	~FormPropertyWidgetImpl();
	void setInnerWidget(QWidget* pInner);

protected: /* override */
	void showEvent(QShowEvent* pEvent);

protected slots:
	void slot_pushButtonClose();
	void slot_pushButtonReset();
	void slot_pushButtonSave();

private:

public:
	Ui_FormPropertyWidget m_vForm;
	QWidget* m_pInner;
};

#endif /* __FORM_PROPERTY_WIDGET_IMPL_H__ */
