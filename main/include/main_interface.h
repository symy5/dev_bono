#ifndef __MAIN_INTERFACE_H__
#define __MAIN_INTERFACE_H__

#include <qstring.h>
//class FormScriptWindowImpl;
class MainManager;
class MainWindow;
class PanelTimeLineWidget;

class MainInterface
{
private:
	MainInterface();

public:
	~MainInterface();
	static MainInterface* getInstance();
	MainManager* getMainManager();
//	FormScriptWindowImpl* getFormScriptWindowImpl();
	PanelTimeLineWidget* getTimeLineWidget();
	void logout(const QString& rqStr);
	void startGL();
	void setSaveSetting(bool isSave);

private:
	static MainInterface* _thisInterface;
	MainWindow* _pMainWindow;
};

#endif /* __MAIN_INTERFACE_H__ */
