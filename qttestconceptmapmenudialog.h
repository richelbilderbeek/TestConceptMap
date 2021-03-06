#ifndef QTTESTCONCEPTAMPMENUDIALOG_H
#define QTTESTCONCEPTAMPMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <vector>
#include "qttestconceptmappage.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestMenuDialog;
}

namespace ribi {
namespace cmap {

class QtTestMenuDialog : public QtPage
{
  Q_OBJECT

public:
  explicit QtTestMenuDialog(QWidget *parent = 0);
  QtTestMenuDialog(const QtTestMenuDialog&) = delete;
  QtTestMenuDialog& operator=(const QtTestMenuDialog&) = delete;
  ~QtTestMenuDialog() noexcept;

  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_about_clicked();
  void on_button_edit_conceptmap_clicked();
  void on_button_quit_clicked();
  void on_button_view_conceptmaps_clicked();

private:
  Ui::QtTestMenuDialog *ui;
};

} //~namespace cmap
} //~namespace ribi

#endif // QTTESTCONCEPTAMPMENUDIALOG_H
