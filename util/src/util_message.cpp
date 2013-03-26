#include "util_message.h"

#include <QMessageBox>
#include <QString>


int UtilMessage_showWarningOk(const char* pMsg)
{
	QMessageBox::StandardButton reply;
	QString msg = QString(pMsg);

	reply = QMessageBox::warning( this, tr("warning"), msg, QMessageBox::Ok);
	if (reply == QMessageBox::Ok) {
		//...
	} else {
		//... }
	}

	return 0;
}
