#include "list_widget_drag_drop.h"
#include <QtGui>

ListWidgetDragDrop::ListWidgetDragDrop(QWidget* parent) : QListWidget(parent)
{
	// The tree can accept drops
	setAcceptDrops(true);
	// The tree supports dragging of its own items
	setDragEnabled(true);
}


bool ListWidgetDragDrop::dropMimeData(int index, const QMimeData *data, Qt::DropAction action)
{
	QList<QUrl> urlList;
	QListWidgetItem *item;
	QFileInfo info;
	QString fName;

	urlList = data->urls(); // retrieve list of urls

	foreach(QUrl url, urlList) // iterate over list
	{
#if 1
		fName = url.toLocalFile();
		info.setFile( fName );

		item = new QListWidgetItem(info.fileName());
		insertItem(index, item);
		++index; // increment index to preserve drop order
#else
		item = 0;
		if (parent == NULL) {
			item = new QListWidgetItem(this);
		}

		if (item != 0) {
			// set item text
			item->setText(url.toLocalFile() );
		}
#endif
	}

	return true;
}


QStringList ListWidgetDragDrop::mimeTypes() const
{
	QStringList qstrList;
	// list of accepted mime types for drop
	qstrList.push_back("text/uri-list");
	return qstrList;
}


void ListWidgetDragDrop::mouseMoveEvent(QMouseEvent *event)
{
	// if not left button - return
	if (!(event->buttons() & Qt::LeftButton)) return;
 
	// if no item selected, return (else it would crash)
	if (currentItem() == NULL) return;
 
	QDrag *drag = new QDrag(this);
	QMimeData *mimeData = new QMimeData;

	// construct list of QUrls
	// other widgets accept this mime type, we can drop to them
	QList<QUrl> list;
	list.push_back(QUrl(currentItem()->text())); // only QUrl in list will be text of actual item

	// mime stuff
	mimeData->setUrls(list); 
	drag->setMimeData(mimeData);

	// start drag
	drag->start(Qt::CopyAction | Qt::MoveAction);
}


Qt::DropActions ListWidgetDragDrop::supportedDropActions() const
{
	// returns what actions are supported when dropping
	return Qt::CopyAction | Qt::MoveAction;
}
