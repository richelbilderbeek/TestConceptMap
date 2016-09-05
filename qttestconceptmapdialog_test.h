#ifndef QTTESTCONCEPTMAPDIALOG_TEST_H
#define QTTESTCONCEPTMAPDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace cmap {

class qttestconceptmapdialog_test : public QObject
{
    Q_OBJECT

private slots:
  void default_construction();
  void create_node();
  void create_edge_with_arrow_head();
};

} //~namespace cmap
} //~namespace ribi

#endif // QTTESTCONCEPTMAPDIALOG_TEST_H
