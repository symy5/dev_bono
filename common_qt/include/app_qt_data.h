#ifndef __APPQTDATA_H__
#define __APPQTDATA_H__

#include <Qt>
#include <QString>

class AppQtData
{
public:
	static const Qt::DockWidgetAreas AreaDefaultTool;
	static const Qt::DockWidgetAreas AreaDefaultWindow;
	static const Qt::DockWidgetAreas AreaDefaultLandscape;
	static const QString qDefaultFileFilter; /* Save As 用 ファイルフィルター */
};

#endif /* __APPQTDATA_H__ */
