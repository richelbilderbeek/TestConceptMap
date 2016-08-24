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
#include "conceptmapexample.h"
#include "conceptmapexamplesfactory.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "convert_dot_to_svg.h"
#include "convert_svg_to_png.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapexamplesitem.h"
#include "qtconceptmap.h"
#include "qtconceptmaphelper.h"
#include "qtconceptmapqtedge.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmapratestrategy.h"
#include "qtconceptmaptoolsitem.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttesteditconceptmapdialog.h"
#pragma GCC diagnostic pop

namespace ribi {
  namespace testeditconceptmapdialog {
    QKeyEvent CreateRandomKey() noexcept {
      const std::vector<Qt::Key> keys = {
        Qt::Key_A,
        Qt::Key_B,
        Qt::Key_C,
        Qt::Key_D,
        Qt::Key_E,
        Qt::Key_E,
        Qt::Key_E,
        Qt::Key_E, //Edge
        Qt::Key_F,
        Qt::Key_G,
        Qt::Key_H,
        Qt::Key_H, //Head
        Qt::Key_I,
        Qt::Key_J,
        Qt::Key_K,
        Qt::Key_L,
        Qt::Key_M,
        Qt::Key_N,
        Qt::Key_N, //New
        Qt::Key_O,
        Qt::Key_P,
        Qt::Key_Q,
        Qt::Key_R,
        Qt::Key_S,
        Qt::Key_T,
        Qt::Key_T, // Tail
        Qt::Key_U,
        Qt::Key_V,
        Qt::Key_W,
        Qt::Key_X,
        Qt::Key_Y,
        Qt::Key_Z,
        Qt::Key_0,
        Qt::Key_1,
        Qt::Key_2,
        Qt::Key_3,
        Qt::Key_4,
        Qt::Key_5,
        Qt::Key_6,
        Qt::Key_7,
        Qt::Key_8,
        Qt::Key_9,
        Qt::Key_F2,
        Qt::Key_Left,
        Qt::Key_Right,
        Qt::Key_Up,
        Qt::Key_Down,
        Qt::Key_Space,
        Qt::Key_Delete,
        Qt::Key_Insert
      };
      const std::vector<Qt::KeyboardModifier> modifiers = {
        Qt::NoModifier,
        Qt::ControlModifier,
        Qt::ShiftModifier,
        Qt::AltModifier
        //Qt::ControlModifier | Qt::ShiftModifier,
        //Qt::ControlModifier | Qt::AltModifier,
        //Qt::AltModifier | Qt::ShiftModifier
        //Qt::ControlModifier | Qt::AltModifier | Qt::ShiftModifier
      };
      return QKeyEvent(
        QEvent::KeyPress,
        keys[ std::rand() % keys.size() ],
        modifiers[ std::rand() % modifiers.size() ]
      );
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

  #ifndef NDEBUG
  this->setWindowTitle(this->windowTitle() + QString(" (debug mode)"));
  #else
  this->setWindowTitle(this->windowTitle() + QString(" (release mode)"));
  #endif
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
    timer->setInterval(1);
    timer->start();
  }
  {
    QObject::connect(m_timer_virtual_bastard,SIGNAL(timeout()),this,SLOT(OnVirtualBastard()));
    m_timer_virtual_bastard->setInterval(1);
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
  m_qtconceptmap->keyPressEvent(event);
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
  //TRACE(n_keys);
  ++n_keys;

  QKeyEvent event{
    testeditconceptmapdialog::CreateRandomKey()
  };
  m_qtconceptmap->SetVerbosity(true);
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


void ribi::cmap::QtTestEditConceptMapDialog::on_button_view_graphviz_summary_clicked()
{
  SaveSummaryToFile(m_qtconceptmap->GetConceptMap(),"summary.dot");
  convert_dot_to_svg("summary.dot","summary.svg");
  convert_svg_to_png("summary.svg","summary.png");
  ui->image_concept_map_summary->setPixmap(QPixmap("summary.png"));
  this->repaint();
}

void ribi::cmap::QtTestEditConceptMapDialog::on_button_view_graphviz_full_clicked()
{
  SaveToFile(m_qtconceptmap->GetConceptMap(),"full.dot");
  convert_dot_to_svg("full.dot","full.svg");
  convert_svg_to_png("full.svg","full.png");
  ui->image_concept_map_full->setPixmap(QPixmap("full.png"));
  this->repaint();

}

void ribi::cmap::QtTestEditConceptMapDialog::on_box_run_virtual_bastard_stateChanged(int /* arg1 */)
{
  ToggleVirtualBastard();
}

void ribi::cmap::QtTestEditConceptMapDialog::on_box_mode_currentIndexChanged(int index)
{
  switch(index)
  {
    case 0: this->m_qtconceptmap->SetMode(Mode::edit); return;
    case 1: this->m_qtconceptmap->SetMode(Mode::rate); return;
    case 2: this->m_qtconceptmap->SetMode(Mode::uninitialized); return;
    default:
      assert(!"Should not get here");
      throw std::logic_error("on_box_mode_currentIndexChanged: unimplemented index");
  }
  m_qtconceptmap->update();
}

void ribi::cmap::QtTestEditConceptMapDialog::on_button_set_concept_map_clicked()
{
  static int i = 0;
  const auto conceptmaps = ConceptMapFactory().GetAllTests();
  m_qtconceptmap->SetConceptMap(conceptmaps[i]);
  i = ((i + 1) % conceptmaps.size());
}
