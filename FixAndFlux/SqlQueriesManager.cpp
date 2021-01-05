#include "SqlQueriesManager.h"
#include <qdebug.h>

SqlQueriesManager::SqlQueriesManager()
{
}

SqlQueriesManager::~SqlQueriesManager()
{
}

void SqlQueriesManager::setDb(QSqlDatabase & db)
{
	m_db = db;
}

QVector<Console*> SqlQueriesManager::getConsoles(QWidget *parent)
{
	QVector<Console*> consoles;
	QSqlQuery query(m_db);
	if (query.exec("SELECT ConsoleId, ConsoleName, Problem, Fixed, ClientId FROM console"))
	{
		while (query.next())
		{
			int _consoleId = query.value(0).toInt();
			QString _consoleName = query.value(1).toString();
			QString _problem = query.value(2).toString();
			bool _fixed = query.value(3).toBool();
			int _clientId = query.value(4).toInt();

			QSqlQuery clientQuery(m_db);
			clientQuery.exec("SELECT ClientName, ClientFirstName, Phone, Email FROM client WHERE ClientId = 1");
			clientQuery.first();
			QString _clientName = clientQuery.value(0).toString();
			QString _clientFirstName = clientQuery.value(1).toString();
			QString _clientPhone = clientQuery.value(2).toString();
			QString _clientEmail = clientQuery.value(3).toString();
			qDebug() << "clientName: " << _clientName;
			qDebug() << "clientFirstName: " << _clientFirstName;
			qDebug() << "clientPhone: " << _clientPhone;
			qDebug() << "clientEmail: " << _clientEmail;
			Console* _console = new Console(parent, _clientId, _clientFirstName, _clientName, _clientPhone,
				_clientEmail, _consoleId, _consoleName, _fixed, _problem);
			_console->setAttribute(Qt::WA_DeleteOnClose, true);
			consoles.push_back(_console);
		}
	}
	else
	{
		QMessageBox::information(nullptr, "ERROR", "ERROR");
	}
	return consoles;
}

bool SqlQueriesManager::createConsole(QString consoleBrand, QString consoleName, QString problem, int idClient)
{
	bool result(false);
	QSqlQuery query(m_db);
	query.prepare("INSERT INTO console (ConsoleName, Problem, Fixed, ClientId) "
					"VALUES (?, ?, ?, ?)");
	query.addBindValue(consoleName);
	query.addBindValue(problem);
	query.addBindValue(false);
	query.addBindValue(idClient);
	return query.exec();
}

bool SqlQueriesManager::createConsoleAndClient(QString consoleBrand, QString consoleName, 
	QString problem, QString clientFirstName, QString clientName, QString clientPhone, QString clientEmail)
{
	QSqlQuery clientQuery(m_db);
	clientQuery.prepare("INSERT INTO client (ClientName, ClientFirstName, Phone, Email) "
		"VALUES (?, ?, ?, ?)");
	clientQuery.addBindValue(clientName);
	clientQuery.addBindValue(clientFirstName);
	clientQuery.addBindValue(clientPhone);
	clientQuery.addBindValue(clientEmail);
	if (clientQuery.exec())
	{
		QSqlQuery query(m_db);
		query.prepare("INSERT INTO console (ConsoleName, Problem, Fixed, ClientId) "
			"VALUES (?, ?, ?, ?)");
		query.addBindValue(consoleName);
		query.addBindValue(problem);
		query.addBindValue(false);
		query.addBindValue(clientQuery.lastInsertId());
		return query.exec();
	}
	return false;
}
