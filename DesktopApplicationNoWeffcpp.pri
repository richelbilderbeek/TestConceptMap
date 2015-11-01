# -Weffc++ does not go with apfloat, Qwt

win32 {
  # Windows only
  message("Desktop application, no effc++, built for Windows")
  greaterThan(QT_MAJOR_VERSION, 4): QT += svg
  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra #-Weffc++
}

macx {
  # Mac only
  message("Desktop application, no effc++, built for Mac")
  QMAKE_CXXFLAGS = -mmacosx-version-min=10.7 -std=gnu0x -stdlib=libc+
  CONFIG +=c++1y
}

unix:!macx{
  # Linux only
  message("Desktop application, no effc++, built for Linux")
  equals(QT_MAJOR_VERSION, 4): LIBS +=  -lQtSvg
  greaterThan(QT_MAJOR_VERSION, 4): QT +=  concurrent opengl printsupport svg

  message(Host name: $$QMAKE_HOST.name)
  contains(QMAKE_HOST.name,fwn-biol-132-102) {
    message("C++1y: Host is university computer")
    QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra #-Werror
  }
  contains(QMAKE_HOST.name,pg-login) {
    message("C++1y: Host is Peregrine cluster")
    QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra #-Werror
  }
  contains(QMAKE_HOST.name,maakplek-PC6-lubuntu) {
    message("C++17: Host is home computer")
    QMAKE_CXXFLAGS += -std=c++17 -Wall -Wextra #-Werror
  }
}

cross_compile {
  # Crosscompile only
  message("Desktop application, no effc++, cross-compiling from Linux to Windows")
  greaterThan(QT_MAJOR_VERSION, 4): QT += svg
  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra #-Weffc++
}


QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}


