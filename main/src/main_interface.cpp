#include "main_interface.h"
#include "mainwindow.h"

MainInterface* MainInterface::_thisInterface = 0;


MainInterface::MainInterface()
{
	_pMainWindow = MainWindow::getInstance();
}


MainInterface* MainInterface::getInstance()
{
	if (_thisInterface == 0) {
		_thisInterface = new MainInterface();
	}

	return _thisInterface;
}


#if 0
FormScriptWindowImpl* MainInterface::getFormScriptWindowImpl()
{
	return _pMainWindow->m_pFormScriptWindowImpl;
}
#endif


PanelTimeLineWidget* MainInterface::getTimeLineWidget()
{
	return _pMainWindow->m_pTimeLineWidget;
}


void MainInterface::logout(const QString& rqStr)
{
	_pMainWindow->logout(rqStr);
}


void MainInterface::startGL()
{
	_pMainWindow->startGL();
}
