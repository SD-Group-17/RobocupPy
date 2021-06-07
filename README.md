# RobocupPy
[![Build Status](https://travis-ci.org/SD-Group-17/RobocupPy.svg?branch=core_test)](https://travis-ci.org/SD-Group-17/RobocupPy) [![codecov](https://codecov.io/gh/SD-Group-17/RobocupPy/branch/core_test/graph/badge.svg)](https://codecov.io/gh/SD-Group-17/RobocupPy)

RobocupPy is a wrapper for the UT Austin Villa Codebase that allows you to use python for Robocup.

## Documentation:
* [RobocupPy Class](https://htmlpreview.github.io/?https://github.com/SD-Group-17/RobocupPy/blob/master/Documentation/html/classRobocup_1_1Robocup.html)
* functions added to [strategy.cc](https://htmlpreview.github.io/?https://github.com/SD-Group-17/RobocupPy/blob/master/Documentation/html/strategy_8cc.html)
* [Wiki](https://github.com/SD-Group-17/RobocupPy/wiki)
  * [UML Diagrams](https://github.com/SD-Group-17/RobocupPy/blob/master/Documentation/UML/ReadMe.md)
  * [Requirements Document](https://github.com/SD-Group-17/RobocupPy/blob/master/Documentation/RD.pdf)

for a better view download the documentation and view it on your browser
## Installation
### (Singularity)
This is a quick instruction guide on how to install the Robocup distribution on your home computer.

Make sure you are connected to the internet as this will require a once off ~300mb download
this is a setup for debian based systems. to run this on windows download WSL. more info can be found [here](https://docs.microsoft.com/en-us/windows/wsl/install-win10)
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
* if a permission denied message is thrown run the following command and run the above command again
```
 chmod 777 start.sh
```

## Running First Game
instructions on how to run first game can be found [here](https://courses.ms.wits.ac.za/~branden/RoboCup/my-first-game.html)

## Tutorial
### Coding your first team in python using strategyPy.py

```python
import Robocup as RC #Do Not edit this line
def selectSkill(world_data): #Do Not edit this line
    robocup = RC.Robocup(world_data) #Do Not edit this line

    if robocup.playerNumber() == 1:
        return robocup.STAND()
    else:
        if robocup.gameSide() == 0:
            return robocup.HARD_KICK(robocup.GOAL_LEFT_CENTRE_X +0.1,robocup.GOAL_LEFT_CENTRE_Y)
        else:
            return robocup.HARD_KICK(robocup.GOAL_RIGHT_CENTRE_X -0.1,robocup.GOAL_RIGHT_CEN
```
The above is example code showing a single 2 player team, where player 0 acts as goalie and player 1 goes ahead to score a goal.


In your verison, do not edit the first 3 lines, these are necessary for running a game.


You must always return a skill from the robocup class. See provided documentation for the Robocup class in Robocup.py for a list of these skills, and how to call on them. 

The above mentioned documentation provides a detailed list of the rest of the class and how to use it. See also the original documentation.

To return a specific skill, use the following format:

```python
return robocup.<YOUR CHOSEN SKILL>
```

### Debugging your code using sandbox.py

Often the singularity fails to notify you if your python code is not compiling/running correctly, use sandbox.py to quickly check if your code is able to run.

To use the sandbox: Navigate to the Behaviors folder in the Code_Base with your terminal, then run the following line in terminal:

```
python sandbox.py
```

This checks your selectSkill() function in strategyPy.py against a single instance of world model data to see if it is returning a skill correctly. It will also reveal any syntax errors or bugs in your code.

### Adding more methods to strategyPy.py

If you want to add your own functions and methods to strategyPy.py, for certain purposes, you may need to pass through the robocup object, so as to gain access to the world data contained in the robocup instance, as well as the methods and functionality contained in the Robocup class.

Do this inside strategyPy.py:

```python
import Robocup as RC
def selectSkill(world_data):
	robocup = RC.Robocup(world_data)
	
	return yourMethod(robocup) #call your method, but remember to pass thorugh the robocup instance

def yourMethod(robocup):
	#your method logic here
	my_number = robocup.playerNumber() #accessing world data contained in robocup instance
	chosen_skill = robocup.STAND() #accessing methods of Robocup class
	return chosen_skill
```




## How to send more data to python
* To see these techniques in use view [Strategy.cc](https://github.com/SD-Group-17/RobocupPy/blob/master/Code_Base/behaviors/strategy.cc). the pyFunction.
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


## Using the world data object:

In strategy.cc, there is a method: worldData(), which takes in a series of PyObjects, and returns them as a list. It is this list, world_data, that is passed through to python.

### Passing the world_data list through to python:
C++ side:
```C++
PyObject * world_data = worldData(playerNumPy,playModePy,sidePy,posPy,ballPy, teamPositionsPy, oppPositionsPy ,teamDistToBallPy,OppDistToBallPy);
n = pyFunction(world_data,pos); //This calls on selectSkill() in python, passing it world_data as a parameter
```
Python side:
```python
import Robocup as RC
def selectSkill(world_data): #see how selectSkill() takes in world_data as a parameter
    robocup = RC.Robocup(world_data) #see how the Robocup constructor takes in world_data as a parameter
```

### Comparing the worldData() method to the constructor for the Robocup class in python:

worldData()
```C++
PyObject * worldData(PyObject *  _playerNumber,PyObject * _playMode,PyObject * _side,PyObject * posPy,PyObject * ballPy,PyObject *  teamPositionsPy,PyObject *  oppPositionsPy,PyObject * teamDistToBallPy,PyObject * OppDistToBallPy){
    
    //this mirrors constructor for Robocup class on python side
    
    PyObject * pyList;
    pyList = PyList_New(9);
    PyList_SetItem(pyList,0,_playerNumber);
    PyList_SetItem(pyList,1,_playMode);
    PyList_SetItem(pyList,2,_side);
    PyList_SetItem(pyList,3,posPy);    
    PyList_SetItem(pyList,4,ballPy);
    PyList_SetItem(pyList,5,teamPositionsPy);
    PyList_SetItem(pyList,6,oppPositionsPy);

    PyList_SetItem(pyList,7,teamDistToBallPy);
    PyList_SetItem(pyList,8,OppDistToBallPy);



    return pyList;
```

Robocup constructor:
```python
class Robocup():
    #...
    def __init__(self, world_data):
        """
        Parameters
        ----------
        world data passed through to selectSkill() - ALTERATION IS NOT RECOMMENDED
        This mirrors worldDate object on C++ side
        """

        #World Model Data:
        self.__player_number=world_data[0]
        self.__play_mode=world_data[1]
        self.__side = world_data[2]
        self.__player_pos = world_data[3]        
        self.__ball_pos = world_data[4]
        self.__team_positions = world_data[5]
        self.__opponent_positions = world_data[6]

        #Wrapped C++ Functions:
        self.__team_dist_ball = world_data[7]
        self.__opp_dist_ball = world_data[8]
```

As you can see, the constructor for the Robocup class in python clearly mirrors the method for worldData in C++.

### Send through more data using the world data object:

If you wish to pass more data through from C++ to python, simply convert that data to a PyObject (as described above) and edit the worldData() method so it accepts another object parameter, and adds it to the world_data list. 

You will have to initialise the list to be larger, as well as add the object to the list:
```python
PyObject * worldData(/*...*/, PyObject yourNewObject){
    pyList = PyList_New(n);//change the n value to match the number of parameters.
    // ...
    PyList_SetItem(pyList,n,yourNewObject);
    
    return pyList
}
```

Now, make the relevant changes to the Robocup constructor on the python side. This will mirror the worldData() method in C++.

```python
class Robocup():
    #...
    def __init__(self, world_data):        
        #...
        self.__your_new_object = world_data[n] #we recommend making this object private, so that users do not edit (and lost) the world data they receive from the server.
        #...

    def yourObjectGetter(self):
        return self.__your_new_object #since your object is private, you will need a getter
```

## Known issues
* Running the simulator in full screen can cause issues.
