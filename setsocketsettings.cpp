#include "setsocketsettings.h"
#include "ui_setsocketsettings.h"

SetSocketSettings::SetSocketSettings(QWidget *parent)
    : QDialog(parent), ui(new Ui::setSocketSettings) {
  ui->setupUi(this);
  ui->nicknameLineEdit->setText("Batman");
  ui->portLineEdit->setText("7010");
  connect(this, SIGNAL(rejected()), this, SLOT(setFalseSolution()));
  // connect(this, SLOT(reject()), this, SIGNAL(closeApp()));
}

SetSocketSettings::~SetSocketSettings() { delete ui; }
bool SetSocketSettings::getDialogSolution() { return _solution; }

void SetSocketSettings::setFalseSolution() { _solution = false; }

void SetSocketSettings::on_buttonBox_accepted() {
  emit getSettings(ui->nicknameLineEdit->text(),
                   ui->portLineEdit->text().toLong());
}
