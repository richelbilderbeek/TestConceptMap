include(../RibiLibraries/ConsoleApplicationNoWeffcpp.pri)
include(../RibiLibraries/Apfloat.pri)
include(../RibiLibraries/Boost.pri)
include(../RibiLibraries/GeneralConsole.pri)

#Specific, console
include(../RibiClasses/CppContainer/CppContainer.pri)
#include(../RibiClasses/CppCoordinat/CppCoordinat.pri)
include(../RibiClasses/CppCounter/CppCounter.pri)
include(../ConceptMap/ConceptMap.pri)
include(../RibiClasses/CppGeometry/CppGeometry.pri)
include(../RibiClasses/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../plane/plane.pri)
include(../RibiClasses/CppRibiRegex/CppRibiRegex.pri)
include(../RibiClasses/CppXml/CppXml.pri)

include(../BoostGraphTutorial/BoostGraphTutorial/boost_graph_tutorial.pri)

#Specific
include(../TestConceptMap/TestConceptMapConsole.pri)
SOURCES += main.cpp

# gcov
# QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
# QMAKE_LFLAGS += -lgcov -coverage

LIBS += -lboost_graph

# QResources give this error
QMAKE_CXXFLAGS += -Wno-unused-variable

# Prevents this error:
#/usr/include/boost/math/constants/constants.hpp:277: error: unable to find numeric literal operator 'operator""Q'
#   BOOST_DEFINE_MATH_CONSTANT(half, 5.000000000000000000000000000000000000e-01, "5.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-01")
#   ^
QMAKE_CXXFLAGS += -fext-numeric-literals
