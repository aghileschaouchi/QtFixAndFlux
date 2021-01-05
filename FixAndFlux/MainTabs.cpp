#include "MainTabs.h"
#include <qdebug.h>

MainTabs::MainTabs(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

MainTabs::MainTabs(QWidget *parent, QSqlDatabase & db)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_sqlManager.setDb(db);
}

MainTabs::~MainTabs()
{
}

void MainTabs::displayConsoles(QSqlDatabase &db)
{
	if (db.isOpen())
	{
		QVector<Console*> consoles = m_sqlManager.getConsoles(this);
		QMutableVectorIterator<Console*> mIt(consoles);
		while(mIt.hasNext())
		{
			ui.verticalLayout_5->insertWidget(0, mIt.next());
		}
	}
}

void MainTabs::cleanLayout(QLayout* layout)
{
	for (int i = 0; i < layout->count(); ++i)
	{
		QWidget* _widget = layout->itemAt(i)->widget();
		_widget->close();
	}
}

void MainTabs::cleanConsolesTab()
{
	cleanLayout(ui.verticalLayout_5);
}

