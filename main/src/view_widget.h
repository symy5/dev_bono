#ifndef __VIEW_WIDGET_H__
#define __VIEW_WIDGET_H__

#include <QWidget>

class ViewFrame;
class QAction;
class QMenu;

class ViewWidget : public QWidget
{
	Q_OBJECT

public:
	ViewWidget(QString name, QWidget* parent = 0);

public:
	/* override */
	virtual void keyPressEvent(QKeyEvent* e);
	virtual void keyReleaseEvent(QKeyEvent* e);

public slots:
	void slot_onMenuCamera(QAction *action);
	void slot_onMenuDisplay(QAction *action);
	void slot_onShowPanel(QAction* action);

private:
	void _setupMenu();

public:
	ViewFrame* m_pFrame;

public:
	QString m_name;
	QMenu* m_pMenuCamera;
	QMenu* m_pMenuDisplay;
	QMenu* m_pMenuPanel;
};

#endif /* __VIEW_WIDGET_H__ */
