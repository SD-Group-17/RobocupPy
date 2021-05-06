import RobocupWrapper

    
class Robocup:

    #Atributes

    def __init__(self):
        self.teamDistanceToBall = RobocupWrapper.sendTeamDistanceToBall(0)

    def Update(self,teamDistanceToBall):
        self.teamDistanceToBall = RobocupWrapper.sendTeamDistanceToBall(0)

    def playerdistance(self,playernum):

        return self.teamDistanceToBall[playernum]