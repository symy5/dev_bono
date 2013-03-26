#ifndef __VIEW_MAIN_H__
#define __VIEW_MAIN_H__

#include <QWidget>

class Splitter;
class ViewWidget;

class ViewMain : public QWidget
{
	Q_OBJECT

public:
	enum View_Position {
		VIEW_POS_LEFT_UP,
		VIEW_POS_LEFT_DOWN,
		VIEW_POS_RIGHT_UP,
		VIEW_POS_RIGHT_DOWN
	};

public:
	ViewMain(QWidget* parent = 0);
	void setView(int viewPos, QWidget* pWidget);

public:
	/* override */
	virtual void keyPressEvent(QKeyEvent* e);
	virtual void keyReleaseEvent(QKeyEvent* e);

private:
	void _setupSplit4();

public:
	bool m_isSplite;
	Splitter* m_pSplitterH;
	Splitter* m_pSplitterV1;
	Splitter* m_pSplitterV2;
	
	int m_nCurrent;
	QWidget* m_pCurrentWidget;
	ViewWidget* m_pWidgetLeftUp;
	ViewWidget* m_pWidgetLeftDown;
	ViewWidget* m_pWidgetRightUp;
	ViewWidget* m_pWidgetRightDown;

	QList<int> m_listHSizes;
	QList<int> m_listV1Sizes;
	QList<int> m_listV2Sizes;
};

#endif /* __VIEW_MAIN_H__ */
