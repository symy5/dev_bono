#include "main_manager.h"
#include "mainwindow.h"


#define SPEC_WORK_DIR_NAME	".temp"


MainManager::MainManager(MainWindow* pMainWindow)
{
	m_pMainWindow = pMainWindow;
	m_qDir = QDir::currentPath();

	/* [SPEC] スタートログ */
	m_pMainWindow->logout(QString("currentPath: %1").arg(m_qDir.absolutePath()));

	_init();
}


bool MainManager::_init()
{
	bool isResult;

	isResult = createDir(QObject::tr(SPEC_WORK_DIR_NAME));

	return isResult;
}


bool MainManager::_fin()
{
	bool isResult;

	isResult = deleteDir(QObject::tr(SPEC_WORK_DIR_NAME));

	return isResult;
}


bool MainManager::createDir(const QString& rqPathName)
{
	if (! m_qDir.mkdir(rqPathName))
	{
		m_pMainWindow->logout(QObject::tr("[ERROR] MainManager::createDir()"));
		return false;
	}

	return true;
}


bool MainManager::deleteDir(const QString& rqPathName)
{
	if (! m_qDir.rmdir(rqPathName))
	{
		m_pMainWindow->logout(QObject::tr("[ERROR] MainManager::deleteDir()"));
		return false;
	}

	return true;
}


bool MainManager::end()
{
	return _fin();
}


bool MainManager::start()
{
	return _init();
}
