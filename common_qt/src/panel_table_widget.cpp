#include "panel_table_widget.h"
#include <QtGui/QApplication>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QTableWidget>


PanelTableWidget::PanelTableWidget(QWidget* parent)
{
	_setupLayout(this);
}


PanelTableWidget::~PanelTableWidget()
{
}


void PanelTableWidget::_setupLayout(QWidget *Form)
{
	m_pVerticalLayoutForm = new QVBoxLayout(Form);

	/* name */
	m_pHorizontalLayoutName = new QHBoxLayout();
	m_pLabelName = new QLabel(Form);
	m_pLabelName->setText(QApplication::translate("Form", "name:", 0, QApplication::UnicodeUTF8));
	m_pLineEditName = new QLineEdit(Form);
	m_pLineEditName->setReadOnly(true);
	m_pHorizontalLayoutName->addWidget(m_pLabelName);
	m_pHorizontalLayoutName->addWidget(m_pLineEditName);

	/* Table */
	m_pTableWidget = new QTableWidget(Form);

	/* Form : Layout */
	m_pVerticalLayoutForm->addLayout(m_pHorizontalLayoutName);
#if 1
	m_pVerticalLayoutForm->addWidget(m_pTableWidget);
#else
	/* test */
	m_pTableWidgetTest = new QTableWidget(Form);
	m_pTableWidgetTest->setRowCount(1);
	m_pTableWidgetTest->setColumnCount(1);

	m_pTableWidgetTest->setCellWidget(0, 0, m_pTableWidget);
	m_pTableWidgetTest->resizeColumnToContents(0); 
	m_pTableWidgetTest->resizeRowToContents(0);
	m_pVerticalLayoutForm->addWidget(m_pTableWidgetTest);
#endif
}


void PanelTableWidget::setName(const QString& name)
{
	m_pLineEditName->setText(name);
}


void PanelTableWidget::setTable(const PanelTable_t* pPanelTable)
{
	if (pPanelTable == 0) {
		return;
	}

	int nHeaderCnt = pPanelTable->m_horizontalHeaderStrList.size();
	int nItemsStrCnt = pPanelTable->m_itemStrList.size();
	int nRowCnt = nItemsStrCnt / nHeaderCnt;
	int nColCnt = nHeaderCnt;

	/*
		set title
	 */

	m_pTableWidget->setRowCount(nRowCnt);
	m_pTableWidget->setColumnCount(nHeaderCnt);
	m_pTableWidget->setHorizontalHeaderLabels(pPanelTable->m_horizontalHeaderStrList);
	m_pTableWidget->setVerticalHeaderLabels(pPanelTable->m_verticalheaderStrList);

	QTableWidgetItem *pItem;
	for (int nRow = 0; nRow < nRowCnt; nRow++) {
		for (int nCol = 0; nCol < nColCnt; nCol++) {
			pItem = new QTableWidgetItem(pPanelTable->m_itemStrList[(nRow * nColCnt) + nCol]);
			m_pTableWidget->setItem(nRow, nCol, pItem);
		}
	}
}
