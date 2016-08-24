#include "qttestconceptmapdialog.h"

#include <QCloseEvent>
#include <QDebug>

ribi::cmap::QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent)
{

}

void ribi::cmap::QtDialog::closeEvent(QCloseEvent *)
{
  //From http://stackoverflow.com/a/29250691/3364162
  //event->setAccepted(!event->spontaneous());
  emit remove_me(this);
}
