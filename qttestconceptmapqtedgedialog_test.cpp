#include "qttestconceptmapqtedgedialog_test.h"

#include "qtconceptmapqtedgefactory.h"
#include "qtkeyboardfriendlygraphicsview.h"
#include "qttestconceptmapqtedgedialog.h"
#include "ui_qttestconceptmapqtedgedialog.h"

void ribi::cmap::qttestconceptmapqtedgedialog_test::test_numbers_of_gui_must_match_with_actual_number()
{
  // Number of tests in GUI must be equal to the number of actual tests
  const QtTestQtEdgeDialog dialog;
  const int n = dialog.GetUi()->box_test_index->maximum();
  // If there are x tests, the maximum test index is x-1
  QCOMPARE(n, QtEdgeFactory().GetNumberOfTests() - 1);
}


void ribi::cmap::qttestconceptmapqtedgedialog_test::gui_must_select_for_valid_test_numbers()
{
  // Number of tests in GUI must be equal to the number of actual tests
  QtTestQtEdgeDialog dialog;
  for (int i=-1; i!=QtEdgeFactory().GetNumberOfTests() + 2; ++i)
  {
    dialog.GetUi()->box_test_index->setValue(i);
    QVERIFY(dialog.GetUiTestIndex() >= 0);
    QVERIFY(dialog.GetUiTestIndex() < QtEdgeFactory().GetNumberOfTests());
  }
}


void ribi::cmap::qttestconceptmapqtedgedialog_test::set_all_tests()
{
  // Setting all tests
  QtTestQtEdgeDialog dialog;
  const int n{QtEdgeFactory().GetNumberOfTests()};
  for (int i=0; i!=n; ++i)
  {
    dialog.GetUi()->box_test_index->setValue(i);
    dialog.on_button_load_clicked();
  }
}

void ribi::cmap::qttestconceptmapqtedgedialog_test::check_number_of_items_is_qgraphicsview()
{
  // There are items in the QGraphicsView
  const QtTestQtEdgeDialog dialog;
  QVERIFY(dialog.m_qtedge_view->items().size() >= 3);
}

/*
void ribi::cmap::qttestconceptmapqtedgedialog_test::all_tests()
{
  const bool verbose{false};
  QtTestQtEdgeDialog dialog;
  const boost::shared_ptr<QtEdge> qtedge{dialog.GetQtEdge()};
  const int n = dialog.GetUi()->box_test_index->maximum();
  dialog.SetQtEdge(qtedge); //Put QtEdge in back again
  {
  }
  if (verbose) { TRACE("Grabbing QtEdge of QGraphicsView twice, results in an identical picture"); }
  {
    //If the line below is needed, update() is not called automatically
    const QImage image_tmp{dialog.GetUiView()}; //Needed to force something more thorough than update and repaint
    const QImage image_before{dialog.GetUiView()};
    const QImage image_after{dialog.GetUiView()};
    QVERIFY(image_before == image_after);
  }
  if (verbose) { TRACE("If the head arrow head of an QtEdge its Edge is changed, the Item must be updated"); }
  {
    dialog.GetQtEdge()->GetEdge().SetHeadArrow(true);
    const QImage image_before{dialog.GetUiView()};
    dialog.GetQtEdge()->SetHasHeadArrow(false);
    const QImage image_after{dialog.GetUiView()};
    if(image_before == image_after)
    {
      image_before.save("tmp_before.png");
      image_after.save( "tmp_after.png");
      image_before.save("tmp.png");
    }
    QVERIFY(image_before != image_after);
  }
  if (verbose) { TRACE("If the tail arrow head of an QtEdge its Edge is changed, the Item must be updated"); }
  {
    dialog.GetQtEdge()->GetEdge().SetTailArrow(true);
    const QImage image_before{dialog.GetUiView()};
    dialog.GetQtEdge()->GetEdge().SetTailArrow(false);
    const QImage image_after{dialog.GetUiView()};
    QVERIFY(image_before != image_after);
  }
  if (verbose) { TRACE("If the source/'from' of an QtEdge is made invisible, this will show in a screenshot"); }
  {
    QVERIFY(dialog.m_from->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_from->setVisible(false);
    const QImage image_after{dialog.GetUiView()};
    QVERIFY(image_before != image_after);
  }
  if (verbose) { TRACE("If the target/'to' of an QtEdge is made invisible, this will show in a screenshot"); }
  {
    QVERIFY(dialog.m_to->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_to->setVisible(false);
    const QImage image_after{dialog.GetUiView()};
    QVERIFY(image_before != image_after);
  }
  if (verbose) { TRACE("If the QtNode an QtEdge is made invisible, this will show in a screenshot"); }
  {
    QVERIFY(dialog.m_qtedge_dialog->GetQtEdge()->GetQtNode()->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_qtedge_dialog->GetQtEdge()->GetQtNode()->setVisible(false);
    const QImage image_after{dialog.GetUiView()};
    QVERIFY(image_before != image_after);
  }
  if (verbose) { TRACE("If the source/'from' of an QtEdge its Edge is changed, the Item must be updated"); }
  {
    const boost::shared_ptr<QtRoundedEditRectItem> from{
      boost::dynamic_pointer_cast<QtRoundedEditRectItem>(dialog.m_from)
    };

    const QImage image_before{dialog.GetUiView()};
    from->setX(from->x() + 100.0);
    const QImage image_after{dialog.GetUiView()};
    //if (image_before != image_after)
    {
      image_before.save("QtTestQtEdgeDialogTest1_before.png");
      image_after.save("QtTestQtEdgeDialogTest1_after.png");
      const QImage result{QtImage().Difference(image_before,image_after)};
      result.save("QtTestQtEdgeDialogTest1_difference.png");
    }
    QVERIFY(image_before != image_after);
  }
  if (verbose) { TRACE("If the target/'to' of an QtEdge its Edge is changed by a member function, the Item must be updated"); }
  {
    const boost::shared_ptr<QtRoundedEditRectItem> to{
      boost::dynamic_pointer_cast<QtRoundedEditRectItem>(dialog.m_to)
    };

    const QImage image_before{dialog.GetUiView()};
    to->setX(to->x() + 100.0);
    const QImage image_after{dialog.GetUiView()};
    //if (image_before != image_after)
    {
      image_before.save("QtTestQtEdgeDialogTest1_before.png");
      image_after.save("QtTestQtEdgeDialogTest1_after.png");
      const QImage result{QtImage().Difference(image_before,image_after)};
      result.save("QtTestQtEdgeDialogTest1_difference.png");
    }
    QVERIFY(image_before != image_after);
  }
  if (verbose) { TRACE("If the target/'to' of an QtEdge its Edge is changed by a drag event, the Item must be updated"); }
  {
    const boost::shared_ptr<QtRoundedEditRectItem> to{
      boost::dynamic_pointer_cast<QtRoundedEditRectItem>(dialog.m_to)
    };
    const QImage image_before{dialog.GetUiView()};
    to->setX(to->x() + 100.0);
    const QImage image_after{dialog.GetUiView()};
    QVERIFY(image_before != image_after);
  }
  if (verbose) { TRACE("If QtNode of QtEdge is made visible, this will look different"); }
  {
    QVERIFY(!dialog.m_qtedge_dialog->GetQtEdge()->GetQtNode()->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_qtedge_dialog->GetQtEdge()->GetQtNode()->setVisible(true);
    const QImage image_after{dialog.GetUiView()};
    QVERIFY(image_before != image_after);
  }
  if (verbose) { TRACE("If arrow of QtEdge is made visible, this will look different"); }
  {
    QVERIFY(dialog.m_qtedge_dialog->GetQtEdge()->GetArrow()->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_qtedge_dialog->GetQtEdge()->GetArrow()->setVisible(false);
    const QImage image_after{dialog.GetUiView()};
    QVERIFY(image_before != image_after);
  }
}
*/
