##  readme
*   . . .
*   how to build external rexx functions using cmake
*   classic and native
*   . . .
*   will support  : MACOS[x], Linux, FreeBSD, OpenBSD
*   . . .
* * *

##  copyright
*   . . .
*   Copyright (c) Enrico Sorichetti 2018 - 2019
*   Distributed under the Boost Software License, Version 1.0.
*   See accompanying file LICENSE\_1\_0.txt or copy at
*   [http://www.boost.org/LICENSE\_1\_0.txt](http://www.boost.org/LICENSE\_1\_0.txt)
*   . . .
* * *

##  how to get it
*   . . .
*   git clone http://00003481@bitbucket.org/00003481/rxSnippets
*   . . .
*   NOTE
*   the repository name casing is a bit tricky
*   it is displayed with the casing used when creating it
*   but in the BitBucket remote store it is in lower case
*   as seen when clicking on the clone button
*   when cloning the name casing will be irrelevant for the remote repository
*   but it will be the casing used for the local repository
*   . . .
* * *

##  usage notes
*   . . .
*   clone anywhere with any name
*   mkdir  'the build directory'
*   cd  'the build directory'
*   cmake -DOOREXX_INSTALL_PREFIX='the prefix oYour ooRexx installation" 'the source dir'
*   make
*   export LD_LIBRARY_PATH=`pwd`    <=== not needed on Darwin
*   rexx rxClassic
*   rexx rxNative
*   . . .
*   I wrote a minimalist CMakeList  which also does the job and is now the default
*   the CMakeLists.txt is just a copy of CMakeLists.txt.minimalist
*   . . .
*   to see what a more sophisticated approach might look like
*   just ...
*   cp CMakeLists.txt.platinum CMakeLists.txt
*   and rerun the whole build process
*   . . .
*   let me know if I forgot something
*   . . .
*   for non unix-like directory structures
*   added -DOOREXX_INCLUDE_DIR=...
*   added -DOOREXX_LIB_DIR=...
*   . . .
* * *
-DOOREXX_INLUDE_DIR=... -DOOREXX_LIB_DIR=... for the include/lib directories"

##  supported environments
*   . . .
*   macOS[X] El Capitan, High Sierra, Mojave
*   Linux, FreeBSD, OpenBSD
*   . . .
* * *

##  dependencies
*   . . .
* * *

##  nice to have
*   . . .
*   ccache  - a C/C++ compiler cache
*   ninja   - alternative for make/gmake ( macOS/Linux/FreeBSD )
*   pkgconf - to retrieve the metainformation of a package/library
*   . . .
* * *

##  contribution guidelines
*   . . .
*   Comments welcome
*   Suggestions welcome
*   . . .
*   but remember ... My repository, my rules :-)
*   . . .
* * *

##  other
*   [Markdown Information](https://bitbucket.org/tutorials/markdowndemo)
* * *

