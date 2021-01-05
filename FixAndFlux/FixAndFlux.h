#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FixAndFlux.h"
#include <QtSql/qsql.h>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlerror.h>
#include "MainTabs.h"
#include "AddConsole.h"

class FixAndFlux : public QMainWindow
{
    Q_OBJECT

public:
    FixAndFlux(QWidget *parent = Q_NULLPTR);

private:
	MainTabs *m_mainTabs;
    Ui::FixAndFluxClass ui;
	QSqlDatabase m_db;

private slots:
	void on_actionConnect_to_database_triggered();
	void on_actionDisconnect_from_database_triggered();
	void on_actionAbout_triggered();
	void on_actionAdd_a_console_triggered();
};
