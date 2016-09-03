#ifndef QTTESTCONCEPTMAPPAGE_H
#define QTTESTCONCEPTMAPPAGE_H

#include <QDialog>

namespace ribi {
namespace cmap {

///Base class for all dialogs displayed within the Master Dialog
class QtPage : public QDialog
{
  Q_OBJECT
public:
  explicit QtPage(QWidget *parent = 0);

protected:

  void closeEvent(QCloseEvent *);

signals:

  ///The Dialog creates another QDialog
  ///Ownership of dialog will be of MasterDialog
  void add_me(QDialog * const dialog) const;

  ///This Dialog signals to be removed, by emitting 'this'
  void remove_me(QDialog * const dialog) const;

public slots:

};

} //~namespace cmap
} //~namespace ribi

#endif // QTTESTCONCEPTMAPPAGE_H
