#ifndef QTCONCEPTMAPVIEWTESTSDIALOG_H
#define QTCONCEPTMAPVIEWTESTSDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qttestconceptmappage.h"

#include "qtconceptmap.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtConceptMapViewTestsDialog;
}

namespace ribi {
namespace cmap {

class QtConceptMapViewTestsDialog : public QtPage
{
  Q_OBJECT
  
public:
  explicit QtConceptMapViewTestsDialog(QWidget* parent = 0);
  QtConceptMapViewTestsDialog(const QtConceptMapViewTestsDialog&) = delete;
  QtConceptMapViewTestsDialog& operator=(const QtConceptMapViewTestsDialog&) = delete;
  ~QtConceptMapViewTestsDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent* event);
  
private:
  Ui::QtConceptMapViewTestsDialog *ui;

  const std::vector<ConceptMap> m_concept_maps;

  /// Tha widgets
  std::vector<boost::shared_ptr<QtConceptMap>> m_qtconceptmaps;

  static boost::shared_ptr<QtConceptMap> CreateWidget(
    const ConceptMap conceptmap);
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPVIEWTESTSDIALOG_H
