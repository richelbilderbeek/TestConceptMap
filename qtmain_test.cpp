#include "qttesteditconceptmapdialog_test.h"
#include "qttestconceptmapqtnodedialog_test.h"
#include "qttestconceptmapqtedgedialog_test.h"

#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  int error = 0;
  { ribi::qttesteditconceptmapdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::qttestconceptmapqtnodedialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::cmap::qttestconceptmapqtedgedialog_test t; error |= QTest::qExec(&t, argc, argv); }
  return error;
}
