#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QApplication>
#include "qttestconceptmapmasterdialog.h"
#include "qttestconceptmapmenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::cmap::QtMasterDialog w;
  w.add_new(new ribi::cmap::QtTestMenuDialog);
  w.setWindowState(Qt::WindowFullScreen);
  w.show();
  return a.exec();
}
