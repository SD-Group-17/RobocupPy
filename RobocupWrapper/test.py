import Robocup

robocup = Robocup.Robocup()

#Wrapper functions:
def runTests():
    print("Ball Coordinates:  " + str(robocup.ballCoordinates() ))
    print("Team Coordinates:  " + str(robocup.teamCoordinates()))
    print("Player Number:  " + str(robocup.playerNumber()))
    print("Player Coordinates  " + str(robocup.playerCoordinates()))
    print("Number of agents:  " + str(robocup.num_agents()))
    for n in range(robocup.num_agents()):
        print("Distance of player "+str(n)+" to ball: " + str(robocup.playerDistanceToBall(n)))

runTests()
