import Robocup as RC

def selectSkill(world_data):
    robocup = RC.Robocup(world_data)

    if robocup.playerNumber() == 1:
        return robocup.STAND()
    else:
        return robocup.HARD_KICK(1.0,3.0)