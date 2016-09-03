#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestconceptmapqtnodedialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <QDesktopWidget>
#include <QGraphicsView>
#include <QKeyEvent>

#include "conceptmapcompetencies.h"
#include "conceptmapconcept.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapnodedialog.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmapqtnodedialog.h"
#include "qtkeyboardfriendlygraphicsview.h"
#include "qtimage.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestconceptmapqtnodedialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestQtNodeDialog::QtTestQtNodeDialog(
  QWidget *parent)
  : QtPage(parent),
    ui(new Ui::QtTestQtNodeDialog),
    m_dialog{new QtQtNodeDialog},
    m_view{new QtKeyboardFriendlyGraphicsView}
{
  ui->setupUi(this);
  {
    QGraphicsScene * const my_scene = new QGraphicsScene(this);
    m_view->setScene(my_scene);
  }

  assert(!this->ui->here->layout());
  QGridLayout * const my_layout = new QGridLayout;
  ui->here->setLayout(my_layout);

  my_layout->addWidget(ui->widget_top,0,0,1,4);

  my_layout->addWidget(m_view.get(),1,0);
  my_layout->addWidget(m_dialog.get(),1,2);


  ui->box_test_index->setMinimum(0);
  ui->box_test_index->setMaximum(NodeFactory().GetNumberOfTests());
  ui->box_test_index->setValue(0);

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 9 / 10, screen.height() * 9 / 10);
    this->move( screen.center() - this->rect().center() );
  }


  this->on_button_load_clicked();

}

ribi::cmap::QtTestQtNodeDialog::~QtTestQtNodeDialog() noexcept
{
  delete ui;
}


boost::shared_ptr<ribi::cmap::QtNode> ribi::cmap::QtTestQtNodeDialog::GetQtNode() const noexcept
{
  return m_dialog->GetQtNode();
}

QImage ribi::cmap::QtTestQtNodeDialog::GetUiView() const noexcept
{
  const auto scene = this->m_view->scene();
  // Create the image with the exact size of the shrunk scene
  QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
  // Start all pixels transparent
  image.fill(Qt::transparent);
  QPainter painter(&image);
  scene->render(&painter);
  return image;
}

void ribi::cmap::QtTestQtNodeDialog::SetQtNode(const boost::shared_ptr<QtNode>& qtnode) noexcept
{
  assert(qtnode);
  assert(m_view);
  assert(m_view->scene());
  if (!m_view->scene()->items().isEmpty())
  {
    const auto v = m_view->scene()->items();
    assert(v.count() == 1);
    assert(v[0]->scene());
    m_view->scene()->removeItem(v[0]);
    assert(!v[0]->scene());
  }
  assert(m_view->scene()->items().isEmpty());
  m_dialog->SetQtNode(qtnode);

  assert(!qtnode->scene());
  this->m_view->scene()->addItem(qtnode.get());
  assert(qtnode->scene());

  m_dialog->setMinimumHeight(QtQtNodeDialog::GetMinimumHeight(*qtnode));
}

void ribi::cmap::QtTestQtNodeDialog::keyPressEvent(QKeyEvent *event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::cmap::QtTestQtNodeDialog::on_button_load_clicked() noexcept
{
  const int index{ui->box_test_index->value()};
  const auto qtnode = boost::make_shared<QtNode>(
    NodeFactory().GetTest(index)
  );
  SetQtNode(qtnode);
}
