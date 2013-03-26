#ifndef __MAIN_MANAGER_H__
#define __MAIN_MANAGER_H__

#include <qdir.h>
#include <qstring.h>

class MainWindow;
class MainManager
{
public:
	MainManager(MainWindow* pMainWindow);
	bool createDir(const QString& rqPathName);
	bool deleteDir(const QString& rqPathName);
	bool end();
	bool start();

private:
	bool _init();
	bool _fin();

public:
	MainWindow* m_pMainWindow;
	QDir m_qDir;
};

#endif /* __MAIN_MANAGER_H__ */
