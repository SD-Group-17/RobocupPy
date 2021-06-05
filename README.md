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
* this is an example on how you can call on a python file. to check if it has imported you can put pModule in an if statement
```C++
if(pModule)
	{
		PyObject * pFunc = PyObject_GetAttrString(pModule, "selectSkill"); 
       
		if(pFunc && PyCallable_Check(pFunc))
		{
            //TODO, below function should not take "i", should take something else representing a PyList
            PyObject * pReturn = PyObject_CallFunction(pFunc,"O",world_data);
            int x = (int) PyLong_AsLong(pReturn);
			return x;
		}
		else
		{
            
			cout << "ERROR: function selectSkill()\n"<<endl;
            return -1;
		}

	}
	else
	{
        
		cout << "ERROR: Module not imported"<<endl;
        return -2;
	}
```
