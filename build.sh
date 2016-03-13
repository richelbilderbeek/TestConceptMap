#!/bin/bash
cd ..
pwd
ls
git clone https://github.com/richelbilderbeek/RibiClasses
git clone https://github.com/richelbilderbeek/RibiLibraries
cd RibiLibraries; ./fparser.sh; cd ..
cd RibiLibraries; ./Apfloat.sh; cd ..
cd TestConceptMap
ls
pwd
qmake TestConceptMapConsole.pro
make
qmake TestConceptMapDesktop.pro
make
