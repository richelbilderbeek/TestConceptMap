#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestconceptmapconceptdialog.h"

#include <cassert>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>
#include <QLabel>

#include "conceptmapcompetencies.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "qtconceptmapconceptdialog.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapratestrategy.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestconceptmapconceptdialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestConceptDialog::QtTestConceptDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestConceptDialog),
    m_qtconceptdialog{new QtConceptDialog}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  assert(layout());

  ui->box_test->setMinimum(0);
  ui->box_test->setMaximum(ConceptFactory().GetNumberOfTests() - 1);

  //assert(grid_layout);
  if (!ui->widget->layout())
  {
    QLayout * const layout = new QVBoxLayout;
    ui->widget->setLayout(layout);

  }
  {
    QSizePolicy policy;
    policy.setVerticalStretch(0);
    QLabel * const label = new QLabel("#1");
    label->setSizePolicy(policy);
    assert(ui->widget->layout());
    ui->widget->layout()->addWidget(label);
    //grid_layout->addWidget(label,1,0);
  }
  {
    QSizePolicy policy;
    policy.setVerticalStretch(2);
    m_qtconceptdialog->setSizePolicy(policy);
    ui->widget->layout()->addWidget(m_qtconceptdialog.get());
    //grid_layout->addWidget(m_qtconceptdialog_1.get(),2,0);
  }

  m_qtconceptdialog->setMinimumHeight(100);
  m_qtconceptdialog->setMinimumWidth(100);

  ui->box_test->setValue(1);
  on_button_load_clicked();

}

ribi::cmap::QtTestConceptDialog::~QtTestConceptDialog() noexcept
{
  delete ui;
}


void ribi::cmap::QtTestConceptDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void ribi::cmap::QtTestConceptDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

void ribi::cmap::QtTestConceptDialog::on_button_load_clicked()
{
  const int i = ui->box_test->value();
  assert(i >= 0);
  assert(i < ConceptFactory().GetNumberOfTests());
  const auto concept = ConceptFactory().GetTest(i);
  m_qtconceptdialog->SetConcept(concept);
  assert(m_qtconceptdialog->GetConcept() == concept);
  m_qtconceptdialog->repaint();
}
