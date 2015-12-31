#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestconceptmapnodedialog.h"

#include <cassert>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>
#include <QLabel>

#include "conceptmapcompetencies.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "qtconceptmapnodedialog.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapratestrategy.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestconceptmapnodedialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestNodeDialog::QtTestNodeDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestNodeDialog),
    m_qtnodedialog{new QtNodeDialog}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  assert(layout());

  ui->box_test->setMinimum(0);
  ui->box_test->setMaximum(NodeFactory().GetNumberOfTests() - 1);

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
    m_qtnodedialog->setSizePolicy(policy);
    ui->widget->layout()->addWidget(m_qtnodedialog.get());
    //grid_layout->addWidget(m_qtnodedialog_1.get(),2,0);
  }

  m_qtnodedialog->setMinimumHeight(100);
  m_qtnodedialog->setMinimumWidth(100);
  ui->box_test->setValue(1);
  on_button_load_clicked();

}

ribi::cmap::QtTestNodeDialog::~QtTestNodeDialog() noexcept
{
  delete ui;
}


void ribi::cmap::QtTestNodeDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void ribi::cmap::QtTestNodeDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

void ribi::cmap::QtTestNodeDialog::on_button_load_clicked()
{
  const int i = ui->box_test->value();
  assert(i >= 0);
  assert(i < NodeFactory().GetNumberOfTests());
  const auto node = NodeFactory().GetTest(i);
  m_qtnodedialog->SetNode(node);
  assert(m_qtnodedialog->GetNode() == node);
  m_qtnodedialog->repaint();
}
