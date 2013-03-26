#pragma once

#include <QWidget>

//
class TimeLineSlider : public QWidget
{
	Q_OBJECT

public:
	TimeLineSlider();

	void setCurrentFrame(int currentFrame);
	void setKeyFrames(const QVector< bool > &keyFrames);
	QVector< bool > keyFrames() { return keyFrames_; }
	void setTimeLine(float fStart, float fEnd);

signals:
	void currentFrameChanged(int currentFrame);

private:
	QVector< bool > keyFrames_;

	bool ldragged_;
	bool rdragged_;

	int current_;
	int offset_;
	int prex_;

	int o0_;
	int x0_;


	void mousePressEvent(QMouseEvent *evt);
	void mouseReleaseEvent(QMouseEvent *evt);
	void mouseMoveEvent(QMouseEvent *evt);
	void paintEvent(QPaintEvent *evt);

	int toScreen(int frame);
	int toFrame(int x);
	void updateFrame(int x);
};

