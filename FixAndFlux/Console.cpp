#include "Console.h"

Console::Console(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Console::Console(QWidget * parent, int clientId, int consoleId, QString consoleName, bool fixed, QString problem)
	: QWidget(parent)
{
	m_clientId = clientId; m_consoleId = consoleId; m_consoleName = consoleName; m_fixed = fixed; m_problem = problem;
	ui.setupUi(this);
	ui.clientId->setText(QString::number(m_clientId));
	ui.consoleId->setText(QString::number(m_consoleId));
	ui.consoleName->setText(m_consoleName);
	QString _fixed;
	(m_fixed) ? _fixed = QString("Fixed") : _fixed = QString("Not fixed");
	ui.fixed->setText(_fixed);
	ui.problem->setText(m_problem);
}

Console::Console(QWidget * parent, int clientId, QString clientFirstName, QString clientName, QString clientPhone,
	QString clientEmail, int consoleId, QString consoleName, bool fixed, QString problem) 
	: QWidget(parent)
{
	m_clientId = clientId; m_consoleId = consoleId; m_consoleName = consoleName; m_fixed = fixed; m_problem = problem;
	m_clientFirstName = clientFirstName;
	m_clientName = clientName;
	m_clientPhone = clientPhone;
	m_clientEmail = clientEmail;

	ui.setupUi(this);
	ui.clientId->setText(QString::number(m_clientId));
	ui.consoleId->setText(QString::number(m_consoleId));
	ui.consoleName->setText(m_consoleName);
	QString _fixed;
	(m_fixed) ? _fixed = QString("Fixed") : _fixed = QString("Not fixed");
	ui.fixed->setText(_fixed);
	ui.problem->setText(m_problem);
	ui.clientFirstName->setText(m_clientFirstName);
	ui.clientName->setText(m_clientName);
	ui.clientPhone->setText(m_clientPhone);
	ui.clientEmail->setText(m_clientEmail);
}

Console::~Console()
{
}
