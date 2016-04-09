#include "testconceptmapmenudialog.h"

#include <cassert>
#include <iostream>


#include "conceptmap.h"
#include "conceptmapfactory.h"

#include "container.h"
#include "fileio.h"
#include "geometry.h"
#include "plane.h"
#include "ribi_regex.h"
#include "testtimer.h"
#include "trace.h"

ribi::TestConceptMapMenuDialog::TestConceptMapMenuDialog()
{

}

int ribi::TestConceptMapMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 0;
  }
  std::cout << "This application does not have a console mode\n";
  return 0;
}

ribi::About ribi::TestConceptMapMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestConceptMap",
    "tests the ConceptMap classes",
    "on the 2nd of October 2015",
    "2013-2015",
    "http://www.richelbilderbeek.nl/ToolTestConceptMap.htm",
    GetVersion(),
    GetVersionHistory());

  a.AddLibrary("apfloat version: 2.4.1");
  //a.AddLibrary("ConceptMap version: " + ribi::cmap::ConceptMap::GetVersion());
  a.AddLibrary("Container version: " + ribi::Container().GetVersion());
  a.AddLibrary("FileIo version: " + FileIo().GetVersion());
  a.AddLibrary("Geometry version: " + Geometry().GetVersion());
  a.AddLibrary("ribi::Regex version: " + Regex().GetVersion());
  a.AddLibrary("Plane version: " + Plane::GetVersion());
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());

  return a;
}

ribi::Help ribi::TestConceptMapMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

std::string ribi::TestConceptMapMenuDialog::GetVersion() const noexcept
{
  return "1.3";
}

std::vector<std::string> ribi::TestConceptMapMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-12-03: version 1.0: initial version",
    "2014-05-18: version 1.1: added testing Example",
    "2014-08-07: version 1.2: increased use of TDD"
    "2015-10-02: version 1.3: moved to own GitHub"
  };
}
