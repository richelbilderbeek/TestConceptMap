#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestconceptmapexamplesdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QDesktopWidget>
#include <QKeyEvent>
#include <QLabel>

#include "conceptmapexamplesfactory.h"
#include "qtconceptmapexamplesdialog.h"
#include "trace.h"
#include "ui_qttestconceptmapexamplesdialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestExamplesDialog::QtTestExamplesDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestExamplesDialog),
    m_examples{new QtExamplesDialog}
{
  ui->setupUi(this);


  {
    assert(this->layout());
    layout()->addWidget(m_examples.get());
  }
  {
    const int n_tests = ExamplesFactory().GetNumberOfTests();
    for (int i=0; i!=n_tests; ++i)
    {
      ui->box_load_examples->addItem(boost::lexical_cast<std::string>(i).c_str());
    }
    ui->box_load_examples->setCurrentIndex(0);
  }
  on_button_load_examples_clicked();

}

ribi::cmap::QtTestExamplesDialog::~QtTestExamplesDialog()
{
  delete ui;
}

void ribi::cmap::QtTestExamplesDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::cmap::QtTestExamplesDialog::on_button_load_examples_clicked()
{
  const int i = ui->box_load_examples->currentIndex();
  assert(i >= 0);
  assert(i < ExamplesFactory().GetNumberOfTests());
  const auto examples = ExamplesFactory().GetTest(i);
  m_examples->SetExamples(examples);
  assert(m_examples->GetExamples() == examples);
}
