#include "qttesteditconceptmapdialog.h"
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

QKeyEvent CreateCtrlE() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_E,Qt::ControlModifier); }
QKeyEvent CreateCtrlLeft() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::ControlModifier); }
QKeyEvent CreateCtrlN() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_N,Qt::ControlModifier); }
QKeyEvent CreateCtrlRight() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Right,Qt::ControlModifier); }
QKeyEvent CreateDelete() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Delete,Qt::NoModifier); }
QKeyEvent CreateDown() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Down,Qt::NoModifier); }
QKeyEvent CreateE() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_E,Qt::NoModifier); }
QKeyEvent CreateLeft() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::NoModifier); }
QKeyEvent CreateN() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_N,Qt::NoModifier); }
QKeyEvent CreateRight() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Right,Qt::NoModifier); }
QKeyEvent CreateShiftE() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_E,Qt::ShiftModifier); }
QKeyEvent CreateShiftLeft() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::ShiftModifier); }
QKeyEvent CreateShiftN() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_N,Qt::ShiftModifier); }
QKeyEvent CreateShift() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Shift,Qt::NoModifier); }
QKeyEvent CreateShiftRight() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Right,Qt::ShiftModifier); }
QKeyEvent CreateSpace() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Space,Qt::NoModifier); }
QKeyEvent CreateUp() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Up,Qt::NoModifier); }
QKeyEvent CreateX() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_X,Qt::NoModifier); }

BOOST_AUTO_TEST_CASE(ribi_cmap_qttesteditconceptmapdialog_default_construction)
{
  ribi::cmap::QtTestEditConceptMapDialog d;
  d.show();
  //Without 'qApp->processEvents()' the dialog is not drawn well
  for (int i=0; i!=1000000; ++i) { qApp->processEvents(); }
  BOOST_CHECK_EQUAL(boost::num_vertices(d.GetQtConceptMap()->GetConceptMap()), 0);
  d.close();
}

BOOST_AUTO_TEST_CASE(ribi_cmap_qttesteditconceptmapdialog_create_node)
{
  ribi::cmap::QtTestEditConceptMapDialog d;
  d.show();
  d.setFocus();
  for (int i=0; i!=1000000; ++i) { qApp->processEvents(); }
  {
    auto key = CreateCtrlN();
    d.keyPressEvent(&key);
  }
  d.GetQtConceptMap()->setFocus();
  for (int i=0; i!=1000000; ++i) { qApp->processEvents(); }
  {
    auto key = CreateCtrlN();
    d.keyPressEvent(&key);
  }
  d.update();
  for (int i=0; i!=1000000; ++i) { qApp->processEvents(); }
  {
    auto key = CreateCtrlN();
    d.keyPressEvent(&key);
  }
  for (int i=0; i!=1000000; ++i) { qApp->processEvents(); }
  BOOST_CHECK_EQUAL(boost::num_vertices(d.GetQtConceptMap()->GetConceptMap()), 1);
  d.close();
}
