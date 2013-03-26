#ifndef __VIEW_SPLITTER_H__
#define __VIEW_SPLITTER_H__

#include <QLinearGradient>
#include <QSplitter>
#include <QSplitterHandle>

#include <QPainter>
#include <QPaintEvent>

class Splitter : public QSplitter {
public:
	Splitter(Qt::Orientation orientation, QWidget *parent = 0)
			: QSplitter(orientation, parent) {
				setHandleWidth(7);
			}

	QSplitterHandle *createHandle() {
		return new SplitterHandle(orientation(), this);
	}




private:
	class SplitterHandle : public QSplitterHandle {
	public:
		QSplitter* m_parent;

		SplitterHandle(Qt::Orientation orientation, QSplitter *parent = 0)
				: QSplitterHandle(orientation, parent)
		{
			m_parent = parent;
		}

		void paintEvent(QPaintEvent *event) {
			QPainter painter(this);
			QLinearGradient gradient(0, 0, rect().width(), rect().height());

			if (orientation() == Qt::Horizontal) {
				gradient.setStart(rect().left(), rect().height()/2);
				gradient.setFinalStop(rect().right(), rect().height()/2);

				painter.fillRect(rect(), QBrush(gradient));

				painter.setPen(QColor(170, 170, 170));
				painter.drawLine(0, 0, 0, rect().bottom());
				painter.drawLine(6, 0, 6, rect().bottom());

			} else {

				gradient.setColorAt(0, QColor(250, 250, 250));
				gradient.setColorAt(1, QColor(190, 190, 190));

				gradient.setStart(rect().width()/2, rect().top());
				gradient.setFinalStop(rect().width()/2, rect().bottom());
				painter.fillRect(rect(), QBrush(gradient));

				painter.setPen(QColor(170, 170, 170));
				painter.drawLine(0, rect().top(), rect().width(), 0);
				painter.drawLine(0, rect().bottom(), rect().width(), rect().bottom());

			}
		}


		void SplitterHandle::mouseMoveEvent(QMouseEvent *e)
		{
			QSplitterHandle::mouseMoveEvent(e);
		}

		void SplitterHandle::mouseReleaseEvent(QMouseEvent *e)
		{
			QSplitterHandle::mouseReleaseEvent(e);
		}
	};
};

#endif /* __VIEW_SPLITTER_H__ */
