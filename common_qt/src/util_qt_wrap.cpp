#include "util_qt_wrap.h"
#include <QtGui>


static bool _isFoundInQTreeWidget(QTreeWidget* pTreeWidget, const QStringList& rqStringList)
{
	bool isFound = false;
	int nCnt = rqStringList.count();
	for (int i = 0; i < nCnt; i++) {
		const QString& rqStr = rqStringList[i];
		QList<QTreeWidgetItem *> qList = pTreeWidget->findItems(rqStr, Qt::MatchExactly);
		if (qList.count() > 0) {
			isFound = true;
			break;
		}
	}

	return isFound;
}


/* 重複がある場合は登録しない */
bool UtilQtWrap_QTreeWidget_addTopLevelItem(QTreeWidget* pTreeWidget, const QStringList& rqStringList, bool isOnlyOne)
{
	if (pTreeWidget == 0) {
		return false;
	}

	if (isOnlyOne) {
		/* 既にトップアイテムが登録されている場合は登録しない。*/
		int nCnt = pTreeWidget->topLevelItemCount();
		if (nCnt > 0) {
			return false;
		}
	}

	bool isFound = _isFoundInQTreeWidget(pTreeWidget, rqStringList);
	if (isFound == true) {
		return false;
	}

	/* 登録 */
	QTreeWidgetItem* pqItem = new QTreeWidgetItem(rqStringList);
	pTreeWidget->addTopLevelItem(pqItem);

	return true;
}


/* 重複がある場合は登録しない */
bool UtilQtWrap_QTreeWidgetItem(QTreeWidget* pTreeWidget, const QStringList& rqStringList)
{
	if (pTreeWidget == 0) {
		return false;
	}

	bool isFound = _isFoundInQTreeWidget(pTreeWidget, rqStringList);
	if (isFound == true) {
		return false;
	}

	/* 登録 */
	QTreeWidgetItem* pqTopItem = pTreeWidget->topLevelItem(0);
	QTreeWidgetItem* pqSubItem = new QTreeWidgetItem(pqTopItem, rqStringList);

	return true;
}


static void _expandAllTreeItem(QTreeWidgetItem* item)
{
	item->setExpanded(true);
	int nCnt = item->childCount();
	for (int i = 0; i < nCnt; i++) {
		QTreeWidgetItem* itemChild = item->child(i);
		_expandAllTreeItem(itemChild);
	}
}


void UtilQtWrap_QTreeWidget_expandAll(QTreeWidget* pTreeWidget)
{
	int nCnt = pTreeWidget->topLevelItemCount();

	for (int i = 0; i < nCnt; i++) {
		QTreeWidgetItem* itemTop = pTreeWidget->topLevelItem(i);		
		_expandAllTreeItem(itemTop);
	}
}
