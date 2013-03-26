#ifndef __PANEL_TIME_LINE_WIDGET_H__
#define __PANEL_TIME_LINE_WIDGET_H__

#include <QDockWidget>
#include <QPushButton>

class TimeLineSlider;

//!
class PanelTimeLineWidget : public QDockWidget
{
	Q_OBJECT
public:
	PanelTimeLineWidget(QWidget *parent = 0);
	float getCurrentTime();

signals:
	void closed();
private:
	TimeLineSlider *_pTimeLineSlider;
	QPushButton *_pBtnPlay;

	void closeEvent(QCloseEvent *evt);

private slots:
	//
	void onCurrentFrameChanged(int currentFrame);
	void onPlayClicked(bool checked);
	void onPreviousFrameClicked(bool checked);
	void onNextFrameClicked(bool checked);
	void onStartFrameClicked(bool checked);
	void onEndFrameClicked(bool checked);
	void onKeyFrameClicked(bool checked);
	void onRemoveKeyFrameClicked(bool checked);
	void onFilterClicked(bool checked);
	void onAutoKeyChecked(bool checked);

private:
	bool _isAnimated;
	float _fCurrentTime;
	float _fTimePosStart;
	float _fTimePosEnd;

};

#endif /* __PANEL_TIME_LINE_WIDGET_H__ */
