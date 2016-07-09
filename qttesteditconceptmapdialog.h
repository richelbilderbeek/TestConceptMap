#ifndef QTCONCEPTMAPTESTCONCEPTMAPEDITWIDGETDIALOG_H
#define QTCONCEPTMAPTESTCONCEPTMAPEDITWIDGETDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmap.h"
#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

struct QTimer;
namespace Ui { class QtTestEditConceptMapDialog; }

namespace ribi {
namespace cmap {

///Tests all QtConceptMaps
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtTestEditConceptMapDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestEditConceptMapDialog(QWidget *parent = 0);
  QtTestEditConceptMapDialog(const QtTestEditConceptMapDialog&) = delete;
  QtTestEditConceptMapDialog& operator=(const QtTestEditConceptMapDialog&) = delete;
  ~QtTestEditConceptMapDialog() noexcept;

        QtConceptMap * GetQtConceptMap()       noexcept { return m_qtconceptmap; }
  const QtConceptMap * GetQtConceptMap() const noexcept { return m_qtconceptmap; }

  void keyPressEvent(QKeyEvent *);

private slots:

  void OnCheck();
  void OnVirtualBastard();

  void on_button_view_graphviz_summary_clicked();

  void on_button_view_graphviz_full_clicked();

private:

  Ui::QtTestEditConceptMapDialog *ui;

  ///The to-be-tested concept map
  QtConceptMap * m_qtconceptmap;

  QTimer * const m_timer_virtual_bastard;

  void DoSomethingRandom();
  void ToggleVirtualBastard() noexcept;
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPTESTCONCEPTMAPEDITWIDGETDIALOG_H
