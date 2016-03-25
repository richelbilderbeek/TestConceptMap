#!/bin/bash
cd ..
git clone https://github.com/richelbilderbeek/BoostGraphTutorial
git clone https://github.com/richelbilderbeek/RibiClasses
git clone https://github.com/richelbilderbeek/RibiLibraries
cd RibiLibraries; ./fparser.sh; cd ..
cd RibiLibraries; ./Apfloat.sh; cd ..
cd TestConceptMap
qmake TestConceptMapConsole.pro
make
qmake TestConceptMapDesktop.pro
make
