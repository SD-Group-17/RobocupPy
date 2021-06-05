# RobocupPy
[![Build Status](https://travis-ci.org/SD-Group-17/RobocupPy.svg?branch=core_test)](https://travis-ci.org/SD-Group-17/RobocupPy) [![codecov](https://codecov.io/gh/SD-Group-17/RobocupPy/branch/core_test/graph/badge.svg)](https://codecov.io/gh/SD-Group-17/RobocupPy)

RobocupPy is a wrapper for the UT Austin Villa Codebase that allows you to use python for Robocup.

## Documentation:
* Open [html file](https://github.com/SD-Group-17/RobocupPy/tree/core_test/Documentation/html) using a browser
* [Wiki](https://github.com/SD-Group-17/RobocupPy/wiki)
  * [Robocup Class Documentation](https://github.com/SD-Group-17/RobocupPy/wiki/Robocup-Class-Documentation)
  * [UML Diagrams](https://github.com/SD-Group-17/RobocupPy/wiki/UML)

## Installation
### (Singularity)
This is a quick instruction guide on how to install the Robocup distribution on your home computer.

Make sure you are connected to the internet as this will require a once off ~300mb download
this is a setup for debian based systems. to run this on windows download WSL. more info can be found [here](https://docs.microsoft.com/en-us/windows/wsl/about)
* Open a terminal
* Type the command and run it
```
wget lamp.ms.wits.ac.za/robocup/setup
```
* It may appear to hang, however, I found it was asking for my password. So input your password when/if prompted
* Once complete if you type ‘ls’ you should see a file called ‘setup’
* Type the command and run it
```
 chmod +x setup
```
* Type the command and run it (This process will install quite a few things)
```
  ./setup
```
* You will be prompted on whether or not you have a graphics card type “Y” or “N”. If you are unsure of if you have one you can run “nvidia-smi”, this will indicate if you have nvidia drivers installed. If it asks to install something then you don’t have nvidia drivers :)

* Based upon which option you chose in Step 7 you will be told which command you require to run the singularity instance.

```
    - IF no "N" in step 7 run ./robocup-mesa
    - IF yes "Y" in step 7 run ./robocup-nvidia
```
A new terminal should have opened which is within the singularity robocup instance

* In this new terminal you can run the server using the following command
```
 rcssserver3d
```
This will run the server like we have done in the labs
* Type “ctrl-shift-t” while the terminal is active(selected) to open a new tab. Remember we need to run each of the server, agent and visualiser in a serperate tab
* In the new tab run the following command to run the visualiser - which will open the roboviz window
```
 /roboviz/roboviz.sh
```

* Type “ctrl-shift-t” to open a third tab
* In order to run the agent we must first extract the Code_Base file which can be found in the same directory as you saw “setup”
* In the original terminal you can type and run (This is the non singularity terminal)
```
unzip Code_Base.zip
```
Or navigate to that folder and right click unzip to Code_Base.zip
* In your third singularity terminal tab cd into Code_Base.zip
Once here the following commands only need to be run once

```
cmake .
```
* type and run (dont forget space afterwards)
```
make 
```
* to add agents to the simulator run the following command
```
./start.sh
```

## How to wrap more data for python
* To see these techniques in use view [Strategy.cc](https://github.com/SD-Group-17/RobocupPy/blob/core_test/Code_Base/behaviors/strategy.cc). the pyFunction.
* the first command that must be run before using or calling python Scripts or PyObjects is Py_Initialize(). this function basically creates a python interpreter to run python commands and files
* to run a python command use the following command PyRun_SimpleString("import os"). in this example here we are importing the os library to interpreter.
* this is an example on how you can call on a python file. to check if it has imported you can put pModule in an if statement
```C++

//calling on myFile.py 
PyObject *  pName = PyUnicode_FromString("myFile");
PyObject * pModule = PyImport_Import(pName);

if(pModule)
{
	// running the method myFunc in myFile.py
	PyObject * pFunc = PyObject_GetAttrString(pModule, "myFunc"); 
       
	if(pFunc && PyCallable_Check(pFunc))
	{
           //here we call on the python function and store the output in a PyObject in this example we are sending in a list so we attach an O before world_data
           PyObject * pReturn = PyObject_CallFunction(pFunc,"O",world_data);
	   //here we convert the pyobject to the relevent c++ format
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
for info on how to convert c++ to PyObject look [here](https://docs.python.org/3/c-api/arg.html)
and how to convert from PyObject to c++ you can look [here](https://docs.python.org/3/c-api/long.html)

* an example of converting a c++ data type to a python Object
```C++
//converting an integer to a PyObject
int x = 5
PyObject * temp;
temp = Py_BuildValue("i",x);
```
* an example of extracting data from a PyObject 
```C++
PyObject * objectPy;
//update objectPy
int x = (int) PyLong_AsLong(objectPy);
```

### Handling Python Lists 
* how to define a python list
```C++
int n = 5;
PyObject* pyList = PyList_New(n);
```
* how to get an item from the pyList (get the item at index 0)
```C++
PyObject* item = PyList_GetItem(pyList, 0);
```
* how to set an item in a python list
```C++
int value = 5;
PyObject * item = Py_BuildValue("i",value);
PyList_SetItem(PyList,0,item);
```
