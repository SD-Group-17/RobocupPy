import Robocup



def selectSkill():
    print('Python function selectSkill() called')
    return calculateSkill()

def calculateSkill():

    robocup = Robocup.Robocup()

    print('Calculating next skill...')
    #calculations here
    
    skill = 0 #robocup.playerNumber()

    return skill