#pragma once

#include <QWidget>
#include <qpushbutton.h>
#include "ui_MainTabs.h"
#include <QtSql/qsql.h>
#include <QtSql/qsqldatabase.h>
#include <QVector>
#include "Console.h"
#include "SqlQueriesManager.h"

class MainTabs : public QWidget
{
	Q_OBJECT

public:
	MainTabs(QWidget *parent = Q_NULLPTR);
	MainTabs(QWidget *parent = Q_NULLPTR, QSqlDatabase &db = QSqlDatabase());
	~MainTabs();

private:
	Ui::MainTabs ui;
	SqlQueriesManager m_sqlManager;

public slots:
	void displayConsoles(QSqlDatabase &db);
	void cleanLayout(QLayout* layout);
	void cleanConsolesTab();
};
