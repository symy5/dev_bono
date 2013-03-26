#ifndef __UTIL_QT_H__
#define __UTIL_QT_H__

#include "FileType.h"
#include <qstring.h>
#include <QVariant>


/* [NOTE]
	オリジナルのポインタを QVariant へストア、逆に、QVariant から取得するテンプレートクラス
	以下を参考
	http://blog.bigpixel.ro/2010/04/23/storing-pointer-in-qvariant/
*/
template <class T> class UtilQtQVariantConvert
{
public:
	static T* asPtr(QVariant v)
	{
		return  (T *) v.value<void *>();
	}

	static QVariant asQVariant(T* ptr)
	{
		return qVariantFromValue((void *) ptr);
	}
};


class QWidget;

#if 0 /* NG */
const char* UtilQt_getCharString(const QString& qString);
#endif
const char* UtilQt_allocCharString(const QString& qString);
void UtilQt_freeCharString(const char* pBuf);
QString UtilQt_getFileName(const QString& rqFilePathName, bool isWithExt);
FileType UtilQt_getFileType(const QString& rqFileName);
bool UtilQt_saveFileWithDialog(QWidget* parent, const QString& rqCurrentDir, const QString& rqFileFilter, const QString& rqSaveText);

#endif /* __UTIL_QT_H__ */
