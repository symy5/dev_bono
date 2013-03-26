#include <QtGui>
#include <QApplication>
//#include <QtOpenGL>

#include "mainwindow.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
#if 0
	if (!QGLFormat::hasOpenGL()) {
		qDebug("[ERROR]This system has no OpenGL support\n");
		return -1;
	}
#endif

	/* スタイル設定 */
	QApplication::setStyle("plastique");
	/* スタイルシート設定 */
	{
		QFile file("res/style.qss");
		file.open(QIODevice::ReadOnly);
		QTextStream in(&file); 
		QString qStyle = in.readAll();
		qApp->setStyleSheet(qStyle);
	}

#if 1
	MainWindow vMainWindow;
	MainWindow* pMainWindow = &vMainWindow;
	pMainWindow->init();
	pMainWindow->show();
#else
	ViewMain viewMain;
	viewMain.show();
#endif
	return app.exec();
}
