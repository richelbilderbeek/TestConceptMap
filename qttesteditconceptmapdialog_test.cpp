#include "qttesteditconceptmapdialog_test.h"

#include <QtTest>
#include "qttesteditconceptmapdialog.h"

//#include <QDesktopWidget>
//#include <QGraphicsView>
//#include <QKeyEvent>

//#include "conceptmapcompetencies.h"
//#include "qttesteditconceptmapdialog.h"
//#include "conceptmapconcept.h"
//#include "conceptmapexample.h"
//#include "conceptmapexamples.h"
//#include "conceptmapnodefactory.h"
//#include "conceptmapnode.h"
//#include "qtconceptmapbrushfactory.h"
//#include "qtconceptmapdisplaystrategy.h"
//#include "qtconceptmapeditstrategy.h"
//#include "qtconceptmapnodedialog.h"
//#include "qtconceptmapqtnode.h"
//#include "qtconceptmapqtnodedialog.h"
//#include "qtconceptmapratestrategy.h"
//#include "qtkeyboardfriendlygraphicsview.h"
//#include "qtimage.h"
//#include "qtroundededitrectitem.h"
//#include "ui_qttestconceptmapqtnodedialog.h"

void ribi::cmap::qttesteditconceptmapdialog_test::create_node()
{
  ribi::cmap::QtTestEditConceptMapDialog d;
  d.show();
  QTest::keyClick(d.GetQtConceptMap(), Qt::Key_N, Qt::ControlModifier, 100);
  const auto excepted_vertices = 1;
  const auto measured_vertices = boost::num_vertices(d.GetQtConceptMap()->GetConceptMap());
  QVERIFY(measured_vertices == excepted_vertices);
}

void ribi::cmap::qttesteditconceptmapdialog_test::create_node_on_concept_map()
{
  ribi::cmap::QtConceptMap d;
  d.show();
  QTest::keyClick(&d, Qt::Key_N, Qt::ControlModifier, 100);
  const auto excepted_vertices = 1;
  const auto measured_vertices = boost::num_vertices(d.GetConceptMap());
  QVERIFY(measured_vertices == excepted_vertices);
}
