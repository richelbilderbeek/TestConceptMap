#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestconceptmapqtedgedialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QDesktopWidget>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QTimer>

#include "conceptmapcompetencies.h"
#include "conceptmapconcept.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmapnodefactory.h"
#include "conceptmapedge.h"
#include "conceptmapnode.h"
#include "grabber.h"
#include "qtimage.h"
#include "qtconceptmapedgefactory.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapnodedialog.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmapqtnodefactory.h"
#include "qtconceptmapqtedge.h"
#include "qtconceptmapqtedgedialog.h"
#include "qtconceptmapqtedgefactory.h"
#include "qtconceptmapratestrategy.h"
#include "qtimage.h"
#include "qtdisplaypositem.h"
#include "qtquadbezierarrowitem.h"
#include "qtkeyboardfriendlygraphicsview.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestconceptmapqtedgedialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestQtEdgeDialog::QtTestQtEdgeDialog(
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestQtEdgeDialog),
    m_qtedge_dialog(
      new QtQtEdgeDialog(
        boost::shared_ptr<QtEdge>() //Stub
      )
    ),
    m_from(QtNodeFactory().GetTest(1)),
    m_to(QtNodeFactory().GetTest(1)),
    m_qtedge_view(new QtKeyboardFriendlyGraphicsView)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  m_from->SetCenterPos(0.0,0.0);
  m_to->SetCenterPos(10.0,100.0);

  assert(m_from->flags() & QGraphicsItem::ItemIsMovable);
  assert(m_from->flags() & QGraphicsItem::ItemIsSelectable);
  assert(m_to->flags()   & QGraphicsItem::ItemIsMovable);
  assert(m_to->flags()   & QGraphicsItem::ItemIsSelectable);


  {
    QGraphicsScene * const my_scene = new QGraphicsScene(this);
    m_qtedge_view->setScene(my_scene);

    my_scene->addItem(m_from.get()); //Remove in destructor
    my_scene->addItem(m_to.get()); //Remove in destructor

    QtDisplayPosItem * const item{new QtDisplayPosItem};
    item->setZValue(10000.0);
    my_scene->addItem(item); //Displays the positions
  }
  ui->area1->setWidget(m_qtedge_view.get());
  ui->area3->setWidget(m_qtedge_dialog.get());

  ui->box_test_index->setMinimum(0);
  ui->box_test_index->setMaximum(QtEdgeFactory().GetNumberOfTests() - 1); //-1 because first index has [0]
  ui->box_test_index->setValue(0);

  this->on_button_load_clicked();

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 9 / 10, screen.height() * 9 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

ribi::cmap::QtTestQtEdgeDialog::~QtTestQtEdgeDialog() noexcept
{
  SetQtEdge(nullptr);
  m_qtedge_view->scene()->removeItem(m_from.get()); //Remove in destructor
  m_qtedge_view->scene()->removeItem(m_to.get());   //Remove in destructor
  delete ui;
}


boost::shared_ptr<ribi::cmap::QtEdge> ribi::cmap::QtTestQtEdgeDialog::GetQtEdge() const noexcept
{
  return m_qtedge_dialog->GetQtEdge();
}

int ribi::cmap::QtTestQtEdgeDialog::GetUiTestIndex() const noexcept
{
  return ui->box_test_index->value();
}

QImage ribi::cmap::QtTestQtEdgeDialog::GetUiView() const noexcept
{ 
  const auto scene = this->m_qtedge_view->scene();
  // Create the image with the exact size of the shrunk scene
  const QSize old_size{scene->sceneRect().size().toSize()};
  //Rescaled by a factor two to fix BUG_260
  //const QSize new_size(old_size.scaled(2,2, Qt::KeepAspectRatio)); //Adding this introduces a new bug
  QImage image(old_size, QImage::Format_ARGB32);
  // Start all pixels transparent
  image.fill(Qt::transparent);
  QPainter painter(&image);
  scene->render(&painter);
  return image;
}

double ribi::cmap::QtTestQtEdgeDialog::GetUiX() const noexcept
{
  return m_qtedge_dialog->GetUiX();
}

double ribi::cmap::QtTestQtEdgeDialog::GetUiY() const noexcept
{
  return m_qtedge_dialog->GetUiX();
}

void ribi::cmap::QtTestQtEdgeDialog::SetQtEdge(const boost::shared_ptr<QtEdge>& qtedge) noexcept
{
  assert(m_qtedge_view);
  const auto old_qtedge = m_qtedge_dialog->GetQtEdge();

  if (old_qtedge)
  {
    m_qtedge_view->scene()->removeItem(old_qtedge.get());
  }
  if (qtedge)
  {
    m_qtedge_dialog->SetQtEdge(qtedge);
    this->m_qtedge_view->scene()->addItem(qtedge.get());

    m_qtedge_dialog->setMinimumHeight(QtQtEdgeDialog::GetMinimumHeight(*qtedge));
  }
}

void ribi::cmap::QtTestQtEdgeDialog::keyPressEvent(QKeyEvent *event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void ribi::cmap::QtTestQtEdgeDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    QtImage();
  }
  const TestTimer test_timer(__func__,__FILE__,2.0);
  const bool verbose{false};
  QtTestQtEdgeDialog dialog;
  const boost::shared_ptr<QtEdge> qtedge{dialog.GetQtEdge()};
  const int n = dialog.ui->box_test_index->maximum();
  if (verbose) { TRACE("Number of tests in GUI must be equal to the number of actual tests"); }
  {
    assert(n == QtEdgeFactory().GetNumberOfTests() - 1
      && "If there are x tests, the maximum test index is x-1");
  }
  if (verbose) { TRACE("Test index in GUI must be lower than the number of actual tests"); }
  {    
    for (int i=0; i!=10; ++i)
    {
      dialog.ui->box_test_index->setValue(i);
      assert(dialog.GetUiTestIndex() < QtEdgeFactory().GetNumberOfTests());
    }
  }
  if (verbose) { TRACE("Setting all test edges"); }
  {
    //QtTestQtEdgeDialog dialog;
    const int n{QtEdgeFactory().GetNumberOfTests()};
    for (int i=0; i!=n; ++i)
    {
      dialog.ui->box_test_index->setValue(i);
      dialog.on_button_load_clicked();
    }
  }
  dialog.SetQtEdge(qtedge); //Put QtEdge in back again
  if (verbose) { TRACE("There are items in the QGraphicsView"); }
  {
    assert(dialog.m_qtedge_view->items().size() >= 3);
  }
  if (verbose) { TRACE("Grabbing QtEdge of QGraphicsView twice, results in an identical picture"); }
  {
    //If the line below is needed, update() is not called automatically
    const QImage image_tmp{dialog.GetUiView()}; //Needed to force something more thorough than update and repaint
    const QImage image_before{dialog.GetUiView()};
    const QImage image_after{dialog.GetUiView()};
    assert(image_before == image_after);
  }
  if (verbose) { TRACE("If the head arrow head of an QtEdge its Edge is changed, the Item must be updated"); }
  {
    dialog.GetQtEdge()->GetEdge().SetHeadArrow(true);
    const QImage image_before{dialog.GetUiView()};
    dialog.GetQtEdge()->SetHasHeadArrow(false);
    const QImage image_after{dialog.GetUiView()};
    if(image_before == image_after)
    {
      image_before.save("tmp_before.png");
      image_after.save( "tmp_after.png");
      image_before.save("tmp.png");
    }
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the tail arrow head of an QtEdge its Edge is changed, the Item must be updated"); }
  {
    dialog.GetQtEdge()->GetEdge().SetTailArrow(true);
    const QImage image_before{dialog.GetUiView()};
    dialog.GetQtEdge()->GetEdge().SetTailArrow(false);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the source/'from' of an QtEdge is made invisible, this will show in a screenshot"); }
  {
    assert(dialog.m_from->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_from->setVisible(false);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the target/'to' of an QtEdge is made invisible, this will show in a screenshot"); }
  {
    assert(dialog.m_to->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_to->setVisible(false);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the QtNode an QtEdge is made invisible, this will show in a screenshot"); }
  {
    assert(dialog.m_qtedge_dialog->GetQtEdge()->GetQtNode()->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_qtedge_dialog->GetQtEdge()->GetQtNode()->setVisible(false);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the source/'from' of an QtEdge its Edge is changed, the Item must be updated"); }
  {
    const boost::shared_ptr<QtRoundedEditRectItem> from{
      boost::dynamic_pointer_cast<QtRoundedEditRectItem>(dialog.m_from)
    };

    const QImage image_before{dialog.GetUiView()};
    from->setX(from->x() + 100.0);
    const QImage image_after{dialog.GetUiView()};
    //if (image_before != image_after)
    {
      image_before.save("QtTestQtEdgeDialogTest1_before.png");
      image_after.save("QtTestQtEdgeDialogTest1_after.png");
      const QImage result{QtImage().Difference(image_before,image_after)};
      result.save("QtTestQtEdgeDialogTest1_difference.png");
    }
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the target/'to' of an QtEdge its Edge is changed by a member function, the Item must be updated"); }
  {
    const boost::shared_ptr<QtRoundedEditRectItem> to{
      boost::dynamic_pointer_cast<QtRoundedEditRectItem>(dialog.m_to)
    };

    const QImage image_before{dialog.GetUiView()};
    to->setX(to->x() + 100.0);
    const QImage image_after{dialog.GetUiView()};
    //if (image_before != image_after)
    {
      image_before.save("QtTestQtEdgeDialogTest1_before.png");
      image_after.save("QtTestQtEdgeDialogTest1_after.png");
      const QImage result{QtImage().Difference(image_before,image_after)};
      result.save("QtTestQtEdgeDialogTest1_difference.png");
    }
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the target/'to' of an QtEdge its Edge is changed by a drag event, the Item must be updated"); }
  {
    const boost::shared_ptr<QtRoundedEditRectItem> to{
      boost::dynamic_pointer_cast<QtRoundedEditRectItem>(dialog.m_to)
    };

    const QImage image_before{dialog.GetUiView()};
    to->setX(to->x() + 100.0);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If QtNode of QtEdge is made visible, this will look different"); }
  {
    assert(!dialog.m_qtedge_dialog->GetQtEdge()->GetQtNode()->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_qtedge_dialog->GetQtEdge()->GetQtNode()->setVisible(true);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If arrow of QtEdge is made visible, this will look different"); }
  {
    assert(dialog.m_qtedge_dialog->GetQtEdge()->GetArrow()->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_qtedge_dialog->GetQtEdge()->GetArrow()->setVisible(false);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
}
#endif

void ribi::cmap::QtTestQtEdgeDialog::on_button_load_clicked() noexcept
{
  const int index = ui->box_test_index->value();
  assert(m_from);
  assert(m_to);
  assert(index >= 0);
  assert(index < QtEdgeFactory().GetNumberOfTests());
  const auto qtedge = QtEdgeFactory().GetTest(index,m_from,m_to);

  assert(m_from->flags() & QGraphicsItem::ItemIsMovable);
  assert(m_from->flags() & QGraphicsItem::ItemIsSelectable);
  assert(m_to->flags()   & QGraphicsItem::ItemIsMovable);
  assert(m_to->flags()   & QGraphicsItem::ItemIsSelectable);

  SetQtEdge(qtedge);

  assert(qtedge == m_qtedge_dialog->GetQtEdge());

  assert(m_from->flags() & QGraphicsItem::ItemIsMovable);
  assert(m_from->flags() & QGraphicsItem::ItemIsSelectable);
  assert(m_to->flags()   & QGraphicsItem::ItemIsMovable);
  assert(m_to->flags()   & QGraphicsItem::ItemIsSelectable);

  //qtedge itself is not movable
  //assert(qtedge->flags() & QGraphicsItem::ItemIsMovable);
  //assert(qtedge->flags() & QGraphicsItem::ItemIsSelectable);

  assert(qtedge->GetFrom()->flags() & QGraphicsItem::ItemIsMovable);
  assert(qtedge->GetFrom()->flags() & QGraphicsItem::ItemIsSelectable);
  assert(qtedge->GetTo()->flags() & QGraphicsItem::ItemIsMovable);
  assert(qtedge->GetTo()->flags() & QGraphicsItem::ItemIsSelectable);
  assert(qtedge->GetQtNode()->flags() & QGraphicsItem::ItemIsMovable);
  assert(qtedge->GetQtNode()->flags() & QGraphicsItem::ItemIsSelectable);


  this->m_qtedge_dialog->GetQtEdge()->GetFrom()->GetNode().GetConcept().SetName("From");
  this->m_qtedge_dialog->GetQtEdge()->GetTo()->GetNode().GetConcept().SetName("To");
}
