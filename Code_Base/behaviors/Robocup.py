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
        self.player_number=world_data[0]
        self.play_mode=world_data[1]
        self.side = world_data[2]
        self.player_pos = world_data[3]        
        self.ball_pos = world_data[4]
        self.team_positions = world_data[5]
        self.opponent_positions = world_data[6]

        #Wrapped C++ Functions:
        self.team_dist_ball = world_data[7]
        self.opp_dist_ball = world_data[8]
    
    #getters (for world model data):

    def playerNumber(self):
        return self.player_number

    def playMode(self):
        return self.play_mode

    def playerPos(self):
        return self.player_pos

    def gameSide(self):
        return self.side 
          
      
    def ballPos(self):
        return self.ball_pos 
       

    def teamPositions(self):
        return self.team_positions 
        

    def opponentPositions(self):
        return self.opponent_positions 

    # getters for Wrapped C++ functions:

    def teamDistBall(self):
        return self.team_dist_ball 
      

    def oppDistBall(self):
        return self.opp_dist_ball 


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