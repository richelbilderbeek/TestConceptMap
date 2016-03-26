#ifndef QTCONCEPTMAPTESTQTEDGEDIALOG_H
#define QTCONCEPTMAPTESTQTEDGEDIALOG_H

#ifdef NOT_NOW_20151230

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <memory>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#include "qtconceptmapqtedge.h"
#include "qtconceptmapqtnode.h"
#pragma GCC diagnostic pop

namespace Ui { class QtTestQtEdgeDialog; }

namespace ribi {
namespace cmap {

///Tests all QtConceptMapConceptItem items when being a member of a cmap::QtEdge,
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtTestQtEdgeDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:

public:
  explicit QtTestQtEdgeDialog(QWidget *parent = 0);
  QtTestQtEdgeDialog(const QtTestQtEdgeDialog&) = delete;
  QtTestQtEdgeDialog& operator=(const QtTestQtEdgeDialog&) = delete;
  ~QtTestQtEdgeDialog() noexcept;

  boost::shared_ptr<QtEdge> GetQtEdge() const noexcept;

  ///Obtain the GUI's value of test index. This might differ from
  ///the currently active test, as the user needs to press 'Load Test'
  ///to make it active
  int GetUiTestIndex() const noexcept;

  QImage GetUiView() const noexcept;

  //Obtain the X coordinat of the Node on the Edge from the GUI
  double GetUiX() const noexcept;
  //Obtain the Y coordinat of the Node on the Edge from the GUI
  double GetUiY() const noexcept;

  void SetQtEdge(const boost::shared_ptr<QtEdge>& qtnode) noexcept;


protected:

  void keyPressEvent(QKeyEvent *) noexcept override final;

private slots:

  void on_button_load_clicked() noexcept;

private:

  Ui::QtTestQtEdgeDialog *ui;


  std::unique_ptr<QtQtEdgeDialog> m_qtedge_dialog;
  const boost::shared_ptr<QtNode> m_from;
  const boost::shared_ptr<QtNode> m_to;
  std::unique_ptr< ::ribi::QtKeyboardFriendlyGraphicsView> m_qtedge_view;
};

} //~namespace cmap

} //~namespace ribi

#endif //NOT_NOW_20151230

#endif // QTCONCEPTMAPTESTQTEDGEDIALOG_H


