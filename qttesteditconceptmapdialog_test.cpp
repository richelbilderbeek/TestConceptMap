#include "qttesteditconceptmapdialog_test.h"

#include <QtTest>
#include "qttesteditconceptmapdialog.h"

void ribi::cmap::qttesteditconceptmapdialog_test::default_construction()
{
  ribi::cmap::QtTestEditConceptMapDialog d;
  d.show();
}

void ribi::cmap::qttesteditconceptmapdialog_test::create_node()
{
  ribi::cmap::QtTestEditConceptMapDialog d;
  d.show();
  //If you want to use 'd.GetQtConceptMap()' go work on the QtConceptMap tests :-)
  QTest::keyClick(&d, Qt::Key_N, Qt::ControlModifier, 100);
  const auto excepted_vertices = 1;
  const auto measured_vertices = boost::num_vertices(d.GetQtConceptMap()->GetConceptMap());
  QVERIFY(measured_vertices == excepted_vertices);
}
