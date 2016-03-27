#!/bin/bash
qmake TestConceptMapDesktop.pro
make
# Don't run on Travis
# ./TestConceptMapDesktop
