#include "AddConsole.h"
#include <qobject.h>
#include <qmessagebox.h>
#include <QtSql/qsql.h>
#include <QtSql/qsqldatabase.h>
#include <qdebug.h>

AddConsole::AddConsole(QWidget *parent, QSqlDatabase &db)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_sqlManager.setDb(db);

	ui.brandComboBox->addItem(QString("Sony"));
	ui.brandComboBox->addItem(QString("Microsoft"));
	ui.brandComboBox->addItem(QString("Nintendo"));
	ui.brandComboBox->addItem(QString("Neo geo"));
	ui.brandComboBox->addItem(QString("Sega"));

	ui.consoleNameComboBox->addItem(QString("Ps one"));
	ui.consoleNameComboBox->addItem(QString("Ps one slim"));
	ui.consoleNameComboBox->addItem(QString("Ps2 fat"));
	ui.consoleNameComboBox->addItem(QString("Ps2 slim"));
	ui.consoleNameComboBox->addItem(QString("Ps3 fat"));
	ui.consoleNameComboBox->addItem(QString("Ps3 slim"));
	ui.consoleNameComboBox->addItem(QString("Ps3 ultra slim"));
	ui.consoleNameComboBox->addItem(QString("Ps4 fat"));
	ui.consoleNameComboBox->addItem(QString("Ps4 slim"));
	ui.consoleNameComboBox->addItem(QString("Ps4 pro"));
	ui.consoleNameComboBox->addItem(QString("Psp"));
	ui.consoleNameComboBox->addItem(QString("Ps vita"));
	ui.consoleNameComboBox->addItem(QString("Xbox"));
	ui.consoleNameComboBox->addItem(QString("Xbox 360 fat"));
	ui.consoleNameComboBox->addItem(QString("Xbox 360 slim"));
	ui.consoleNameComboBox->addItem(QString("Xbox One"));
	ui.consoleNameComboBox->addItem(QString("Xbox One S"));
	ui.consoleNameComboBox->addItem(QString("Xbox One X"));
	ui.consoleNameComboBox->addItem(QString("Xbox Series X"));
	ui.consoleNameComboBox->addItem(QString("Nes"));
	ui.consoleNameComboBox->addItem(QString("SNes"));
	ui.consoleNameComboBox->addItem(QString("Nintendo 64"));
	ui.consoleNameComboBox->addItem(QString("Gamecube"));
	ui.consoleNameComboBox->addItem(QString("Wii"));
	ui.consoleNameComboBox->addItem(QString("Wii U"));
	ui.consoleNameComboBox->addItem(QString("Switch"));
	ui.consoleNameComboBox->addItem(QString("Switch light"));
	ui.consoleNameComboBox->addItem(QString("Gameboy classic"));
	ui.consoleNameComboBox->addItem(QString("Gameboy pocket"));
	ui.consoleNameComboBox->addItem(QString("Gameboy light"));
	ui.consoleNameComboBox->addItem(QString("Gameboy color"));
	ui.consoleNameComboBox->addItem(QString("Gameboy advance"));
	ui.consoleNameComboBox->addItem(QString("Gameboy advance sp"));
	ui.consoleNameComboBox->addItem(QString("Gameboy micro"));
	ui.consoleNameComboBox->addItem(QString("Ds"));
	ui.consoleNameComboBox->addItem(QString("Ds light"));
	ui.consoleNameComboBox->addItem(QString("Dsi"));
	ui.consoleNameComboBox->addItem(QString("Dsi XL"));
	ui.consoleNameComboBox->addItem(QString("2DS"));
	ui.consoleNameComboBox->addItem(QString("2DS XL"));
	ui.consoleNameComboBox->addItem(QString("3DS"));
	ui.consoleNameComboBox->addItem(QString("3DS XL"));

	//for tests purposes
	ui.clientComboBox->addItem(QString("0"));

	ui.clientComboBox->setVisible(false);
	modifyLayoutsWidgetsVisibility(ui.newClientVerticalLayout, false);
	ui.createConsoleButton->setDisabled(true);
	connect(ui.existingClientCheckBox, SIGNAL(clicked(bool)), this, SLOT(onExisting_client_check_box_checked()));
	connect(ui.newClientCheckBox, SIGNAL(clicked(bool)), this, SLOT(onNew_client_check_box_checked()));
	connect(ui.newClientCheckBox, SIGNAL(clicked()), this, SLOT(onNew_client_check_box_unchecked()));

	connect(ui.brandComboBox, SIGNAL(textChanged()), this, SLOT(ungreyConsoleDialog()));
	connect(ui.consoleNameComboBox, SIGNAL(textChanged()), this, SLOT(ungreyConsoleDialog()));
	connect(ui.consoleProblemText, SIGNAL(textChanged()), this, SLOT(ungreyConsoleDialog()));
	connect(ui.clientComboBox, SIGNAL(textChanged()), this, SLOT(ungreyConsoleDialog()));
	connect(ui.firstNameLine, SIGNAL(textChanged()), this, SLOT(ungreyConsoleDialog()));
	connect(ui.nameLine, SIGNAL(textChanged()), this, SLOT(ungreyConsoleDialog()));
	connect(ui.phoneLine, SIGNAL(textChanged()), this, SLOT(ungreyConsoleDialog()));
	connect(ui.emailLine, SIGNAL(textChanged()), this, SLOT(ungreyConsoleDialog()));

	connect(ui.cancelButton, SIGNAL(clicked(bool)), this, SLOT(onCancel_button_clicked()));
	connect(ui.createConsoleButton, SIGNAL(clicked(bool)), this, SLOT(on_Create_console_button_clicked()));

	//connect(m_sqlManager, SIGNAL(newConsoleCreated()), this, SLOT(onNew_console_created()));
}

AddConsole::~AddConsole()
{
}

void AddConsole::modifyLayoutsWidgetsVisibility(QLayout* layout, bool visible)
{
	for (int i = 0; i < layout->count(); ++i)
	{
		QLayout* _layout = layout->itemAt(i)->layout();
		if (_layout != nullptr) {
			for (int j = 0; j < _layout->count(); j++)
			{
				QWidget* _widget = _layout->itemAt(j)->widget();
				if (_widget != nullptr) {
					_widget->setVisible(visible);
				}
			}
		}
	}
}

void AddConsole::onExisting_client_check_box_checked()
{
	ui.clientComboBox->setVisible(true);
	modifyLayoutsWidgetsVisibility(ui.newClientVerticalLayout, false);
	ui.newClientCheckBox->setChecked(false);
}

void AddConsole::onNew_client_check_box_unchecked()
{
	ui.createConsoleButton->setEnabled(false);
}

void AddConsole::onNew_client_check_box_checked()
{
	modifyLayoutsWidgetsVisibility(ui.newClientVerticalLayout, true);
	ui.clientComboBox->setVisible(false);
	ui.existingClientCheckBox->setChecked(false);
}

void AddConsole::ungreyConsoleDialog()
{
	bool ok(false);
	if (ui.newClientCheckBox->isChecked())
	{
		ok = !ui.consoleProblemText->document()->isEmpty()
			&& !ui.firstNameLine->text().isEmpty()
			&& !ui.nameLine->text().isEmpty()
			&& !ui.phone->text().isEmpty()
			&& !ui.email->text().isEmpty();
	}
	if (ui.existingClientCheckBox->isChecked())
	{
		ok = !ui.consoleProblemText->document()->isEmpty();
	}
	ui.createConsoleButton->setEnabled(ok);
}

void AddConsole::on_Create_console_button_clicked()
{
	qDebug() << "on_Create_console_button_clicked called";
	if (!ui.consoleProblemText->document()->isEmpty()) {
		if (ui.existingClientCheckBox->isChecked())
		{
			createConsole(ui.brandComboBox->currentText(), ui.consoleNameComboBox->currentText(),
				ui.consoleProblemText->toPlainText(), ui.clientComboBox->currentText().toInt());
			close();
		}
			
		else if ((ui.newClientCheckBox->isChecked() &&
			(!ui.firstNameLine->text().isEmpty()) &&
				!ui.nameLine->text().isEmpty() &&
				!ui.phoneLine->text().isEmpty() &&
				!ui.emailLine->text().isEmpty())) {
			createConsoleAndClient(ui.brandComboBox->currentText(), ui.consoleNameComboBox->currentText(), 
				ui.consoleProblemText->toPlainText(), ui.firstNameLine->text(), ui.nameLine->text(), 
				ui.phoneLine->text(), ui.emailLine->text());
			close();

		} else {
			QMessageBox::warning(this, "Not enough information", "Fill all the informations!");
		}
	} else {
		QMessageBox::warning(this, "Not enough information", "Fill all the informations!");
	}
}

void AddConsole::onCancel_button_clicked()
{
	close();
}

void AddConsole::createConsole(QString consoleBrand, QString consoleName, QString problem, int idClient)
{
	bool result = m_sqlManager.createConsole(consoleBrand, consoleName, problem, idClient);
	if (!result)
	{
		QMessageBox::warning(this, "Insertion error", "An error occured while inserting a console!");
	}
}

void AddConsole::createConsoleAndClient(QString consoleBrand, QString consoleName, QString problem, 
	QString clientFirstName, QString clientName, QString clientPhone, QString clientEmail)
{
	bool result = m_sqlManager.createConsoleAndClient(consoleBrand, consoleName, problem, clientFirstName,
		clientName, clientPhone, clientEmail);
	if (!result)
	{
		QMessageBox::warning(this, "Insertion error", "An error occured while inserting a console!");
	}
}
