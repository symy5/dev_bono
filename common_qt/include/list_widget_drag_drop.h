#ifndef __LIST_WIDGET_DRAG_DROP_H__
#define __LIST_WIDGET_DRAG_DROP_H__

#include <QListWidget>

class ListWidgetDragDrop : public QListWidget
{
public:
	ListWidgetDragDrop(QWidget* parent = 0);

protected: /* override */
	virtual bool dropMimeData(int index, const QMimeData *data, Qt::DropAction action);
	virtual QStringList mimeTypes() const;
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual Qt::DropActions supportedDropActions () const;
};

#endif /* __LIST_WIDGET_DRAG_DROP_H__ */
