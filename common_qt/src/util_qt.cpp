#include "util_qt.h"
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>


const char* UtilQt_allocCharString(const QString& qString)
{
	if (qString.length() <= 0) {
		return 0;
	}

	QByteArray qByteStr = qString.toLocal8Bit();
	int nSize = qByteStr.length();
	if (nSize <= 0) {
		return 0;
	}

	/* [NOTE] QByteArray の length() は、'\0' が考慮されていないので、+1 する */
	char* pBuf = (char*)malloc(sizeof(char) * (nSize + 1));
	const char* pStr = qByteStr.constData();
	strncpy(pBuf, pStr, nSize);
	pBuf[nSize] = '\0';

	return(pBuf); 
}


void UtilQt_freeCharString(const char* pBuf)
{
	if (pBuf != 0) {
		free((void*)pBuf);
	}
}

#if 0 /* NG */
const char* UtilQt_getCharString(const QString& qString)
{
	if (qString.length() <= 0) {
		return 0;
	}
	//return (qString.toUtf8().data());
	return (qString.toLocal8Bit().data());
#if 0
	static QByteArray qByteStr = qString.toLocal8Bit();
	if (qByteStr.length() <= 0) {
		return 0;
	}

	return(qByteStr.constData()); 
#endif
}
#endif

QString UtilQt_getFileName(const QString& rqFilePathName, bool isWithExt)
{
	if (rqFilePathName == NULL || rqFilePathName.length() <= 0) {
		return QString("");
	}

	QFileInfo fileInfo(rqFilePathName);
	QString name;
	
	if (isWithExt) {
		/* 拡張子付き */
		name = fileInfo.fileName();
	} else {
		/* 拡張子なし */
		name = fileInfo.baseName();
	}

	return name;

}


FileType UtilQt_getFileType(const QString& rqFileName)
{
	if (rqFileName.length() <= 0) {
		return FileType_UNKNOWN;
	}

	QFileInfo fileInfo(rqFileName);
	QString qExtName = fileInfo.suffix();
	if (qExtName.compare("bac", Qt::CaseInsensitive) == 0) {
		return FileType_BAC;
	} else if (qExtName.compare("mcm", Qt::CaseInsensitive) == 0) {
		return FileType_MCM;
	} else if (qExtName.compare("mca", Qt::CaseInsensitive) == 0) {
		return FileType_MCA;
	} else if (qExtName.compare("mct", Qt::CaseInsensitive) == 0) {
		return FileType_MCT;
	} else if (qExtName.compare("tra", Qt::CaseInsensitive) == 0) {
		return FileType_TRA;
	} else if (qExtName.compare("mbac", Qt::CaseInsensitive) == 0) {
		return FileType_MBAC;
	} else if (qExtName.compare("mtra", Qt::CaseInsensitive) == 0) {
		return FileType_MTRA;
	} else if (qExtName.compare("bmp", Qt::CaseInsensitive) == 0) {
		return FileType_BMP;
	} else {
		return FileType_UNKNOWN;
	}
}

#if 0
/* tr(".bac")
http://www.kde.gr.jp/~ichi/qt-2.3.2/qstring.html#28dcfd
 */
QString UtilQt_getFileName(const QString& rqFilePathName, const QString& rqExt,  bool isWithExt)
{
	if (rqFilePathName == NULL || rqFilePathName.length() <= 0) {
		return QString("");
	}

	/* 拡張子にて判断、後ろから検索(大文字/小文字区別なし) */
	int nPosExt = rqFilePathName->find (rqExt, -1, false);
	if (nPosExt == -1) {
		/* Not Found */
		return QString("");
	}

	/* 拡張子にて判断、後ろから検索(大文字/小文字区別なし) */
	int nRet = rqFilePathName->find (rqExt, -1, false);
	if (nRet == -1) {
		/* Not Found */
		return QString("");
	}

}
#endif


bool UtilQt_saveFileWithDialog(QWidget* parent, const QString& rqCurrentDir, const QString& rqFileFilter, const QString& rqSaveText)
{
	QString qFileName = QFileDialog::getSaveFileName(parent, QObject::tr("Save file."), rqCurrentDir/*QDir::homePath()*/, rqFileFilter);
	if (qFileName.isEmpty()) {
		/* nothing to do. */
		return true;
	}

	QFile qFile(qFileName);
	if (!qFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		// ファイルのオープン
		QMessageBox::warning(parent, QObject::tr("Application"), QObject::tr("Cannot open file %1:\n%2.").arg(qFileName).arg(qFile.errorString()));
		return false;
	}
	QTextStream outputFile(&qFile); // ストリームに接続
	outputFile << rqSaveText; // 書き込み
	qFile.close();

	return true;
}
