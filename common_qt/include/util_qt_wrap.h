#ifndef __UTIL_QT_WRAP_H__
#define __UTIL_QT_WRAP_H__

#include <qstringlist.h>
class QTreeWidget;

bool UtilQtWrap_QTreeWidget_addTopLevelItem(QTreeWidget* pTreeWidget, const QStringList& rqStringList, bool isOnlyOne);
bool UtilQtWrap_QTreeWidgetItem(QTreeWidget* pTreeWidget, const QStringList& rqStringList);
void UtilQtWrap_QTreeWidget_expandAll(QTreeWidget* pTreeWidget);

#endif /* __UTIL_QT_WRAP_H__ */
