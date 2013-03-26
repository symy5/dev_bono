#include "view_frame.h"
#include <QApplication>
#include <QPainter>


ViewFrame::ViewFrame(QWidget* parent)
		: QFrame(parent)
{
	m_pParent = parent;
	this->setFrameStyle(QFrame::Box);
	this->setStyleSheet("color:blue");
}


void ViewFrame::paintEvent(QPaintEvent *event)
{
	if (m_pParent && m_pParent->hasFocus()) {
		this->setLineWidth(1);
	} else {
		this->setLineWidth(0);
	}

	QFrame::paintEvent(event);
}
