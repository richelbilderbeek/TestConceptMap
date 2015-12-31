#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestconceptmapedgedialog.h"

#include <cassert>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>
#include <QLabel>

#include "conceptmapcompetencies.h"
#include "conceptmapedgefactory.h"
#include "conceptmapedge.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "qtconceptmapnodedialog.h"
#include "qtconceptmapedgedialog.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapratestrategy.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestconceptmapedgedialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestEdgeDialog::QtTestEdgeDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestEdgeDialog),
    m_from_node(NodeFactory().GetTest(0)),
    m_qtedgedialog{nullptr},
    m_to_node(NodeFactory().GetTest(0))
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  assert(layout());

  m_qtedgedialog = new QtEdgeDialog(
    EdgeFactory().GetTest(0,m_from_node,m_to_node),this
  );

  ui->box_test->setMinimum(0);
  ui->box_test->setMaximum(EdgeFactory().GetNumberOfTests() - 1);
  QGridLayout * const my_layout = new QGridLayout;
  {
    assert(!ui->scrollAreaWidgetContents->layout());
    ui->scrollAreaWidgetContents->setLayout(my_layout);
    assert(ui->scrollAreaWidgetContents->layout());
  }
  {
    QSizePolicy policy;
    policy.setVerticalStretch(0);
    QLabel * const label = new QLabel("#1");
    label->setSizePolicy(policy);
    my_layout->addWidget(label,0,0);
  }
  {
    QSizePolicy policy;
    policy.setVerticalStretch(2);
    m_qtedgedialog->setSizePolicy(policy);
    my_layout->addWidget(m_qtedgedialog,1,0);
  }

  {
    QSizePolicy policy;
    policy.setVerticalStretch(0);
    QLabel * const label = new QLabel("#2");
    label->setSizePolicy(policy);
    my_layout->addWidget(label,0,1);
  }

  m_qtedgedialog->setMinimumHeight(500);
  m_qtedgedialog->setMinimumWidth(100);
  ui->box_test->setValue(1);
  on_button_load_clicked();

}

ribi::cmap::QtTestEdgeDialog::~QtTestEdgeDialog() noexcept
{
  delete ui;
}


void ribi::cmap::QtTestEdgeDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void ribi::cmap::QtTestEdgeDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

void ribi::cmap::QtTestEdgeDialog::on_button_load_clicked()
{
  const int i = ui->box_test->value();
  assert(i >= 0);
  assert(i < EdgeFactory().GetNumberOfTests());
  const auto edge = EdgeFactory().GetTest(i,m_from_node,m_to_node);
  m_qtedgedialog->SetEdge(edge);
  assert(m_qtedgedialog->GetEdge() == edge);
  m_qtedgedialog->repaint();
}
