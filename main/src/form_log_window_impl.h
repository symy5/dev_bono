#ifndef __FORM_LOG_WINDOW_IMPL_H__
#define __FORM_LOG_WINDOW_IMPL_H__

#include "ui_form_log_window.h"
#include <QtGui>

class FormLogWindowImpl : public QWidget
{
	Q_OBJECT
public:
	FormLogWindowImpl(QWidget* parent = 0);
	void settings(QSettings* pqSettings, bool isWrite);
	void logout(const QString& rqStr);

protected slots:
	void slot_action_copy();
	void slot_pushButtonClear();
	void slot_showContextMenu(const QPoint& rqPoint);

private:
	void _createContextMenu();

public:
	Ui_FormLogWindow m_vForm;

private:
	QMenu* _pqContextMenu;
	QAction* _pqActionCopy;
};

#endif /* __FORM_LOG_WINDOW_IMPL_H__ */
