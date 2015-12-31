#ifndef QTCONCEPTMAPTESTEDGEDIALOG_H
#define QTCONCEPTMAPTESTEDGEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#include "qtconceptmapfwd.h"
#include "conceptmapnode.h"
#pragma GCC diagnostic pop

namespace Ui { class QtTestEdgeDialog; }

namespace ribi {
namespace cmap {

///Tests all QtConceptMapConceptItem items, especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtTestEdgeDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestEdgeDialog(QWidget *parent = 0);
  QtTestEdgeDialog(const QtTestEdgeDialog&) = delete;
  QtTestEdgeDialog& operator=(const QtTestEdgeDialog&) = delete;
  ~QtTestEdgeDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *event);
  
private slots:

  void on_button_load_clicked();

private:
  Ui::QtTestEdgeDialog *ui;

  Node m_from_node;
  QtEdgeDialog * m_qtedgedialog;
  Node m_to_node;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap

} //~namespace ribi

#endif // QTCONCEPTMAPTESTEDGEDIALOG_H
