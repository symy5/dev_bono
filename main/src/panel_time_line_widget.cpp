#include "panel_time_line_widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QCheckBox>
#include <QCloseEvent>
#include "time_line_slider.h"

#define DEFAULT_TIME_POS_START		0
#define DEFAULT_TIME_POS_END		70


//
PanelTimeLineWidget::PanelTimeLineWidget(QWidget *parent) :
QDockWidget(tr("TimeLine"), parent)
{
	_isAnimated = false;
	_fCurrentTime = 0.0f;
	_fTimePosStart = DEFAULT_TIME_POS_START;
	_fTimePosEnd = DEFAULT_TIME_POS_END;

	QWidget *baseWidget = new QWidget();
	QHBoxLayout *pLayout = new QHBoxLayout();
	pLayout->setMargin(0);
	pLayout->setSpacing(0);

	//
	_pTimeLineSlider = new TimeLineSlider();
	pLayout->addWidget(_pTimeLineSlider);

	//
	QIcon iconStart(":/ex_start_frame.png");
	QPushButton *pBtnStart = new QPushButton(iconStart, "");
	pBtnStart->setMaximumSize(32, 32);
	pLayout->addWidget(pBtnStart);

	QIcon iconPre(":/ex_previous_frame.png");
	QPushButton *pBtnPre = new QPushButton(iconPre, "");
	pBtnPre->setMaximumSize(32, 32);
	pLayout->addWidget(pBtnPre);

	QIcon iconPlay(":/ex_play.png");
	_pBtnPlay = new QPushButton(iconPlay, "");
	_pBtnPlay->setMaximumSize(32, 32);
	pLayout->addWidget(_pBtnPlay);

	QIcon iconNext(":/ex_next_frame.png");
	QPushButton *pBtnNext = new QPushButton(iconNext, "");
	pBtnNext->setMaximumSize(32, 32);
	pLayout->addWidget(pBtnNext);

	QIcon iconEnd(":/ex_end_frame.png");
	QPushButton *pBtnEnd = new QPushButton(iconEnd, "");
	pBtnEnd->setMaximumSize(32, 32);
	pLayout->addWidget(pBtnEnd);

	baseWidget->setLayout(pLayout);

	setWidget(baseWidget);
	setMinimumHeight(50);
	setMaximumHeight(50);

	//
	connect(_pTimeLineSlider, SIGNAL(currentFrameChanged(int)), this, SLOT(onCurrentFrameChanged(int)));
	connect(_pBtnPlay, SIGNAL(clicked(bool)), this, SLOT(onPlayClicked(bool)));
	connect(pBtnPre, SIGNAL(clicked(bool)), this, SLOT(onPreviousFrameClicked(bool)));
	connect(pBtnNext, SIGNAL(clicked(bool)), this, SLOT(onNextFrameClicked(bool)));
	connect(pBtnStart, SIGNAL(clicked(bool)), this, SLOT(onStartFrameClicked(bool)));
	connect(pBtnEnd, SIGNAL(clicked(bool)), this, SLOT(onEndFrameClicked(bool)));
}

//
void PanelTimeLineWidget::closeEvent(QCloseEvent *evt)
{
	emit closed();
	evt->accept();
}


float PanelTimeLineWidget::getCurrentTime()
{
	return _fCurrentTime;
}


//
void PanelTimeLineWidget::onCurrentFrameChanged(int currentFrame)
{
	_fCurrentTime = (float)currentFrame / (_fTimePosEnd - _fTimePosStart);
	//symy _pTimeLineSlider->setCurrentFrame(currentFrame);
}

//
void PanelTimeLineWidget::onPlayClicked(bool)
{
	if (! _isAnimated) {
		/* start the animation */
		QIcon iconStop(":/ex_stop.png");
		_pBtnPlay->setWindowIcon(iconStop);

		_isAnimated = true;
	} else {
		/* stop the animation */
		QIcon iconPlay(":/ex_play.png");
		_pBtnPlay->setWindowIcon(iconPlay);

		_isAnimated = false;
	}
}

//
void PanelTimeLineWidget::onPreviousFrameClicked(bool)
{
}

//
void PanelTimeLineWidget::onNextFrameClicked(bool)
{
}

//
void PanelTimeLineWidget::onStartFrameClicked(bool)
{
}

//
void PanelTimeLineWidget::onEndFrameClicked(bool)
{
}

//
void PanelTimeLineWidget::onKeyFrameClicked(bool)
{
}

//
void PanelTimeLineWidget::onRemoveKeyFrameClicked(bool )
{
}

//
void PanelTimeLineWidget::onFilterClicked(bool)
{
}

//
void PanelTimeLineWidget::onAutoKeyChecked(bool checked)
{
}