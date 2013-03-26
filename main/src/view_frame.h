#ifndef __VIEW_FRAME_H__
#define __VIEW_FRAME_H__

#include <QFrame>


class ViewFrame : public QFrame
{
	Q_OBJECT

public:
	ViewFrame(QWidget* parent = 0);

protected:
	void paintEvent(QPaintEvent *event);

public:
	QWidget* m_pParent;

};

#endif /* __VIEW_FRAME_H__ */
