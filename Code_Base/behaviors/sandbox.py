import Robocup as RC
import strategyPy as strategy
from numbers import Number


# This is a sandbox file to run your strategy on a single world model instance
#
# The purpose of this file is to check if your python file has syntax errors or is throwing exceptions
# Run this file if your agent disappears from the server after starting kick off (this means that your code has errors and has crashed)
#
# Run using this command:
# python3 sandbox.py


# These are the data structures that are passed into your code from the simulator:
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

skill = strategy.selectSkill(world_data)


#The following checks if selectSkill() returns an acceptable object:
check_list = isinstance(skill, list)
allGood = True
if check_list:

    if len(skill) <2:
        print("Skill has too few dimensions")
        allGood = False
    else:
        skill_choice = skill[0]
        position = skill[1]

        check_skill_choice = isinstance(skill_choice, int) 

        if check_skill_choice:
            if not(skill_choice >=0 and  skill_choice <=5):
                print("Chosen skill must be int between 0 and 5")
                allGood = False
        else:
            print("Chosen skill must be int")
            allGood = False

        check_position = isinstance(position,list)

        if check_position:
            if len(position) <2:
                print("Position has too few dimensions")
                allGood = False
            else:
                x = position[0]
                y= position[1]

                check_x = isinstance(x,Number)
                check_y = isinstance(y,Number)
                if not(check_x and check_y):
                    print("x and y coordinates must be of type number")
                    allGood = False
        else:
            print("Check_position must be a list")
            allGood = False
else:
    print("Error: selectSkill() MUST return a list")
    print("Select skill is returning an object of type: ",type(skill))
    allGood = False

if not allGood:
    print("selectSkill() returns incorrect data structures")
    print("selectSkill() must return object of type and shape: [int,[float,float]]")

print("selectSkill() returns: ",skill)