#include "qttestconceptmapmasterdialog.h"
#include <cassert>
#include <QCloseEvent>
#include <QDebug>
#include <QKeyEvent>
//#include "qtbrainweaverdialog.h"
#include "ui_qttestconceptmapmasterdialog.h"

ribi::cmap::QtMasterDialog::QtMasterDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtMasterDialog)
{
  ui->setupUi(this);
  assert(ui->stackedWidget->count() == 0);
}

ribi::cmap::QtMasterDialog::~QtMasterDialog()
{
  delete ui;
}

void ribi::cmap::QtMasterDialog::add_new(QDialog * const dialog)
{
  const int new_index = ui->stackedWidget->addWidget(dialog);
  ui->stackedWidget->setCurrentIndex(new_index);

  //Update
  this->setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());

  QObject::connect(
    ui->stackedWidget->currentWidget(),
    SIGNAL(add_me(QDialog*const)),
    this,
    SLOT(add_new(QDialog*const))
  );
  QObject::connect(dialog, SIGNAL(remove_me(QDialog*const)), this, SLOT(remove(QDialog*const)));
}


void ribi::cmap::QtMasterDialog::remove(QDialog * const dialog)
{
  ui->stackedWidget->removeWidget(dialog);
  delete dialog;

  const int new_index = ui->stackedWidget->count() - 1;

  if (new_index < 0) { close(); return; }

  ui->stackedWidget->setCurrentIndex(new_index);

  //Update
  this->setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());

}
