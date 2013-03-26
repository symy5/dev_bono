#ifndef __TREEWIDGETDRAGDROP_H__
#define __TREEWIDGETDRAGDROP_H__

#include <QTreeWidget>

class TreeWidgetDragDrop : public QTreeWidget
{
public:
	TreeWidgetDragDrop(QWidget* parent = 0, int nColumnCount = 1);

protected: /* override */
	virtual bool dropMimeData(QTreeWidgetItem *parent, int index, const QMimeData *data, Qt::DropAction action);    
	virtual QStringList mimeTypes() const;
	virtual Qt::DropActions supportedDropActions () const;
};

#endif /* __TREEWIDGETDRAGDROP_H__ */
