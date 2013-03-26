#ifndef __PANEL_TABLE_WIDGET_H__
#define __PANEL_TABLE_WIDGET_H__

#include <QWidget>

class QLabel;
class QLineEdit;
class QHBoxLayout;
class QVBoxLayout;
class QTextEdit;
class QTableWidget;
class QStringList;

struct PanelTable_t
{
	QStringList m_horizontalHeaderStrList;
	QStringList m_verticalheaderStrList;
	QStringList m_itemStrList;
};


class PanelTableWidget : public QWidget
{
public:
	PanelTableWidget(QWidget* parent);
	~PanelTableWidget();
	void setName(const QString& name);
	void setTable(const PanelTable_t* pPanelTable);

private:
	void _setupLayout(QWidget *Form);

public:
	QLabel *m_pLabelName;
	QLineEdit *m_pLineEditName;
	QTableWidget *m_pTableWidget;
	QTableWidget *m_pTableWidgetTest;
	QHBoxLayout *m_pHorizontalLayoutName;
	QVBoxLayout *m_pVerticalLayoutForm;
};

#endif /* __PANEL_TABLE_WIDGET_H__ */
