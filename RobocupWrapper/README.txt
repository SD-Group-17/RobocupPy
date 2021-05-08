Set up:
1)Navigate to RobocupWrapper folder through terminal

2) Run:
python3 setup01.py  build_ext --inplace

3) Run:
Python3 test.py

________________________________________________________

To use robocup library, import robocup class and initialise it by adding these lines to your python file:

import Robocup

robocup = Robocup.Robocup()
________________________________________________________

Functionality in Library:

Ball Coordinates (returns 1 d array of float values):  robocup.ballCoordinates() 

Team Coordinates (returns 2 d array of float values, each row corresponcs to the (x,y) cooridnates of a player):  robocup.teamCoordinates()
Player Number (returns 1 d array of float values):  robocup.playerNumber()
Player Coordinates (returns 1 d array of float values): robocup.playerCoordinates()
Number of agents  (returns integer):  robocup.num_agents()
Distance of player n to ball (returns float):  robocup.playerDistanceToBall(n)