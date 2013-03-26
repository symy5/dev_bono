#include "tree_widget_drag_drop.h"
#include <QtGui>


TreeWidgetDragDrop::TreeWidgetDragDrop(QWidget* parent, int nColumnCount) : QTreeWidget(parent)
{
	setColumnCount(nColumnCount);
	// The tree can accept drops
	setAcceptDrops(true);
	// The tree supports dragging of its own items
	setDragEnabled(true);
}


bool TreeWidgetDragDrop::dropMimeData(QTreeWidgetItem *parent, int index, const QMimeData *data, Qt::DropAction action)
{
	QList<QUrl> urlList;
	QTreeWidgetItem *item;

	urlList = data->urls(); // retrieve list of urls

	foreach(QUrl url, urlList) // iterate over list
	{
		// make new QTreeWidgetItem and set its text
		// if parent is null - add top level item (this parent)
		if (parent == NULL) {
			item = new QTreeWidgetItem(this);
		} else {
			// else add QTreeWidgetItem with parent and expand parent
			item = new QTreeWidgetItem(parent);
			parent->setExpanded( true );
		}

		// set item text
		item->setText( 0, url.toLocalFile() );
	}

	return true;
}


QStringList TreeWidgetDragDrop::mimeTypes() const
{
	QStringList qstrList;
	// list of accepted mime types for drop
	qstrList.push_back("text/uri-list");
	return qstrList;
}


Qt::DropActions TreeWidgetDragDrop::supportedDropActions() const
{
	// returns what actions are supported when dropping
	return Qt::CopyAction | Qt::MoveAction;
}


#if 0
void TreeWidgetDragDrop::dragEnterEvent(QDragEnterEvent *e)
{
	e->accept();
}


void TreeWidgetDragDrop::dragMoveEvent(QDragMoveEvent *e)
{
	e->accept();
}
#endif


