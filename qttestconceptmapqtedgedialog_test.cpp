#ifdef NOT_NOW_20151230
void ribi::cmap::QtTestQtEdgeDialog::Test() noexcept
{
  {
    QtImage();
  }
  const TestTimer test_timer(__func__,__FILE__,2.0);
  const bool verbose{false};
  QtTestQtEdgeDialog dialog;
  const boost::shared_ptr<QtEdge> qtedge{dialog.GetQtEdge()};
  const int n = dialog.ui->box_test_index->maximum();
  if (verbose) { TRACE("Number of tests in GUI must be equal to the number of actual tests"); }
  {
    assert(n == QtEdgeFactory().GetNumberOfTests() - 1
      && "If there are x tests, the maximum test index is x-1");
  }
  if (verbose) { TRACE("Test index in GUI must be lower than the number of actual tests"); }
  {
    for (int i=0; i!=10; ++i)
    {
      dialog.ui->box_test_index->setValue(i);
      assert(dialog.GetUiTestIndex() < QtEdgeFactory().GetNumberOfTests());
    }
  }
  if (verbose) { TRACE("Setting all test edges"); }
  {
    //QtTestQtEdgeDialog dialog;
    const int n{QtEdgeFactory().GetNumberOfTests()};
    for (int i=0; i!=n; ++i)
    {
      dialog.ui->box_test_index->setValue(i);
      dialog.on_button_load_clicked();
    }
  }
  dialog.SetQtEdge(qtedge); //Put QtEdge in back again
  if (verbose) { TRACE("There are items in the QGraphicsView"); }
  {
    assert(dialog.m_qtedge_view->items().size() >= 3);
  }
  if (verbose) { TRACE("Grabbing QtEdge of QGraphicsView twice, results in an identical picture"); }
  {
    //If the line below is needed, update() is not called automatically
    const QImage image_tmp{dialog.GetUiView()}; //Needed to force something more thorough than update and repaint
    const QImage image_before{dialog.GetUiView()};
    const QImage image_after{dialog.GetUiView()};
    assert(image_before == image_after);
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
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the tail arrow head of an QtEdge its Edge is changed, the Item must be updated"); }
  {
    dialog.GetQtEdge()->GetEdge().SetTailArrow(true);
    const QImage image_before{dialog.GetUiView()};
    dialog.GetQtEdge()->GetEdge().SetTailArrow(false);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the source/'from' of an QtEdge is made invisible, this will show in a screenshot"); }
  {
    assert(dialog.m_from->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_from->setVisible(false);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the target/'to' of an QtEdge is made invisible, this will show in a screenshot"); }
  {
    assert(dialog.m_to->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_to->setVisible(false);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the QtNode an QtEdge is made invisible, this will show in a screenshot"); }
  {
    assert(dialog.m_qtedge_dialog->GetQtEdge()->GetQtNode()->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_qtedge_dialog->GetQtEdge()->GetQtNode()->setVisible(false);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
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
    assert(image_before != image_after);
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
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If the target/'to' of an QtEdge its Edge is changed by a drag event, the Item must be updated"); }
  {
    const boost::shared_ptr<QtRoundedEditRectItem> to{
      boost::dynamic_pointer_cast<QtRoundedEditRectItem>(dialog.m_to)
    };

    const QImage image_before{dialog.GetUiView()};
    to->setX(to->x() + 100.0);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If QtNode of QtEdge is made visible, this will look different"); }
  {
    assert(!dialog.m_qtedge_dialog->GetQtEdge()->GetQtNode()->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_qtedge_dialog->GetQtEdge()->GetQtNode()->setVisible(true);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
  if (verbose) { TRACE("If arrow of QtEdge is made visible, this will look different"); }
  {
    assert(dialog.m_qtedge_dialog->GetQtEdge()->GetArrow()->isVisible());
    const QImage image_before{dialog.GetUiView()};
    dialog.m_qtedge_dialog->GetQtEdge()->GetArrow()->setVisible(false);
    const QImage image_after{dialog.GetUiView()};
    assert(image_before != image_after);
  }
}
#endif //NOT_NOW_20151230
