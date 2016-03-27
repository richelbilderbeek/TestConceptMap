#include "qttestconceptmapqtnodedialog.h"
#include <boost/test/unit_test.hpp>

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
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapnodedialog.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmapqtnodedialog.h"
#include "qtconceptmapratestrategy.h"
#include "qtkeyboardfriendlygraphicsview.h"
#include "qtimage.h"
#include "testtimer.h"
#include "trace.h"
#include "qtroundededitrectitem.h"
#include "ui_qttestconceptmapqtnodedialog.h"

BOOST_AUTO_TEST_CASE(ribi_cmap_QtTestQtNodeDialog_test)
{
  using namespace ribi;
  using namespace ribi::cmap;
  const bool verbose{false};
  QtTestQtNodeDialog dialog;

  if (verbose) {TRACE("Loading all tests, three times");}
  {
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
  if (verbose) {TRACE("QtNode must be the same in both dialogs");}
  {
    BOOST_CHECK(dialog.GetDialog()->GetQtNode());
  }
  if (verbose) {TRACE("QGraphicsView must contain exactly one item");}
  {
    BOOST_CHECK(dialog.GetView()->scene()->items().size() == 1);
  }
  if (verbose) {TRACE("QGraphicsItem in QGraphicsView must be convertible to a QtRoundedEditRectItem");}
  {
    const QGraphicsItem * const item = dialog.GetView()->scene()->items()[0];
    const QtRoundedEditRectItem * qtitem = dynamic_cast<const QtRoundedEditRectItem*>(item);
    BOOST_CHECK(qtitem);
  }
  if (verbose) {TRACE("QGraphicsItem in QGraphicsView must be convertible to a QtNode");}
  {
    const QGraphicsItem * const item = dialog.GetView()->scene()->items()[0];
    const QtNode * qtnode = dynamic_cast<const QtNode*>(item);
    BOOST_CHECK(qtnode);
  }
  if (verbose) {TRACE("QtNode its base class in the QGraphicsView must contain one line of text");}
  {
    const QGraphicsItem * const item = dialog.GetView()->scene()->items()[0];
    const QtRoundedEditRectItem * qtrectitem = dynamic_cast<const QtRoundedEditRectItem*>(item);
    const auto v = qtrectitem->GetText();
    if (v.size() != 1)
    {
      TRACE(v.size());
      for (const auto& s: v) { TRACE(s); }
    }
    BOOST_CHECK(v.size() == 1);
  }
  if (verbose) { TRACE("Grabbing QtNode of QGraphicsView twice, results in an identical picture"); }
  {
    //If the line below is needed, update() is not called automatically
    const QImage image_before{dialog.GetUiView()};
    const QImage image_after{dialog.GetUiView()};
    BOOST_CHECK(image_before == image_after);
  }
  if (verbose) { TRACE("QGraphicsScene must have one item"); }
  {
    BOOST_CHECK(dialog.GetView()->scene()->items().size() == 1);
  }
}
