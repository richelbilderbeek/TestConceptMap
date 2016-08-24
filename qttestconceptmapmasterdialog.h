#ifndef QTTESTCONCEPTMAPMASTERDIALOG_H
#define QTTESTCONCEPTMAPMASTERDIALOG_H

#include <QDialog>

namespace Ui { class QtMasterDialog; }

namespace ribi {
namespace cmap {

class QtMasterDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtMasterDialog(QWidget *parent = 0);
  ~QtMasterDialog();

private:
  Ui::QtMasterDialog *ui;

public slots:
  ///Add a new dialog. Each dialog will call this
  ///signal when they have created a new child dialog;
  ///a dialog they want to show modally
  void add_new(QDialog * const dialog);

  ///Remove an existing dialog. This signal is used
  ///by a dialog that wants to close
  void remove(QDialog * const dialog);
};

} //~namespace cmap
} //~namespace ribi

#endif // QTTESTCONCEPTMAPMASTERDIALOG_H
