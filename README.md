# RobocupPy
[![Build Status](https://travis-ci.org/SD-Group-17/RobocupPy.svg?branch=core_test)](https://travis-ci.org/SD-Group-17/RobocupPy) [![codecov](https://codecov.io/gh/SD-Group-17/RobocupPy/branch/core_test/graph/badge.svg)](https://codecov.io/gh/SD-Group-17/RobocupPy)

RobocupPy is a wrapper for the UT Austin Villa Codebase that allows you to use python for Robocup.

## Documentation:
* Open [html file](https://github.com/SD-Group-17/RobocupPy/tree/core_test/Documentation/html) using a browser
* [Wiki](https://github.com/SD-Group-17/RobocupPy/wiki)
  * [Robocup Class Documentation](https://github.com/SD-Group-17/RobocupPy/wiki/Robocup-Class-Documentation)
  * [UML Diagrams](https://github.com/SD-Group-17/RobocupPy/wiki/UML)

## Installation
* installtion of Robocup instructions can be found here [(Robocup Install Guide)](https://courses.ms.wits.ac.za/~branden/RoboCup/install-intro.html)


## How to wrap more data for python
* To see these techniques in use view [Strategy.cc](https://github.com/SD-Group-17/RobocupPy/blob/core_test/Code_Base/behaviors/strategy.cc). the pyFunction.
* the first command that must be run before using or calling python Scripts or PyObjects is Py_Initialize(). this function basically creates a python interpreter to run python commands and files
* to run a python command use the following command PyRun_SimpleString("import os"). in this example here we are importing the os library to interpreter.
`PyObject *  pName = PyUnicode_FromString("strategyPy");
	PyObject * pModule = PyImport_Import(pName);`
