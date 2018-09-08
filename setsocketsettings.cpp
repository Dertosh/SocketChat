#include "setsocketsettings.h"
#include "ui_setsocketsettings.h"

SetSocketSettings::SetSocketSettings(QWidget *parent)
    : QDialog(parent), ui(new Ui::setSocketSettings) {
  ui->setupUi(this);
  ui->nicknameLineEdit->setText("Batman");
  ui->portLineEdit->setText("7010");

  QNetworkInterface::InterfaceFlags flags;

  foreach (QNetworkInterface interface, QNetworkInterface::allInterfaces()) {
    flags = interface.flags();
    if (flags.testFlag(QNetworkInterface::IsRunning) &&
        flags.testFlag(QNetworkInterface::IsUp) &&
        !flags.testFlag(QNetworkInterface::IsLoopBack) && interface.isValid() &&
        !flags.testFlag(QNetworkInterface::IsPointToPoint) &&
        (interface.type() != QNetworkInterface::Virtual))
      foreach (QNetworkAddressEntry entry, interface.addressEntries()) {
        if (interface.hardwareAddress() != "00:00:00:00:00:00" &&
            entry.ip().toString().contains(".")) {
          ui->interfaceComboBox->addItem(interface.humanReadableName());
          interfaceList.append(interface);
        }
      }
  }

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

QString SetSocketSettings::getNickname() {
  return ui->nicknameLineEdit->text();
}

quint16 SetSocketSettings::getPort() {
  return ui->portLineEdit->text().toLong();
}

QNetworkInterface SetSocketSettings::getInterface() {
  return interfaceList.takeAt(ui->interfaceComboBox->currentIndex());
}
