#ifndef QTCONCEPTMAPTESTEXAMPLESDIALOG_H
#define QTCONCEPTMAPTESTEXAMPLESDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <memory>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtTestExamplesDialog; }

namespace ribi {
namespace cmap {

class QtTestExamplesDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestExamplesDialog(QWidget *parent = 0);
  QtTestExamplesDialog(const QtTestExamplesDialog&) = delete;
  QtTestExamplesDialog& operator=(const QtTestExamplesDialog&) = delete;
  ~QtTestExamplesDialog() noexcept;

private slots:
  void keyPressEvent(QKeyEvent *event);
  void on_button_load_examples_clicked();
private:
  Ui::QtTestExamplesDialog *ui;
  std::unique_ptr<QtExamplesDialog> m_examples;


};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPTESTEXAMPLESDIALOG_H
