#pragma once
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsql.h>
#include <QtSql/qsqlquery.h>
#include <qvector.h>
#include <qmessagebox.h>
#include "Console.h"
class SqlQueriesManager
{
public:
	SqlQueriesManager();
	SqlQueriesManager(QSqlDatabase &db) : m_db(db) {}
	~SqlQueriesManager();
	void setDb(QSqlDatabase &db);
	QVector<Console*> getConsoles(QWidget *parent = nullptr);
	bool createConsole(QString consoleBrand, QString consoleName, QString problem, int idClient);
	bool createConsoleAndClient(QString consoleBrand, QString consoleName,QString problem, QString clientFirstName,
								QString clientName, QString clientPhone, QString clientEmail);

private: 
	QSqlDatabase m_db;
signals:
};

