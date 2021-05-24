import Robocup
import pytest
import os 

robocup = Robocup.Robocup()

# Test Cases which check the coordinates of the ball (its position)

def testBallCoord():
    wanted_result = [[2.0,0.0],[0.0,0.0],[0.0,2.0]]
    test_result = robocup.ballCoordinates()
    assert(wanted_result == test_result), "Test Failed"

# Test cases which check the coordinates of each player in a team 

def testTeamCoord():
    wanted_result = [[2.0,1.0],[8.0,9.0],[20.0,10.0]]
    test_result = robocup.teamCoordinates()
    assert(wanted_result == test_result), "Test Failed"

# Test cases which check the current player's number

def testPlayerNum():
    wanted_result = [0,5,10]
    test_result = robocup.playerNumber()
    assert(wanted_result == test_result), "Test Failed"

# Test cases which check the coordinates of the current player

def testThisPlayerCoord():
    wanted_result = [[2.0, 1.0], [5.0, 10.0], [12.0, 4.0]]
    test_result = robocup.thisPlayerCoordinates()
    assert(wanted_result == test_result), "Test Failed"

# Test cases which check the total number of agents in a team on the field

def testNumAgents():
    wanted_result = [11,5,1]
    test_result = robocup.num_agents()
    assert(wanted_result == test_result), "Test Failed"

# Test cases which check the distance between the current player and the ball 

def testPlayerDistanceToBall():
    wanted_result = [17.804493814764857, 18.027756377319946, 5.385164807134504]
    test_result = robocup.playerDistanceToBall(0)    
    assert(wanted_result == test_result), "Test Failed"



#Running Tests:
def runTests():
    testBallCoord()
    testTeamCoord()
    testPlayerNum()
    testThisPlayerCoord()
    testPlayerDistanceToBall()


runTests()