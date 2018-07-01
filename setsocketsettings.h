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

 private slots:

 private:
  Ui::setSocketSettings *ui;
  bool _solution;
};

#endif  // SETSOCKETSETTINGS_H
