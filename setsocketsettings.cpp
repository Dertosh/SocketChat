#include "setsocketsettings.h"
#include "ui_setsocketsettings.h"

SetSocketSettings::SetSocketSettings(QWidget *parent)
    : QDialog(parent), ui(new Ui::setSocketSettings) {
  ui->setupUi(this);
  connect(this, SIGNAL(rejected()), this, SLOT(setFalseSolution()));
  // connect(this, SLOT(reject()), this, SIGNAL(closeApp()));
}

SetSocketSettings::~SetSocketSettings() { delete ui; }
bool SetSocketSettings::getDialogSolution() { return _solution; }

void SetSocketSettings::setFalseSolution() { _solution = false; }
