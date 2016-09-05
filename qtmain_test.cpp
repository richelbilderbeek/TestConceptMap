#include <iostream>
#include <QtTest/QtTest>

#include "qtconceptmapviewtestsdialog_test.h"
#include "qttestconceptmapmenudialog_test.h"
#include "qttestconceptmapdialog_test.h"
#include "qttestconceptmapqtnodedialog_test.h"
#include "qttestconceptmapqtedgedialog_test.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  int error = 0;
  { ribi::cmap::qtconceptmapviewtestsdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::cmap::qttestconceptmapmenudialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::cmap::qttestconceptmapdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::cmap::qttestconceptmapqtnodedialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::cmap::qttestconceptmapqtedgedialog_test t; error |= QTest::qExec(&t, argc, argv); }
  if (!error) { std::cout << "Pass\n"; }
  if ( error) { std::cout << "Fail\n"; }
  return error;
}
