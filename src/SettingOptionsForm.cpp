#include "SettingOptionsForm.h"
#include "ui_SettingOptionsForm.h"
#include "ApplicationGlobal.h"
#include "EditProfilesDialog.h"

SettingOptionsForm::SettingOptionsForm(QWidget *parent)
	: AbstractSettingForm(parent)
	, ui(new Ui::SettingOptionsForm)
{
	ui->setupUi(this);
	
	QStringList list = global->appsettings.openai_gpt_models();
	ui->comboBox_openai_gpt_model->addItems(list);
}

SettingOptionsForm::~SettingOptionsForm()
{
	delete ui;
}

void SettingOptionsForm::exchange(bool save)
{
	if (save) {
		settings()->generate_commit_message_by_ai = ui->groupBox_generate_commit_message_by_ai->isChecked();
		settings()->openai_api_key = ui->lineEdit_openai_api_key->text();
		settings()->openai_gpt_model = ui->comboBox_openai_gpt_model->currentText();
	} else {
		ui->groupBox_generate_commit_message_by_ai->setChecked(settings()->generate_commit_message_by_ai);
		ui->lineEdit_openai_api_key->setText(settings()->openai_api_key);
		ui->comboBox_openai_gpt_model->setCurrentText(settings()->openai_gpt_model);
	}
}

void SettingOptionsForm::on_pushButton_edit_profiles_clicked()
{
	Git::User user = mainwindow()->currentGitUser();
	EditProfilesDialog dlg;
	dlg.loadXML(global->profiles_xml_path);
	dlg.enableDoubleClock(false);
	if (dlg.exec({user}) == QDialog::Accepted) {
		dlg.saveXML(global->profiles_xml_path);
	}
}

