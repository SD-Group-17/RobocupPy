import Robocup

robocup = Robocup.Robocup()

#Wrapper functions:
def runTests():
    print("Ball Coordinates:  " + str(robocup.ballCoordinates() ))
    print("Team Coordinates:  " + str(robocup.teamCoordinates()))
    print("This Player Number:  " + str(robocup.playerNumber()))
    print("This player Coordinates  " + str(robocup.thisPlayerCoordinates()))
    print("Number of agents:  " + str(robocup.num_agents()))
    for n in range(robocup.num_agents()):
        print("Distance of player "+str(n)+" to ball: " + str(robocup.playerDistanceToBall(n)))

    print("Distance of player 0 to ball:" + str(robocup.distance( robocup.playerCoordinates(0), robocup.ballCoordinates()  )))
runTests()
