#ifndef QTCONCEPTMAPTESTCONCEPTDIALOG_H
#define QTCONCEPTMAPTESTCONCEPTDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtTestConceptDialog; }

namespace ribi {
namespace cmap {

///Tests all QtConceptMapConceptItem items, especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtTestConceptDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestConceptDialog(QWidget *parent = 0);
  QtTestConceptDialog(const QtTestConceptDialog&) = delete;
  QtTestConceptDialog& operator=(const QtTestConceptDialog&) = delete;
  ~QtTestConceptDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *event);
  
private slots:

  void on_button_load_clicked();

private:
  Ui::QtTestConceptDialog *ui;

  boost::shared_ptr<QtConceptDialog> m_qtconceptdialog;


  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap

} //~namespace ribi

#endif // QTCONCEPTMAPTESTCONCEPTDIALOG_H
