#ifndef QTTESTCONCEPTMAPQTEDGEDIALOG_TEST_H
#define QTTESTCONCEPTMAPQTEDGEDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace cmap {

class qttestconceptmapqtedgedialog_test : public QObject
{
    Q_OBJECT

private slots:
  void test_numbers_of_gui_must_match_with_actual_number();
  void gui_must_select_for_valid_test_numbers();
  void set_all_tests();
  void check_number_of_items_is_qgraphicsview();
};

} //~namespace cmap
} //~namespace ribi

#endif // QTTESTCONCEPTMAPQTEDGEDIALOG_TEST_H
