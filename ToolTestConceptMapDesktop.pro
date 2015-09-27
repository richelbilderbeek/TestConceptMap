
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

include(../DesktopApplicationNoWeffcpp.pri)

#Libs
include(../Libraries/Apfloat.pri)
include(../Libraries/Boost.pri)
include(../Libraries/Fparser.pri)
include(../Libraries/GeneralConsole.pri)
include(../Libraries/GeneralDesktop.pri)

#Specific, console
include(../RibiClasses/CppContainer/CppContainer.pri)
include(../RibiClasses/CppCoordinat/CppCoordinat.pri)
include(../RibiClasses/CppCounter/CppCounter.pri)
include(../RibiClasses/CppConceptMap/CppConceptMap.pri)
include(../RibiClasses/CppGeometry/CppGeometry.pri)
include(../RibiClasses/CppGslLite/CppGslLite.pri)
include(../RibiClasses/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../RibiClasses/CppPlane/CppPlane.pri)
include(../RibiClasses/CppRibiRegex/CppRibiRegex.pri)
include(../RibiClasses/CppXml/CppXml.pri)

#Specific, desktop
include(../RibiClasses/CppGrabber/CppGrabber.pri)
include(../RibiClasses/CppQtArrowItem/CppQtArrowItem.pri)
include(../RibiClasses/CppQtConceptMap/CppQtConceptMap.pri)
include(../RibiClasses/CppQtDisplayPosItem/CppQtDisplayPosItem.pri)
include(../RibiClasses/CppQtKeyboardFriendlyGraphicsView/CppQtKeyboardFriendlyGraphicsView.pri)
include(../RibiClasses/CppQtQuadBezierArrowItem/CppQtQuadBezierArrowItem.pri)
include(../RibiClasses/CppQtImage/CppQtImage.pri)
include(../RibiClasses/CppQtRoundedEditRectItem/CppQtRoundedEditRectItem.pri)
include(../RibiClasses/CppQtRoundedRectItem/CppQtRoundedRectItem.pri)
include(../RibiClasses/CppQtScopedDisable/CppQtScopedDisable.pri)
include(ToolTestConceptMapDesktop.pri)

SOURCES += qtmain.cpp

