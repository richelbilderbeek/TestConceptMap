include(../RibiLibraries/ConsoleApplication.pri)
include(../RibiLibraries/Apfloat.pri)
include(../RibiLibraries/Boost.pri)
include(../RibiLibraries/GeneralConsole.pri)

#Specific, console
include(../RibiClasses/CppContainer/CppContainer.pri)
include(../RibiClasses/CppCoordinat/CppCoordinat.pri)
include(../RibiClasses/CppCounter/CppCounter.pri)
include(../RibiClasses/CppConceptMap/CppConceptMap.pri)
include(../RibiClasses/CppGeometry/CppGeometry.pri)
include(../RibiClasses/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../RibiClasses/CppPlane/CppPlane.pri)
include(../RibiClasses/CppRibiRegex/CppRibiRegex.pri)
include(../RibiClasses/CppXml/CppXml.pri)

#Specific
include(../TestConceptMap/TestConceptMapConsole.pri)
SOURCES += main.cpp

# gcov
# QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
# QMAKE_LFLAGS += -lgcov -coverage

LIBS += -lboost_graph
