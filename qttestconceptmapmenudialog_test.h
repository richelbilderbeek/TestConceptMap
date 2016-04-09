#ifndef QTTESTCONCEPTMAPMENUDIALOG_TEST_H
#define QTTESTCONCEPTMAPMENUDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace cmap {

class qttestconceptmapmenudialog_test : public QObject
{
    Q_OBJECT

private slots:
  void console_menu_dialog();
  void default_construction();
};

} //~namespace cmap
} //~namespace ribi

#endif // QTTESTCONCEPTMAPMENUDIALOG_TEST_H
