#include "time_line_slider.h"
#include <QPainter>
#include <QMouseEvent>
#include <iostream>

//
TimeLineSlider::TimeLineSlider() :
ldragged_(false),
rdragged_(false),
current_(0),
offset_(0)
{
}

void TimeLineSlider::setKeyFrames(const QVector< bool > &keyFrames)
{
	keyFrames_ = keyFrames;
}

//
void TimeLineSlider::mousePressEvent(QMouseEvent *evt)
{
	if(evt->button() == Qt::LeftButton)
	{
		ldragged_ = true;
		updateFrame(evt->x());
	}
	else if(evt->button() == Qt::RightButton)
	{
		rdragged_ = true;
		x0_ = evt->x();
		o0_ = offset_;
	}
}

//
void TimeLineSlider::mouseReleaseEvent(QMouseEvent *evt)
{
	if(evt->button() == Qt::LeftButton)
	{
		ldragged_ = false;
	}
	else if(evt->button() == Qt::RightButton)
	{
		rdragged_ = false;
	}
}

//
void TimeLineSlider::mouseMoveEvent(QMouseEvent *evt)
{
	if(ldragged_)
	{
		updateFrame(evt->x());
	}

	if(rdragged_)
	{
		offset_ = o0_ + (x0_ - evt->x()) / 10;
		if(offset_ < 0)
		{
			offset_ = 0;
		}

		update();
	}
}

//
void TimeLineSlider::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

	float fVal = 115/(float)255;
	QBrush brush(QColor::fromRgbF(fVal, fVal, fVal, 1.0f), Qt::SolidPattern);
	painter.setBrush(brush);
	painter.drawRect(0, 0, width(), height());

	painter.setPen(Qt::black);
	painter.setBrush(Qt::black);
	for (int i = 0 ; i < width() / 10 ; ++i) {
		int f = offset_ + i;
		int x = toScreen(f);

		if (f % 10 == 0) {
			painter.drawLine(x, 0, x, 20);
			painter.drawText(x + 4, 20, QString::number(f));
		} else if(f % 5 == 0) {
			painter.drawLine(x, 0, x, 10);
		} else {
			painter.drawLine(x, 0, x, 5);
		}
	}

	painter.setPen(Qt::red);
	int start = toFrame(10);
	int end = toFrame(width());
	if (end >= keyFrames_.count()) {
		end = keyFrames_.count();
	}
	for (int i = start ; i < end ; ++i) {
		if (keyFrames_[ i ]) {
			int x = toScreen(i);
			painter.drawLine(x, 0, x, height());
		}
	}

	//
	int c = toScreen(current_);
	painter.setPen(Qt::black);
	painter.drawLine(c, 0, c, height());
}


//
int TimeLineSlider::toScreen(int frame)
{
	return 10 + 10 * (frame - offset_);
}

//
int TimeLineSlider::toFrame(int x)
{
	int frame = (x - 10) / 10 + offset_;
	if (frame < 0) {
		frame = 0;
	}
	return frame;
}

//
void TimeLineSlider::setCurrentFrame(int currentFrame)
{
	current_ = currentFrame;
	update();
}

//
void TimeLineSlider::updateFrame(int x)
{
	int frame = toFrame(x);
	if (frame == current_) {
		return;
	}
	current_ = frame;
	update();

	emit currentFrameChanged(current_);
}


void TimeLineSlider::setTimeLine(float fStart, float fEnd)
{

}