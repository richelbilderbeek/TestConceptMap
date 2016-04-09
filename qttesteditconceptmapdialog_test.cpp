#include "qttesteditconceptmapdialog_test.h"

#include <iostream>

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <QtTest>
#include <QDesktopWidget>
#include <QGraphicsView>
#include <QKeyEvent>

#include "conceptmapcompetencies.h"
#include "qttesteditconceptmapdialog.h"
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

void ribi::qttesteditconceptmapdialog_test::create_node()
{
  ribi::cmap::QtTestEditConceptMapDialog d;
  d.show();
  d.setFocus();
  {
    auto key = CreateCtrlN();
    d.keyPressEvent(&key);
  }
  d.GetQtConceptMap()->setFocus();
  {
    auto key = CreateCtrlN();
    d.keyPressEvent(&key);
  }
  d.update();
  {
    auto key = CreateCtrlN();
    d.keyPressEvent(&key);
  }
  const auto excepted_vertices = 1;
  const auto measured_vertices = boost::num_vertices(d.GetQtConceptMap()->GetConceptMap());
  if (measured_vertices != excepted_vertices)
  {
    std::cerr << __func__ << ": "
      << "expected: " << excepted_vertices << ", "
      << "measured: " << measured_vertices << '\n'
    ;
  }
  QVERIFY(measured_vertices == excepted_vertices);
  d.close();
}
