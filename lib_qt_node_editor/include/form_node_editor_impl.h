#ifndef __FORM_NODE_EDITOR_IMPL_H__
#define __FORM_NODE_EDITOR_IMPL_H__

#include "ui_form_node_editor.h"


class NodeGraphicsView;
class QDockWidget;
class FormNodeDataListImpl;
class FormNodeSideImpl;


class FormNodeEditorImpl: public QMainWindow
{
	Q_OBJECT

public:
	FormNodeEditorImpl(QWidget * parent = 0); /* [NOTE:001] main()プログラムから使われること */
	~FormNodeEditorImpl();
	static FormNodeEditorImpl* getInstance(); /* [NOTE:001] main()プログラムから FormNodeEditorImpl() が呼ばれた後で使用すること */
	int init();
	void fin();

protected:
	/* override */
	void closeEvent(QCloseEvent *pEvent);
	void keyReleaseEvent(QKeyEvent* pEvent);
	void keyPressEvent(QKeyEvent* pEvent);


private:
	void _layout();
	void _showForm(QWidget* pWidget, const QString& rqStr, Qt::DockWidgetAreas allowedDockArea, Qt::DockWidgetArea initDockArea);

public:
	Ui::FormNodeEditor m_ui;
	NodeGraphicsView* m_pNodeView;
	FormNodeDataListImpl* m_pFormNodeDataListImpl;
	FormNodeSideImpl* m_pFormNodeSideImpl;

private:
	static FormNodeEditorImpl* _pThisInstance;
	QList<QDockWidget*> listDockWidgets;
	bool _isEnableFormDockable;

};

#endif /* __FORM_NODE_EDITOR_IMPL_H__ */
