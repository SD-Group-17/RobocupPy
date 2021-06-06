from numbers import Number

class Robocup():
    #Documentation:
    """
    Robocup Class for Python - Contains world data, skills and wrapped functions!

    Class Attributes
    ----------
    Constant world model data defined in documentation.
    FIELD_Y=20.0               | width of the field (sideline to sideline) (int)
    FIELD_X=30.0               | length of the field (goal line to goal line) (int)
    HALF_FIELD_Y = FIELD_Y/2.0 | half the width of the field (sideline to sideline) (int)
    HALF_FIELD_X = FIELD_X/2.0 | half the length of the field (goal line to goal line) (int)
    GOAL_Y = 2.1               | width of goal (int)
    GOAL_X = 0.6               | length of goal (int)
    GOAL_Z = 0.8               | height of goal (int)
    HALF_GOAL_Y = GOAL_Y / 2.0 | half goal y (int)
    FIELD_CENTER_X = 0.0       | x coordinate of field centre (int)
    FIELD_CENTER_Y = 0.0       | y coordinate of field centre (int)

    GOAL_LEFT_CENTRE_X = HALF_FIELD_X   | left goal line midpoint x (int)
    GOAL_LEFT_CENTRE_Y = 0              | left goal line midpoint y (int)
    GOAL_RIGHT_CENTRE_X = -HALF_FIELD_X | right goal line midpoint x (int)
    GOAL_RIGHT_CENTRE_Y = 0             | right goal line midpoint y (int)


    Instance Attributes
    ----------
    Variable world  model data passed through wrapper:

    __player_number : private int
        the player number for this agent

    __play_mode : private int
        the play mode for this game

    __side : private int
        the side for this agent's team

    __player_pos : private [float x,float y, float z] list
        the agent's x,y,z coordinates on the field     

    __ball_pos : private [float x,float y, float z] list
        the ball's x,y,z coordinates on the field    

    __team_positions : private [ [[float x,float y, float z], int], [[float x,float y, float z], int], ..., [[float x,float y, float z], int] ] list of lists
        list of the agent's teammates' x,y,z coordinates on the field, paired with each agent's corresponding player number  

    __opponent_positions : private [ [[float x,float y, float z], int], [[float x,float y, float z], int], ..., [[float x,float y, float z], int] ] list of lists
        list of the agent's opponents teammates' x,y,z coordinates on the field, paired with each agent's corresponding player number  

    Wrapped C++ Functions passed through wrapper:

    __team_dist_ball : private [ [float , int], [float , int], ..., [float , int] ] list of lists
        list of the agent's teammates' distance to the ball, paired with each agent's corresponding player number  

    __opp_dist_ball : private [ [float , int], [float , int], ..., [float , int] ] list of lists
        list of the agent's opponents teammates' distance to the ball, paired with each agent's corresponding player number 


    Methods
    ----------
    Getters (for world model data):

    playerNumber():
        returns self.__player_number

    playMode():
        returns self.__play_mode

    playerPos():
        returns self.__player_pos

    gameSide():
        returns self.__side 
    
    ballPos():
        returns self.__ball_pos        

    teamPositions():
        returns self.__team_positions 
    
    opponentPositions():
        returns self.__opponent_positions 

    Getters with data handling:

    teammateLocation(n): [float,float,float]
        returns list of x,y,z coordinates of teammate with player number n
    
    opponentLocation(n): [float,float,float]
        returns list of x,y,z coordinates of opponent with player number n

    Getters for Wrapped C++ functions:

    teamDistBall(self):
        returns self.__team_dist_ball 
    
    oppsDistBall(self):
        returns self.__opp_dist_ball 

    Getters for Wrapped C++ functions with data handling:

    teammateDistBall(n): float
        returns teammate with player number n's distance to ball

    opponentDistBall(n): float
        returns teammate with player number n's distance to ball

    Skills:

    STAND():
        returns skill STAND in Doucmentation (player stands still)
    
    GO_TO_POSITION(x,y):
        returns skill GOTO in Documentation, with target coordinate (x,y,0)
    
    DRIBBLE(x,y):
        returns skill DRIBBLE in Documentation, with target coordinate (x,y,0)
    
    SOFT_KICK(x,y):
        returns skill KICK in Documentation, with target coordinate (x,y,0)
    
    HARD_KICK(x,y):
        returns skill KICK_IK in Documentation, with target coordinate (x,y,0)

    SMART_GO_TO_POSITION(x,y):
        returns skill SMART_GO_TO_TARGET in Documentation, with target coordinate (x,y,0)

    
    """


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
        """
        Parameters
        ----------
        world data passed through to selectSkill() - ALTERATION IS NOT RECOMMENDED
        This mirrors worldDate object on C++ side
        """

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
        """
        Returns
        ----------
        int
        the player number for this agent
        """

        return self.__player_number

    def playMode(self):
        """
        Returns
        ----------
        int
        the play mode for this game
        """

        return self.__play_mode

    def playerPos(self):
        """
        Returns
        ----------
        [float]
        list of x,y,z coordinates for this agent
        """

        return self.__player_pos

    def gameSide(self):
        """
        Returns
        ----------
        int
        0 if agent's team is left side of pitch, 1 if right side
        """

        return self.__side 
          
      
    def ballPos(self):
        """
        Returns
        ----------
        [float]
        list of x,y,z coordinates for ball
        """

        return self.__ball_pos 
       

    def teamPositions(self):
        """
        Returns
        ----------
        [[[float],int]]
        list of x,y,z coordinates for teammates paired with corresponding player number
        """

        return self.__team_positions 
        

    def opponentPositions(self):
        """
        Returns
        ----------
        [[[float],int]]
        list of x,y,z coordinates for opponents paired with corresponding player number
        """

        return self.__opponent_positions 
    
    #Getters with data handling:

    def teammateLocation(self, n):
        """
        Returns
        ----------
        [float]
        list of x,y,z coordinates for teammate with player number n

        Raises
        ----------
        TypeError
            Only integer input is acceptable
        Exception
            Range for n should be: 0< n <= (number of agents in team)
        """

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
        """
        Returns
        ----------
        [float]
        list of x,y,z coordinates for opponent with player number n

        Raises
        ----------
        TypeError
            Only integer input is acceptable
        Exception
            Range for n should be: 12<= n < 12+ (number of agents in team)
        """

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

    # getters for Wrapped C++ functions:

    def teamDistBall(self):
        """
        Returns
        ----------
        [[float,int]]
        list of distances to ball for teammates paired with corresponding player number
        """

        return self.__team_dist_ball 
      

    def oppsDistBall(self):
        """
        Returns
        ----------
        [[float,int]]
        list of distances to ball for opponents paired with corresponding player number
        """

        return self.__opp_dist_ball 

            
    def teammateDistBall(self, n):
        """
        Returns
        ----------
        float
        distance of teammate with player number n to ball

        Raises
        ----------
        TypeError
            Only integer input is acceptable
        Exception
            Range for n should be: 0< n <= (number of agents in team)
        """

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
        """
        Returns
        ----------
        float
        distance of opponent with player number n to ball

        Raises
        ----------
        TypeError
            Only integer input is acceptable
        Exception
            Range for n should be: 12<= n < 12+ (number of agents in team)
        """

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
        """
        Returns
        ----------
        SKILL
        STAND in Documentation (player stands still)
        """

        return [0,[0,0]]
    
    def GO_TO_POSITION(self,x,y):
        """
        Returns
        ----------
        SKILL
        GOTO in Documentation, with target coordinate (x,y,0)

        Raises
        ----------
        TypeError
            Only number input is acceptable
        """

        if not isinstance(x, Number) or not isinstance(y, Number):
            raise TypeError("Only numbers are allowed for x and y")
        return [1, [x,y]]
    
    def DRIBBLE(self,x,y):
        """
        Returns
        ----------
        SKILL
        DRIBBLE in Documentation, with target coordinate (x,y,0)

        Raises
        ----------
        TypeError
            Only number input is acceptable
        """

        if not isinstance(x, Number) or not isinstance(y, Number):
            raise TypeError("Only numbers are allowed for x and y")
        return [2, [x,y]]
    
    def SOFT_KICK(self,x,y):
        """
        Returns
        ----------
        SKILL
        KICK in Documentation, with target coordinate (x,y,0)
        
        Raises
        ----------
        TypeError
            Only number input is acceptable
        """

        if not isinstance(x, Number) or not isinstance(y, Number):
            raise TypeError("Only numbers are allowed for x and y")
        return [3, [x,y]]
    
    def HARD_KICK(self,x,y):
        """
        Returns
        ----------
        SKILL
        KICK_IK in Documentation, with target coordinate (x,y,0)
        
        Raises
        ----------
        TypeError
            Only number input is acceptable
        """

        if not isinstance(x, Number) or not isinstance(y, Number):
            raise TypeError("Only numbers are allowed for x and y")
        return [4, [x,y]]

    def SMART_GO_TO_POSITION(self,x,y):
        """
        Returns
        ----------
        SKILL
        SMART_GO_TO_TARGET in Documentation, with target coordinate (x,y,0)
        
        Raises
        ----------
        TypeError
            Only number input is acceptable
        """

        if not isinstance(x, Number) or not isinstance(y, Number):
            raise TypeError("Only numbers are allowed for x and y")
        return [5, [x,y]]
