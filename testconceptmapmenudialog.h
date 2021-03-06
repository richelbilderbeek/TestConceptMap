#ifndef TESTCONCEPTMAPMENUDIALOG_H
#define TESTCONCEPTMAPMENUDIALOG_H

#include "menudialog.h"

namespace ribi {

///GUI independent TestConceptMap menu dialog
struct TestConceptMapMenuDialog final : public MenuDialog
{
  TestConceptMapMenuDialog();
  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;
};

} //~namespace ribi

#endif // TESTCONCEPTMAPMENUDIALOG_H
