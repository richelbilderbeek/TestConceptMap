#include "qttestconceptmapqtnodedialog_test.h"
#include "qttestconceptmapqtnodedialog.h"

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <QDesktopWidget>
#include <QGraphicsView>
#include <QKeyEvent>

#include "conceptmapcompetencies.h"
#include "conceptmapconcept.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapnodedialog.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmapqtnodedialog.h"
#include "qtkeyboardfriendlygraphicsview.h"
#include "qtimage.h"
#include "testtimer.h"
#include "trace.h"
#include "qtroundededitrectitem.h"
#include "ui_qttestconceptmapqtnodedialog.h"

void ribi::cmap::qttestconceptmapqtnodedialog_test::load_all_tests_thrice()
{
  QtTestQtNodeDialog dialog;
  const int n{dialog.GetUi()->box_test_index->maximum()};
  for (int i=0; i!=n; ++i)
  {
    dialog.GetUi()->box_test_index->setValue(i);
    dialog.on_button_load_clicked();
    dialog.GetUi()->box_test_index->setValue(i);
    dialog.on_button_load_clicked();
    dialog.GetUi()->box_test_index->setValue(i);
    dialog.on_button_load_clicked();
  }
}

void ribi::cmap::qttestconceptmapqtnodedialog_test::must_have_qtnode()
{
  QtTestQtNodeDialog dialog;
  QVERIFY(dialog.GetDialog()->GetQtNode().get());
}

void ribi::cmap::qttestconceptmapqtnodedialog_test::qgraphicsitem_must_be_a_qtnode()
{
  QtTestQtNodeDialog dialog;
  const QGraphicsItem * const item = dialog.GetView()->scene()->items()[0];
  const QtNode * qtnode = dynamic_cast<const QtNode*>(item);
  QVERIFY(qtnode);
}

void ribi::cmap::qttestconceptmapqtnodedialog_test::qgraphicsitem_must_be_a_qtroundededitrectitem()
{
  QtTestQtNodeDialog dialog;
  const QGraphicsItem * const item = dialog.GetView()->scene()->items()[0];
  const QtRoundedEditRectItem * qtitem = dynamic_cast<const QtRoundedEditRectItem*>(item);
  QVERIFY(qtitem);
}

void ribi::cmap::qttestconceptmapqtnodedialog_test::qgraphicsscene_must_contain_exactly_one_item()
{
  QtTestQtNodeDialog dialog;
  QVERIFY(dialog.GetView()->scene()->items().size() == 1);
}

void ribi::cmap::qttestconceptmapqtnodedialog_test::qtnode_must_have_one_line_of_text()
{
  QtTestQtNodeDialog dialog;
  const QGraphicsItem * const item = dialog.GetView()->scene()->items()[0];
  const QtRoundedEditRectItem * qtrectitem = dynamic_cast<const QtRoundedEditRectItem*>(item);
  const auto v = qtrectitem->GetText();
  QVERIFY(v.size() == 1);
}

void ribi::cmap::qttestconceptmapqtnodedialog_test::two_screengrabs_result_in_identical_pictures()
{
  QtTestQtNodeDialog dialog;
  const QImage image_before{dialog.GetUiView()};
  const QImage image_after{dialog.GetUiView()};
  QVERIFY(image_before == image_after);
}
