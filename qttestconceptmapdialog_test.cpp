#include "qttestconceptmapdialog_test.h"

#include <QtTest>
#include "qttestconceptmapdialog.h"
#include "get_my_custom_edge.h"
#include "qtconceptmaphelper.h"
#include "conceptmap.h"
#include "qtquadbezierarrowitem.h"

void ribi::cmap::qttestconceptmapdialog_test::default_construction()
{
  ribi::cmap::QtTestConceptMapDialog d;
  d.show();
}

void ribi::cmap::qttestconceptmapdialog_test::create_node()
{
  ribi::cmap::QtTestConceptMapDialog d;
  d.show();
  //If you want to use 'd.GetQtConceptMap()' go work on the QtConceptMap tests :-)
  QTest::keyClick(&d, Qt::Key_N, Qt::ControlModifier, 100);
  const auto excepted_vertices = 1;
  const auto measured_vertices = boost::num_vertices(d.GetQtConceptMap()->GetConceptMap());
  QVERIFY(measured_vertices == excepted_vertices);
}

void ribi::cmap::qttestconceptmapdialog_test::create_edge_with_arrow_head()
{
  //Added this for https://github.com/richelbilderbeek/Brainweaver/issues/88
  //just to be sure that a QtConceptMap gets saved correctly
  ribi::cmap::QtTestConceptMapDialog d;
  d.show();
  //If you want to use 'd.GetQtConceptMap()' go work on the QtConceptMap tests :-)
  QTest::keyClick(&d, Qt::Key_N, Qt::ControlModifier, 100);
  QTest::keyClick(&d, Qt::Key_N, Qt::ControlModifier, 100);
  QTest::keyClick(&d, Qt::Key_E, Qt::ControlModifier, 100);
  QTest::keyClick(&d, Qt::Key_H, Qt::ControlModifier, 100);

  const auto qtconceptmap = d.GetQtConceptMap();
  const auto qtnodes = ribi::cmap::GetQtNodes(*qtconceptmap->scene());
  const auto excepted_vertices = 2;
  const auto measured_vertices = qtnodes.size();
  QVERIFY(measured_vertices == excepted_vertices);
  const auto qtedges = ribi::cmap::GetQtEdges(*qtconceptmap->scene());
  const auto excepted_edges = 1;
  const auto measured_edges = qtedges.size();
  QVERIFY(measured_edges == excepted_edges);
  const QtEdge * const qtedge = qtedges[0];
  assert(qtedge);

  QVERIFY(qtedge->GetArrow()->HasHead());
  QVERIFY(qtedge->GetEdge().HasHeadArrow());
  QVERIFY(!qtedge->GetArrow()->HasTail());
  QVERIFY(!qtedge->GetEdge().HasTailArrow());

  const std::string s = ToDot(d.GetQtConceptMap()->GetConceptMap());

  QVERIFY(s.find("<has_head>1</has_head>") != std::string::npos);
  QVERIFY(s.find("<has_tail>0</has_tail>") != std::string::npos);
  const std::string t = ToXml(d.GetQtConceptMap()->GetConceptMap());
  QVERIFY(t.find("<has_head>1</has_head>") != std::string::npos);
  QVERIFY(t.find("<has_tail>0</has_tail>") != std::string::npos);
}
