#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestconceptmapmenudialog.h"

#include <cassert>

#include <QTimer>

#include "qtaboutdialog.h"
#include "qtconceptmapviewtestsdialog.h"
#include "qttestconceptmapqtedgedialog.h"
#include "qttestconceptmapqtnodedialog.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qttesteditconceptmapdialog.h"
#include "conceptmapconceptfactory.h"
#include "testconceptmapmenudialog.h"

#include "testtimer.h"
#include "trace.h"
#include "ui_qttestconceptmapmenudialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestMenuDialog::QtTestMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestMenuDialog)
{
  ui->setupUi(this);

  //Show current screen I am most interested in
  #if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
  QTimer::singleShot(100,Qt::CoarseTimer,this,SLOT(on_button_edit_conceptmap_clicked()));
  #else
  QTimer::singleShot(100,this,SLOT(on_button_edit_conceptmap_clicked()));
  #endif
}

ribi::cmap::QtTestMenuDialog::~QtTestMenuDialog() noexcept
{
  delete ui;
}

void ribi::cmap::QtTestMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(TestConceptMapMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::cmap::QtTestMenuDialog::on_button_edit_conceptmap_clicked()
{
  QtTestEditConceptMapDialog d;
  d.setStyleSheet(this->styleSheet());
  //d.setWindowState(Qt::WindowFullScreen);
  this->ShowChild(&d);
}

void ribi::cmap::QtTestMenuDialog::on_button_view_conceptmaps_clicked()
{
  QtConceptMapViewTestsDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}



void ribi::cmap::QtTestMenuDialog::on_button_qtnode_clicked()
{
  QtTestQtNodeDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestMenuDialog::on_button_qtedge_clicked()
{
  //QtTestQtEdgeDialog d;
  //d.setStyleSheet(this->styleSheet());
  //this->ShowChild(&d);
}
