class Robocup():


    #Field Constants
    FIELD_Y=20.0
    FIELD_X=30.0
    HALF_FIELD_Y = FIELD_Y/2.0
    HALF_FIELD_X = FIELD_X/2.0
    GOAL_Y = 2.1
    GOAL_X = 0.6
    GOAL_Z = 0.8
    HALF_GOAL_Y = GOAL_Y / 2.0
    FIELD_CENTER_X = 0.0
    FIELD_CENTER_Y = 0.0

    GOAL_LEFT_CENTRE_X = HALF_FIELD_X
    GOAL_LEFT_CENTRE_Y = 0
    GOAL_RIGHT_CENTRE_X = -HALF_FIELD_X
    GOAL_RIGHT_CENTRE_Y = 0


    def __init__(self, world_data):

                
        #World Model Data:
        self.__player_number=world_data[0]
        self.__play_mode=world_data[1]
        self.__side = world_data[2]
        self.__player_pos = world_data[3]        
        self.__ball_pos = world_data[4]
        self.__team_positions = world_data[5]
        self.__opponent_positions = world_data[6]

        #Wrapped C++ Functions:
        self.__team_dist_ball = world_data[7]
        self.__opp_dist_ball = world_data[8]
    
    #getters (for world model data):

    def playerNumber(self):
        return self.__player_number

    def playMode(self):
        return self.__play_mode

    def playerPos(self):
        return self.__player_pos

    def gameSide(self):
        return self.__side 
          
      
    def ballPos(self):
        return self.__ball_pos 
       

    def teamPositions(self):
        return self.__team_positions 
        

    def opponentPositions(self):
        return self.__opponent_positions 

    # getters for Wrapped C++ functions:

    def teamDistBall(self):
        return self.__team_dist_ball 
      

    def oppsDistBall(self):
        return self.__opp_dist_ball 

    def teammateLocation(self, n):
        if not type(n) is int:
            raise TypeError("Only integers are allowed")

        elif n > len(self.__team_positions):
            raise Exception("Player not in team (player number must be less than number of teammates)")
        
        elif n <= 0:
            raise Exception("Player not in team (player number must be > 0)")

        for playerpos in self.__team_positions:
            if playerpos[1] == n:
                return playerpos[0]

        raise Exception("Player not in team (player number not found in list of teammates)")
    
    def opponentLocation(self, n):
        if not type(n) is int:
            raise TypeError("Only integers are allowed")

        elif n >= len(self.__opponent_positions)+12:
            raise Exception("Player not in opponent team (player number must be less than or equal to number of opponenets + 12 )")
        
        elif n < 12:
            raise Exception("Player not in opponent team (player number must be >= 12)")

        for playerpos in self.__opponent_positions:
            if playerpos[1] == n:
                return playerpos[0]

        raise Exception("Player not in opponent team (player number not found in list of opponents)")
        
    def teammateDistBall(self, n):
        if not type(n) is int:
            raise TypeError("Only integers are allowed")

        elif n > len(self.__team_dist_ball):
            raise Exception("Player not in team (player number must be less than number of teammates)")
        
        elif n <= 0:
            raise Exception("Player not in team (player number must be > 0)")

        for playerdist in self.__team_dist_ball:
            if playerdist[1] == n:
                return playerdist[0]

        raise Exception("Player not in team (player number not found in list of teammates)")
    
    def opponentDistBall(self, n):
        if not type(n) is int:
            raise TypeError("Only integers are allowed")

        elif n >= len(self.__opp_dist_ball)+12:
            raise Exception("Player not in opponent team (player number must be less than or equal to number of opponenets + 12 )")
        
        elif n < 12:
            raise Exception("Player not in opponent team (player number must be >= 12)")

        for playerdist in self.__opp_dist_ball:
            if playerdist[1] == n:
                return playerdist[0]

        raise Exception("Player not in opponent team (player number not found in list of opponents)")
        


    #SKILLS:
    def STAND(self):
        return [0,[0,0]]
    
    def GO_TO_POSITION(self,x,y):
        return [1, [x,y]]
    
    def DRIBBLE(self,x,y):
        return [2, [x,y]]
    
    def SOFT_KICK(self,x,y):
        return [3, [x,y]]
    
    def HARD_KICK(self,x,y):
        return [4, [x,y]]

    def SMART_GO_TO_POSITION(self,x,y):
        return [5, [x,y]]