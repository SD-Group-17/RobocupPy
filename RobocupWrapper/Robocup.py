import RobocupWrapper

    
class Robocup:

    #Atributes

    def __init__(self):
        self.teamDistanceToBall = RobocupWrapper.sendTeamDistanceToBall(0)
        self.ballPos = RobocupWrapper.sendBallPos(0)
        self.teammatesPos = RobocupWrapper.sendTeamPos(0)
        self.myPos = RobocupWrapper.sendMyPos(0)
        self.UNum = RobocupWrapper.sendUNum(0)
        self.NUMAGENTS = RobocupWrapper.sendNUMAGENTS(0)

    def Update(self,teamDistanceToBall):
        self.teamDistanceToBall = RobocupWrapper.sendTeamDistanceToBall(0)

    def playerDistanceToBall(self,playernum):
        return self.teamDistanceToBall[playernum]   

    def ballCoordinates(self):
        return self.ballPos
    
    
    def teamCoordinates(self):
        return self.teammatesPos

    def playerNumber(self):
        return self.UNum

    def playerCoordinates(self):
        return self.myPos

    def num_agents(self):
        return self.NUMAGENTS

    
