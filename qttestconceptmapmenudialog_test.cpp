#include "qttestconceptmapmenudialog_test.h"

#include "qttestconceptmapmenudialog.h"
#include "testconceptmapmenudialog.h"

void ribi::cmap::qttestconceptmapmenudialog_test::console_menu_dialog()
{
  TestConceptMapMenuDialog d;
  QVERIFY(d.Execute( {} ) ==  0);
  QVERIFY(d.Execute( { "test" } ) == 0);
  QVERIFY(d.Execute( { "test", "--about" } ) == 0);
  QVERIFY(d.Execute( { "test", "--help" } ) == 0);
  QVERIFY(d.Execute( { "test", "--history" } ) == 0);
  QVERIFY(d.Execute( { "test", "--license" } ) == 0);
  QVERIFY(d.Execute( { "test", "--version" } ) == 0);
}

void ribi::cmap::qttestconceptmapmenudialog_test::default_construction()
{
  QtTestMenuDialog d;
  d.show();
}
