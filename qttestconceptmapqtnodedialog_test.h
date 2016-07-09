#ifndef QTTESTCONCEPTMAPQTNODEDIALOG_TEST_H
#define QTTESTCONCEPTMAPQTNODEDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace cmap {

class qttestconceptmapqtnodedialog_test : public QObject
{
    Q_OBJECT

private slots:
  void load_all_tests_thrice();
  void must_have_qtnode();
  void qgraphicsitem_must_be_a_qtnode();
  void qgraphicsitem_must_be_a_qtroundededitrectitem();
  void qgraphicsscene_must_contain_exactly_one_item();
  void qtnode_must_have_one_line_of_text();
  void two_screengrabs_result_in_identical_pictures();
};

} //~namespace cmap
} //~namespace ribi

#endif // QTTESTCONCEPTMAPQTNODEDIALOG_TEST_H
