#include "FixAndFlux.h"
#include <qmessagebox.h>

FixAndFlux::FixAndFlux(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	ui.actionDisconnect_from_database->setVisible(false);
	m_mainTabs = new MainTabs(this, m_db);
	ui.horizontalLayout->insertWidget(0, m_mainTabs);
	ui.actionAdd_a_console->setEnabled(false);
}

void FixAndFlux::on_actionConnect_to_database_triggered()
{
	if (!m_db.isOpen())
	{
		m_db = QSqlDatabase::addDatabase("QMYSQL");
		m_db.setHostName("127.0.0.1");
		m_db.setUserName("root");
		m_db.setPassword("");
		m_db.setDatabaseName("ConsoleDB");
		if (m_db.open()) {
			QMessageBox::information(this, "DB Connection", "Connected to the database!");
			ui.actionConnect_to_database->setVisible(false);
			ui.actionDisconnect_from_database->setVisible(true);

			m_mainTabs->displayConsoles(m_db);
			ui.actionAdd_a_console->setEnabled(true);
		}
		else {
			QMessageBox::information(this, "DB Connection", "Can't connect to the database!");
		}
	}
}

void FixAndFlux::on_actionDisconnect_from_database_triggered()
{
	if (m_db.isOpen())
	{
		m_db.close();
		if (!m_db.isOpen())
		{
			QMessageBox::information(this, "DB Disconnection", "DB Disconnected!");
			ui.actionDisconnect_from_database->setVisible(false);
			ui.actionConnect_to_database->setVisible(true);
			ui.actionAdd_a_console->setEnabled(false);
			m_mainTabs->cleanConsolesTab();
		}
	}
}

void FixAndFlux::on_actionAbout_triggered()
{
	QMessageBox::information(this, "About", "Software for video game console fixing management programmed by Bergnez");
}

void FixAndFlux::on_actionAdd_a_console_triggered()
{
	AddConsole* _addConsole = new AddConsole(this, m_db);
	_addConsole->exec();
}
