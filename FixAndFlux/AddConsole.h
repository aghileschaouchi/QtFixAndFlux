#pragma once

#include <QDialog>
#include "ui_AddConsole.h"
#include "SqlQueriesManager.h"

class AddConsole : public QDialog
{
	Q_OBJECT

public:
	AddConsole(QWidget *parent = Q_NULLPTR, QSqlDatabase &db = QSqlDatabase());
	~AddConsole();

private:
	Ui::AddConsole ui;
	SqlQueriesManager m_sqlManager;

private slots:
	void modifyLayoutsWidgetsVisibility(QLayout* layout, bool visible);
	void onExisting_client_check_box_checked();
	void onNew_client_check_box_unchecked();
	void onNew_client_check_box_checked();
	void ungreyConsoleDialog();
	void on_Create_console_button_clicked();
	void onCancel_button_clicked();
	void createConsole(QString consoleBrand, QString consoleName, QString problem, int idClient);
	void createConsoleAndClient(QString consoleBrand, QString consoleName, QString problem, QString clientFirstName,
		QString clientName, QString clientPhone, QString clientEmail);
};
