import Robocup as RC

def selectSkill(world_data):
    robocup = RC.Robocup(world_data)

    if robocup.playerNumber() == 1:
        return robocup.STAND()
    else:
        if robocup.gameSide() == 0:
            return robocup.HARD_KICK(robocup.HALF_FIELD_X +0.1,robocup.HALF_FIELD_Y)
        else:
            return robocup.HARD_KICK(- (robocup.HALF_FIELD_X +0.1),robocup.HALF_FIELD_Y)
