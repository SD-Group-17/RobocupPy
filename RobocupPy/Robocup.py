import RobocupWrapper

    
class Robocup:

    #Atributes
    teamDistanceToBall = None

    def __init__(self,teamDistanceToBall):
        self.teamDistanceToBall = RobocupPy.sendTeamDistanceToBall(0)

    def Update(self,teamDistanceToBall):
        self.teamDistanceToBall = RobocupPy.sendTeamDistanceToBall(0)

    def first():
        return teamDistanceToBall[0]