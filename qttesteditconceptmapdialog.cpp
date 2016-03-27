#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttesteditconceptmapdialog.h"

#include <cassert>
#include <sstream>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>
#include <QTimer>
#include <QUndoView>

#include "conceptmapconcept.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapexample.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "convert_dot_to_svg.h"
#include "convert_svg_to_png.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapexamplesitem.h"
#include "qtconceptmaptoolsitem.h"
#include "conceptmapexamplesfactory.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapqtedge.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmapratestrategy.h"
#include "qtconceptmap.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttesteditconceptmapdialog.h"
#pragma GCC diagnostic pop

namespace ribi {
  namespace testeditconceptmapdialog {
    QKeyEvent CreateCtrlE() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_E,Qt::ControlModifier); }
    QKeyEvent CreateCtrlLeft() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::ControlModifier); }
    QKeyEvent CreateCtrlN() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_N,Qt::ControlModifier); }
    QKeyEvent CreateCtrlRight() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Right,Qt::ControlModifier); }
    QKeyEvent CreateDelete() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Delete,Qt::NoModifier); }
    QKeyEvent CreateDown() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Down,Qt::NoModifier); }
    QKeyEvent CreateE() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_E,Qt::NoModifier); }
    QKeyEvent CreateLeft() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::NoModifier); }
    QKeyEvent CreateN() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_N,Qt::NoModifier); }
    QKeyEvent CreateRight() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Right,Qt::NoModifier); }
    QKeyEvent CreateShiftE() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_E,Qt::ShiftModifier); }
    QKeyEvent CreateShiftLeft() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::ShiftModifier); }
    QKeyEvent CreateShiftN() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_N,Qt::ShiftModifier); }
    QKeyEvent CreateShift() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Shift,Qt::NoModifier); }
    QKeyEvent CreateShiftRight() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Right,Qt::ShiftModifier); }
    QKeyEvent CreateSpace() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Space,Qt::NoModifier); }
    QKeyEvent CreateUp() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Up,Qt::NoModifier); }
    QKeyEvent CreateX() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_X,Qt::NoModifier); }
    QKeyEvent CreateRandomKey() noexcept {
      switch (std::rand() % 18)
      {
        case  0: return CreateCtrlE();
        case  1: return CreateCtrlLeft();
        case  2: return CreateCtrlN();
        case  3: return CreateCtrlRight();
        case  4: return CreateDelete();
        case  5: return CreateDown();
        case  6: return CreateE();
        case  7: return CreateLeft();
        case  8: return CreateN();
        case  9: return CreateRight();
        case 10: return CreateShiftE();
        case 11: return CreateShiftLeft();
        case 12: return CreateShiftN();
        case 13: return CreateShift();
        case 14: return CreateShiftRight();
        case 15: return CreateSpace();
        case 16: return CreateUp();
        case 17: return CreateX();
      }
      return CreateSpace();
    }
  }
}


ribi::cmap::QtTestEditConceptMapDialog::QtTestEditConceptMapDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestEditConceptMapDialog),
  m_qtconceptmap(new QtConceptMap(this)),
  m_timer_virtual_bastard{new QTimer(this)}
{
  ui->setupUi(this);
  //Create an empty concept map
  m_qtconceptmap->SetConceptMap(
    ConceptMapFactory().Get0()
  );
  assert(ui->widget->layout());
  ui->widget->layout()->addWidget(m_qtconceptmap);

  {
    QUndoView * const view{new QUndoView};
    view->setStack(&m_qtconceptmap->GetUndo());
    assert(ui->widget_menu->layout());
    ui->widget_menu->layout()->addWidget(view);
  }
  {
    QTimer * const timer{new QTimer(this)};
    connect(timer,SIGNAL(timeout()),this,SLOT(OnCheck()));
    timer->setInterval(100);
    timer->start();
  }
  {
    QObject::connect(m_timer_virtual_bastard,SIGNAL(timeout()),this,SLOT(OnVirtualBastard()));
    m_timer_virtual_bastard->setInterval(100);
  }
}

ribi::cmap::QtTestEditConceptMapDialog::~QtTestEditConceptMapDialog() noexcept
{
  delete ui;
}

void ribi::cmap::QtTestEditConceptMapDialog::DoSomethingRandom()
{

  const QList<QGraphicsItem *> v = m_qtconceptmap->GetScene()->items();
  std::for_each(v.begin(),v.end(),
    [](QGraphicsItem * const item)
    {
      if (QtNode* const qtitem = dynamic_cast<QtNode*>(item))
      {
        assert(!qtitem->GetNode().GetConcept().GetName().empty());
        qtitem->GetNode().GetConcept().SetName(qtitem->GetNode().GetConcept().GetName() + "N");
        const std::vector<Examples> v = ExamplesFactory().GetTests();
        qtitem->GetNode().GetConcept().SetExamples(v [ std::rand() % v.size() ] );
        qtitem->update();
      }
      if (QtEdge* const qtitem = dynamic_cast<QtEdge*>(item))
      {
        assert(qtitem->GetQtNode());
        assert( (!qtitem->GetQtNode()->GetNode().GetConcept().GetName().empty() || qtitem->GetQtNode()->GetNode().GetConcept().GetName().empty())
          && "An item can contain no text: when connected to the center node");
        qtitem->GetQtNode()->GetNode().GetConcept().SetName(qtitem->GetQtNode()->GetNode().GetConcept().GetName() + "E");
        const std::vector<Examples> v = ExamplesFactory().GetTests();
        qtitem->GetQtNode()->GetNode().GetConcept().SetExamples(v [ std::rand() % v.size() ] );
        qtitem->update();
      }
    }
  );
  m_qtconceptmap->GetScene()->update();
}

void ribi::cmap::QtTestEditConceptMapDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
  if (event->key() == Qt::Key_F1)
  {
    ToggleVirtualBastard();
  }
  if (event->key() == Qt::Key_F2)
  {
    SaveSummaryToFile(m_qtconceptmap->GetConceptMap(),"summary.dot");
    convert_dot_to_svg("summary.dot","summary.svg");
    convert_svg_to_png("summary.svg","summary.png");
    ui->image_concept_map_summary->setPixmap(QPixmap("summary.png"));
    this->repaint();
  }
  if (event->key() == Qt::Key_F3)
  {
    SaveToFile(m_qtconceptmap->GetConceptMap(),"full.dot");
    convert_dot_to_svg("full.dot","full.svg");
    convert_svg_to_png("full.svg","full.png");
    ui->image_concept_map_full->setPixmap(QPixmap("full.png"));
    this->repaint();
  }
  if (event->key() == Qt::Key_1 && event->modifiers() & Qt::AltModifier)
  {
    DoSomethingRandom();
  }
}

void ribi::cmap::QtTestEditConceptMapDialog::OnCheck()
{

  ui->label_n_nodes->setText(QString("# nodes: ") + QString::number(boost::num_vertices(m_qtconceptmap->GetConceptMap())));
  ui->label_n_edges->setText(QString("# edges: ") + QString::number(boost::num_edges(m_qtconceptmap->GetConceptMap())));
  ui->label_n_items->setText(QString("# QGraphicsItems: ") + QString::number(m_qtconceptmap->GetScene()->items().size()));
  ui->label_n_items_selected->setText(QString("# QGraphicsItems selected: ") + QString::number(m_qtconceptmap->GetScene()->selectedItems().size()));
  ui->label_n_qtnodes->setText(QString("# QtNodes: ") + QString::number(CountQtNodes(m_qtconceptmap->GetScene())));
  ui->label_n_qtnodes_selected->setText(QString("# QtNodes selected: ") + QString::number(CountSelectedQtNodes(m_qtconceptmap->GetScene())));
  ui->label_n_qtedges->setText(QString("# QtEdges: ") + QString::number(CountQtEdges(m_qtconceptmap->GetScene())));
  ui->label_n_qtedges_selected->setText(QString("# QtEdges selected: ") + QString::number(CountSelectedQtEdges(m_qtconceptmap->GetScene())));
  /*
  std::stringstream s;
  s
    << "m_conceptmap \n"
    << "  ->GetScene()->items().size(): "
    << "  (which includes m_conceptmap->m_examples: " << (m_qtconceptmap->GetQtExamplesItem()->scene() ? "yes" : "no") << ")\n"
    << "  (which includes m_conceptmap->m_tools: " << (m_qtconceptmap->GetQtToolItem()->scene() ? "yes" : "no") << ")\n"
  ;


  const auto qtnodes = GetQtNodes(m_qtconceptmap->GetScene());
  const int n_qtnodes{static_cast<int>(qtnodes.size())};
  s << "# QtNodes: " << n_qtnodes << '\n';
  for (int i=0; i!=n_qtnodes; ++i)
  {
    const auto qtnode = qtnodes[i];
    s << "[" << i << "] " << qtnode->GetNode().GetConcept().GetName() << ": "  << qtnode->isSelected() << '\n';
  }
  const auto qtedges = GetQtEdges(m_qtconceptmap->GetScene());
  const int n_qtedges{static_cast<int>(qtedges.size())};
  assert(n_qtedges == CountQtEdges(m_qtconceptmap->GetScene()));
  s << "# QtEdges: " << n_qtedges << '\n';
  for (int i=0; i!=n_qtedges; ++i)
  {
    s << "[" << i << "] " << qtedges[i]->isSelected() << '\n';
  }
  s << "Focus item: ";
  if (m_qtconceptmap->GetScene()->focusItem())
  {
    if (QtNode* const qtnode = dynamic_cast<QtNode*>(m_qtconceptmap->GetScene()->focusItem())) { s << qtnode->GetNode().GetConcept().GetName(); }
    if (QtEdge* const qtedge = dynamic_cast<QtEdge*>(m_qtconceptmap->GetScene()->focusItem())) { s << qtedge->GetQtNode()->GetNode().GetConcept().GetName(); }
  }
  else { s << "(none)";}
  s << '\n';

  ui->label_nodes_selected->setText(s.str().c_str());
  */
}

void ribi::cmap::QtTestEditConceptMapDialog::OnVirtualBastard()
{
  static int n_keys = 0;
  TRACE(n_keys);
  ++n_keys;

  QKeyEvent event{
    testeditconceptmapdialog::CreateRandomKey()
  };
  m_qtconceptmap->keyPressEvent(&event);

}

void ribi::cmap::QtTestEditConceptMapDialog::ToggleVirtualBastard() noexcept
{
  if (m_timer_virtual_bastard->isActive()) {
    TRACE("Stop virtual bastard");
    m_timer_virtual_bastard->stop();
  }
  else {
    TRACE("Start virtual bastard");
    m_timer_virtual_bastard->start();
  }
}

