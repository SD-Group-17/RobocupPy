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
        #return self.teamDistanceToBall[playernum]   
        return self.teamDistanceToBall


    def ballCoordinates(self):
        return self.ballPos
    
    
    def teamCoordinates(self):
        return self.teammatesPos

    def playerNumber(self):
        return self.UNum

    def thisPlayerCoordinates(self):
        return self.myPos

    def playerCoordinates(self,n):
        return self.teammatesPos[n]

    def num_agents(self):
        return self.NUMAGENTS
    
    def distance(self, pos1, pos2):
        return RobocupWrapper.distance(pos1[0],pos1[1],pos2[0],pos2[1])

    
