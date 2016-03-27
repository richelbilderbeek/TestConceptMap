#include "testconceptmapmenudialog.h"

#include <iostream>
#include <stdexcept>
#include <sstream>

#include "conceptmap.h"
#include "xml.h"

int main(int argc, char * argv[])
{
  try
  {
    const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
    return ribi::TestConceptMapMenuDialog().Execute(args);
  }
  catch (std::exception& e)
  {
    std::stringstream msg;
    msg << "Program terminated by exception '" << e.what() << "'";
    std::cout << msg.str() << std::endl;
    return 1;
  }
}
