import Robocup as RC
import pytest
import os


player_number=2
play_mode=0
side = 0
player_pos = [-7,0,0]       
ball_pos = [0,0,0]
team_positions = [[[-10,0,0],1],[[-7,0,0],2]]
opponent_positions = [[[10,0,0],12],[[7,0,0],13]]
team_dist_ball = [[10,1],[7,2]]
opp_dist_ball = [[10,12],[7,13]]

world_data = [player_number,play_mode,side,player_pos,ball_pos,team_positions,opponent_positions,team_dist_ball,opp_dist_ball]

robocup = RC.Robocup(world_data)


def test_playerNumber():
    wanted_result = player_number
    test_result = robocup.playerNumber()
    assert(wanted_result == test_result), "Test Failed"

def test_playMode():
    wanted_result = play_mode
    test_result = robocup.playMode()
    assert(wanted_result == test_result), "Test Failed"

def test_gameSide():
    wanted_result = side
    test_result = robocup.gameSide()
    assert(wanted_result == test_result), "Test Failed"

def test_playerPos():
    wanted_result = player_pos
    test_result = robocup.playerPos()
    assert(wanted_result == test_result), "Test Failed"

def test_ballPos():
    wanted_result = ball_pos
    test_result = robocup.ballPos()
    assert(wanted_result == test_result), "Test Failed"

def test_teamPositions():
    wanted_result = team_positions
    test_result = robocup.teamPositions()
    assert(wanted_result == test_result), "Test Failed"

def test_opponentPositions():
    wanted_result = opponent_positions
    test_result = robocup.opponentPositions()
    assert(wanted_result == test_result), "Test Failed"

def test_teamDistBall():
    wanted_result = team_dist_ball
    test_result = robocup.teamDistBall()
    assert(wanted_result == test_result), "Test Failed"

def test_oppDistBall():
    wanted_result = opp_dist_ball
    test_result = robocup.oppsDistBall()
    assert(wanted_result == test_result), "Test Failed"

def test_teammateLocation():
    wanted_result = [-7,0,0]
    test_result = robocup.teammateLocation(2)
    assert(wanted_result == test_result), "Test Failed"

def test_opponentLocation():
    wanted_result = [10,0,0]
    test_result = robocup.opponentLocation(12)
    assert(wanted_result == test_result), "Test Failed"

def test_teammateDistBall():
    wanted_result = 7
    test_result = robocup.teammateDistBall(2)
    assert(wanted_result == test_result), "Test Failed"

def test_opponentDistBall():
    wanted_result = 10
    test_result = robocup.opponentDistBall(12)
    assert(wanted_result == test_result), "Test Failed"

def test_STAND():
    wanted_result = [0,[0,0]]
    test_result = robocup.STAND()

def test_GO_TO_POSITION():
    x = 10
    y = 11
    wanted_result = [1, [x,y]]
    test_result = robocup.GO_TO_POSITION(x,y)
    assert(wanted_result == test_result), "Test Failed"

def test_DRIBBLE():
    x = 10
    y = 11
    wanted_result = [2, [x,y]]
    test_result = robocup.DRIBBLE(x,y)
    assert(wanted_result == test_result), "Test Failed"

def test_SOFT_KICK():
    x = 10
    y = 11
    wanted_result = [3, [x,y]]
    test_result = robocup.SOFT_KICK(x,y)
    assert(wanted_result == test_result), "Test Failed"

def test_HARD_KICK():
    x = 10
    y = 11
    wanted_result = [4, [x,y]]
    test_result = robocup.HARD_KICK(x,y)
    assert(wanted_result == test_result), "Test Failed"

def test_SMART_GO_TO_POSITION():
    x = 10
    y = 11
    wanted_result = [5, [x,y]]
    test_result = robocup.SMART_GO_TO_POSITION(x,y)
    assert(wanted_result == test_result), "Test Failed"

def runTests():
    test_playerNumber()
    test_playMode()
    test_gameSide()
    test_playerPos()
    test_ballPos()
    test_teamPositions()
    test_opponentPositions()
    test_teamDistBall()
    test_oppDistBall()
    test_teammateLocation()
    test_teammateDistBall()
    test_opponentDistBall()
    test_STAND()
    test_GO_TO_POSITION()
    test_DRIBBLE()
    test_SOFT_KICK()
    test_HARD_KICK()
    test_SMART_GO_TO_POSITION()
    test_opponentLocation()


runTests()