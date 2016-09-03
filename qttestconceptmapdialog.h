#ifndef QTCONCEPTMAPTESTCONCEPTMAPEDITWIDGETDIALOG_H
#define QTCONCEPTMAPTESTCONCEPTMAPEDITWIDGETDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qttestconceptmappage.h"

#include "qtconceptmap.h"
#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

struct QTimer;
namespace Ui { class QtTestConceptMapDialog; }

namespace ribi {
namespace cmap {

///Tests all QtConceptMaps
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtTestConceptMapDialog : public QtPage
{
  Q_OBJECT
  
public:
  explicit QtTestConceptMapDialog(QWidget *parent = 0);
  QtTestConceptMapDialog(const QtTestConceptMapDialog&) = delete;
  QtTestConceptMapDialog& operator=(const QtTestConceptMapDialog&) = delete;
  ~QtTestConceptMapDialog() noexcept;

        QtConceptMap * GetQtConceptMap()       noexcept { return m_qtconceptmap; }
  const QtConceptMap * GetQtConceptMap() const noexcept { return m_qtconceptmap; }

  void keyPressEvent(QKeyEvent *);

private slots:

  void OnCheck();
  void OnVirtualBastard();

  void on_button_view_graphviz_summary_clicked();

  void on_button_view_graphviz_full_clicked();

  void on_box_run_virtual_bastard_stateChanged(int arg1);

  void on_box_mode_currentIndexChanged(int index);

  void on_button_set_concept_map_clicked();

private:

  Ui::QtTestConceptMapDialog *ui;

  ///The to-be-tested concept map
  QtConceptMap * m_qtconceptmap;

  QTimer * const m_timer_virtual_bastard;

  void DoSomethingRandom();
  void ToggleVirtualBastard() noexcept;
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPTESTCONCEPTMAPEDITWIDGETDIALOG_H
