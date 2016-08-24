#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestconceptmapmenudialog.h"

#include <cassert>

#include <QTimer>

#include "conceptmapconceptfactory.h"
#include "fileio.h"
#include "qtaboutdialog.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmapviewtestsdialog.h"
#include "qttestconceptmapqtedgedialog.h"
#include "qttestconceptmapqtnodedialog.h"
#include "qttesteditconceptmapdialog.h"
#include "testconceptmapmenudialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestconceptmapmenudialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestMenuDialog::QtTestMenuDialog(QWidget *parent) :
    QtDialog(parent),
    ui(new Ui::QtTestMenuDialog)
{
  ui->setupUi(this);

  //Show current screen I am most interested in
  /*
  #if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
  QTimer::singleShot(100,Qt::CoarseTimer,this,SLOT(on_button_edit_conceptmap_clicked()));
  #else
  QTimer::singleShot(100,this,SLOT(on_button_edit_conceptmap_clicked()));
  #endif
  */
}

ribi::cmap::QtTestMenuDialog::~QtTestMenuDialog() noexcept
{
  delete ui;
}

void ribi::cmap::QtTestMenuDialog::on_button_about_clicked()
{
  QtAboutDialog * const d{
    new QtAboutDialog(TestConceptMapMenuDialog().GetAbout())
  };
  emit add_me(d);
}

void ribi::cmap::QtTestMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::cmap::QtTestMenuDialog::on_button_edit_conceptmap_clicked()
{
  QtTestEditConceptMapDialog * const d{
    new QtTestEditConceptMapDialog
  };
  d->setStyleSheet(this->styleSheet());
  //d.setWindowState(Qt::WindowFullScreen);
  emit add_me(d);
}

void ribi::cmap::QtTestMenuDialog::on_button_view_conceptmaps_clicked()
{
  QtConceptMapViewTestsDialog * const d{
    new QtConceptMapViewTestsDialog
  };
  d->setStyleSheet(this->styleSheet());
  emit add_me(d);
}



void ribi::cmap::QtTestMenuDialog::on_button_qtnode_clicked()
{
  QtTestQtNodeDialog * const d{
    new QtTestQtNodeDialog
  };
  d->setStyleSheet(this->styleSheet());
  emit add_me(d);
}

void ribi::cmap::QtTestMenuDialog::on_button_qtedge_clicked()
{
  QtTestQtEdgeDialog * const d{
    new QtTestQtEdgeDialog
  };
  d->setStyleSheet(this->styleSheet());
  emit add_me(d);
}
