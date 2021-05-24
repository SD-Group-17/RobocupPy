Set up:
1)Navigate to RobocupWrapper folder through terminal

2) Run:
python3 setup01.py  build_ext --inplace

3) Run:
Python3 test.py
___________________________________________________________
Bi-directional:

1) Compile:

Linux:
For python3.8 systems:
g++ strategy.cc -o program -I/usr/include/python3.8 -lpython3.8 

For other versions:
g++ strategy.cc -o program -I/usr/include/python3.<your version>  -lpython3.<your version>
NB Must use python3.7^

Windows:
TODO:
figure out how to run on windows

2) Run: 
./program
___________________________________________________________
Testing:

g++ test.cc -o program -I/usr/include/python3.8 -I/usr/include/CppUTest -I/usr/include/CppUTestExt  -lpython3.8 -lCppUTest -lCppUTestExt

___________________________________________________________

To use robocup library, import robocup class and initialise it by adding these lines to your python file:

import Robocup

robocup = Robocup.Robocup()
________________________________________________________

Functionality in Library:

Ball Coordinates (returns 1 d array of float values):  robocup.ballCoordinates() 

Team Coordinates (returns 2 d array of float values, each row corresponcs to the (x,y) cooridnates of a player):  robocup.teamCoordinates()
This player Number (returns 1 d array of float values):  robocup.playerNumber()
This player Coordinates (returns 1 d array of float values): robocup.thisPlayerCoordinates()
Coordinates of player n (returns 1 d array of float values): robocup.playerCoordinates(n)
Number of agents  (returns integer):  robocup.num_agents()
Distance of player n to ball (returns float):  robocup.playerDistanceToBall(n)
Distance between two points (pos1 and pos2 are 1d arrays cotaining float (x,y) pairs): robocup.distance(pos1, pos2)