#pragma once

#include <QWidget>
#include "ui_Console.h"

class Console : public QWidget
{
	Q_OBJECT

public:
	Console(QWidget *parent = Q_NULLPTR);
	Console(QWidget *parent = Q_NULLPTR, int clientId = 0, int consoleId = 0, QString consoleName = "", bool fixed = false, QString problem = "");
	Console(QWidget *parent = Q_NULLPTR, int clientId = 0, QString clientFirstName = "", QString clientName = "", QString clientPhone = "", 
		QString clientEmail = "", int consoleId = 0, QString consoleName = "", bool fixed = false, QString problem = "");
	~Console();
	int Console::clientId() { return m_clientId; }
	QString Console::clientFirstName() { return m_clientFirstName; }
	QString Console::clientName() { return m_clientName; }
	QString Console::clientPhone() { return m_clientPhone; }
	QString Console::clientEmail() { return m_clientEmail; }
	int Console::consoleId() { return m_consoleId; }
	QString Console::consoleName() { return m_consoleName; }
	bool Console::isFixed() { return m_fixed; }
	QString Console::problem() { return m_problem; }

private:
	Ui::Console ui;
	int m_clientId;
	QString m_clientFirstName;
	QString m_clientName;
	QString m_clientPhone;
	QString m_clientEmail;
	int m_consoleId;
	QString m_consoleName;
	bool m_fixed;
	QString m_problem;
};
