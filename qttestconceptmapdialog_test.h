#ifndef QTTESTEDITCONCEPTMAPDIALOG_TEST_H
#define QTTESTEDITCONCEPTMAPDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace cmap {

class qttesteditconceptmapdialog_test : public QObject
{
    Q_OBJECT

private slots:
  void default_construction();
  void create_node();
  void create_edge_with_arrow_head();
};

} //~namespace cmap
} //~namespace ribi

#endif // QTTESTEDITCONCEPTMAPDIALOG_TEST_H
