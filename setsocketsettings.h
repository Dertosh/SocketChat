#ifndef SETSOCKETSETTINGS_H
#define SETSOCKETSETTINGS_H

#include <QDialog>

namespace Ui {
class setSocketSettings;
}

class SetSocketSettings : public QDialog {
  Q_OBJECT

 public:
  explicit SetSocketSettings(QWidget *parent = 0);
  ~SetSocketSettings();
  bool getDialogSolution();
 public slots:
  void setFalseSolution();
 signals:
  void closeApp();
  void getSettings(QString, quint16);

 private slots:

  void on_buttonBox_accepted();

 private:
  Ui::setSocketSettings *ui;
  bool _solution;
};

#endif  // SETSOCKETSETTINGS_H
