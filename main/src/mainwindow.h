#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

/* view */
class ViewMain;
class FormColladaDataToolImpl;
class FormLogWindowImpl;
class FormNodeEditorImpl;
class MainManager;
class PanelTimeLineWidget;
class ColladaWidget;

class MainWindow: public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget * parent = 0); /* [NOTE:001] main()プログラムから使われること */
	~MainWindow();
	static MainWindow* getInstance(); /* [NOTE:001] main()プログラムから MainWindow() が呼ばれた後で使用すること */
	void init();
	void logout(const QString& rqStr);
	void startGL();
	
protected:
	/* override */
	void closeEvent(QCloseEvent *pEvent);
	void keyReleaseEvent(QKeyEvent* pEvent);
	void keyPressEvent(QKeyEvent* pEvent);

protected slots:
	void slot_showFormColladaDataTool();
	void slot_showFormLogWindow();
	void slot_showFormNodeEditor();
	void slot_showTimeLine();

signals:
	void signal_startGL();

private:
	void _initGLWidget(QWidget* pGLWidget);
	void _layout();
	void _showForm(QWidget* pWidget, const QString& rqStr, Qt::DockWidgetAreas allowedDockArea, Qt::DockWidgetArea initDockArea);
	void _showGLWidget();

public:
	Ui::mainWindow m_ui;
	PanelTimeLineWidget* m_pTimeLineWidget;
	/* view */
	ViewMain* m_pViewMain;
	FormColladaDataToolImpl* m_pFormColladaDataToolImpl;
	FormNodeEditorImpl* m_pFormNodeEditorImpl;
	ColladaWidget* m_pColladaWidget;

private:
	static MainWindow* _pThisInstance;
	QList<QDockWidget*> listDockWidgets;
	FormLogWindowImpl* _pFormLogWindowImpl;
	bool _isEnableFormDockable;

};

#endif
