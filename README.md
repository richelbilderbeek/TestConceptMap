# TestConceptMap

TestConceptMap is a tool to test ConceptMap classes

## Building

In the same folder, clone multiple GitHubs:

```
git clone https://github.com/richelbilderbeek/RibiClasses
git clone https://github.com/richelbilderbeek/TestConceptMap
git clone https://github.com/richelbilderbeek/RibiLibraries
```

Within the `TestConceptMap` folder, 

 * Desktop: Open the Qt Creator project file `TestConceptMapDesktop.pro` in Qt Creator and build
 * Console: Open the Qt Creator project file `TestConceptMapConsole.pro` in Qt Creator and build. This project is more for debugging purposes of the program logic

If you do not use Qt Creator, you can build the project using `qmake` and `make` like this:

```
qmake TestConceptMapDesktop.pro
make
```

## Help

Building doesn't work and the error messages are unclear? I'd be happy if you'd let me know :-)
