import Robocup as RC

def selectSkill(world_data):
    robocup = RC.Robocup(world_data)

    if robocup.playerNumber() == 1:
        return robocup.STAND()
    else:
        if robocup.gameSide() == 0:
            return robocup.HARD_KICK(robocup.GOAL_LEFT_CENTRE_X +0.1,robocup.GOAL_LEFT_CENTRE_Y)
        else:
            return robocup.HARD_KICK(robocup.GOAL_RIGHT_CENTRE_X -0.1,robocup.GOAL_RIGHT_CENTRE_Y)
