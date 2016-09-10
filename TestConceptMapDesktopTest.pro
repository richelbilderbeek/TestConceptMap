include(../RibiLibraries/DesktopApplicationNoWeffcpp.pri)

CONFIG += debug_and_release

#Libs
include(../RibiLibraries/Apfloat.pri)
include(../RibiLibraries/BoostAll.pri)
include(../RibiLibraries/Fparser.pri)
include(../RibiLibraries/GeneralConsole.pri)
include(../RibiLibraries/GeneralDesktop.pri)
#include(../RibiLibraries/Sfml.pri)

#Specific, console
include(../ConceptMap/ConceptMap.pri)
include(../RibiClasses/CppContainer/CppContainer.pri)
include(../RibiClasses/CppCounter/CppCounter.pri)
include(../RibiClasses/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../RibiClasses/CppGeometry/CppGeometry.pri)
include(../RibiClasses/CppGslLite/CppGslLite.pri)
include(../RibiClasses/CppPlane/CppPlane.pri)
include(../RibiClasses/CppRibiRegex/CppRibiRegex.pri)
include(../RibiClasses/CppRibiSystem/CppRibiSystem.pri)
include(../RibiClasses/CppRibiTime/CppRibiTime.pri)
include(../RibiClasses/CppXml/CppXml.pri)

#Specific, desktop
include(../RibiClasses/CppGrabber/CppGrabber.pri)
include(../RibiClasses/CppGrabber/CppGrabberTest.pri)
include(../RibiClasses/CppQtArrowItem/CppQtArrowItem.pri)
include(../RibiClasses/CppQtArrowItem/CppQtArrowItemTest.pri)

include(../QtConceptMap/QtConceptMap.pri)
include(../RibiClasses/CppQtDisplayPosItem/CppQtDisplayPosItem.pri)
include(../RibiClasses/CppQtKeyboardFriendlyGraphicsView/CppQtKeyboardFriendlyGraphicsView.pri)
include(../RibiClasses/CppQtQuadBezierArrowItem/CppQtQuadBezierArrowItem.pri)
include(../RibiClasses/CppQtImage/CppQtImage.pri)
include(../RibiClasses/CppQtRoundedEditRectItem/CppQtRoundedEditRectItem.pri)
include(../RibiClasses/CppQtRoundedRectItem/CppQtRoundedRectItem.pri)
include(../RibiClasses/CppQtScopedDisable/CppQtScopedDisable.pri)

include(TestConceptMapDesktop.pri)
include(TestConceptMapDesktopTest.pri)

include(../BoostGraphTutorial/BoostGraphTutorial/boost_graph_tutorial.pri)

SOURCES += qtmain_test.cpp

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

# gprof
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

# QResources give this error
QMAKE_CXXFLAGS += -Wno-unused-variable

# Qt:
# QtConcurrent::filterInternal(Sequence&, KeepFunctor, ReduceFunctor)’:
# /usr/include/qt4/QtCore/qtconcurrentfilter.h:108:47: error: typedef ‘Iterator’ locally defined but not used [-Werror=unused-local-typedefs]
# typedef typename Sequence::const_iterator Iterator;
QMAKE_CXXFLAGS += -Wno-unused-local-typedefs

# QTest
QT += testlib
