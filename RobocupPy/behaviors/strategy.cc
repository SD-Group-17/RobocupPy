#define PY_SSIZE_T_CLEAN
#include "naobehavior.h"
#include "../rvdraw/rvdraw.h"
#include <Python.h>

extern int agentBodyType;

/* Global Python Variables
 */
PyObject* world;
PyObject* teamDistanceFromBall;




//calling python code
//PyObject* myModuleString = PyString_FromString((char*)"robopy");
//PyObject* myModule = PyImport_Import(myModuleString);

//PyObject* myFunction = PyObject_GetAttrString(myModule,(char*)"hello");


/*
 * Real game beaming.
 * Filling params x y angle
 */
void NaoBehavior::beam( double& beamX, double& beamY, double& beamAngle ) {

    if(worldModel->getPlayMode() == 0){

        if(worldModel->getUNum() == 1){
		    beamX = -3;
            beamY = -2;
            beamAngle = 0;
        }
        else if(worldModel->getUNum() == 2){
		    beamX = -3;
            beamY = 2;
            beamAngle = 0;
        }


    }
    else if(worldModel->getPlayMode() == 1){
        if(worldModel->getUNum() == 1){
		    beamX = 0;
            beamY = 0;
            beamAngle = 0;
        }
        else if(worldModel->getUNum() == 2){
		    beamX = -HALF_FIELD_X + worldModel->getUNum();
            beamY = 0;
            beamAngle = 0;
        }
    }
}

SkillType NaoBehavior::gotoFieldPosBeforeKickOff(int pNum){
    double x = -1;
	double y = -1;
	double angle = -1;
    
    if(pNum== 1){
		    x = -2;
            y = -2;
            angle = 0;
        }
    else if(pNum == 2){
		    x = -3;
            y = 2;
            angle = 0;
    }

    return SmartGoToTarget(VecPosition(x,y,0),0.5); 
}

SkillType NaoBehavior::gotoFieldPosOurKickOff(int pNum){
    double x = -1;
	double y = -1;
	double angle = -1;
    
    if(pNum== 1){
		    x = -0.5;
            y = 0.5;
            angle = 0;
        }
    else if(pNum == 2){
		    x = -3;
            y = 4;
            angle = 0;
    }

    return SmartGoToTarget(VecPosition(x,y,0),0.5); 
}

SkillType NaoBehavior::gotoFieldPosTheirKickOff(int pNum){
    double x = -1;
	double y = -1;
	double angle = -1;
    
    if(pNum== 1){
            WorldObject* opponent1 = worldModel->getWorldObject(WO_OPPONENT1);
            VecPosition temp = opponent1->pos;
		    x = -HALF_FIELD_X /4;
            y = temp.getY();
            angle = 0;
        }
    else if(pNum == 2){
		    WorldObject* opponent2 = worldModel->getWorldObject(WO_OPPONENT2);
            VecPosition temp = opponent2->pos;
		    x = -HALF_FIELD_X /3;
            y = temp.getY();
            angle = 0;
    }

    return SmartGoToTarget(VecPosition(x,y,0),0.5); 
}

SkillType NaoBehavior::gotoFieldPosTheirFreeKick(int pNum){
    double x = -1;
	double y = -1;
	double angle = -1;
    
    if(pNum== 1){
            WorldObject* opponent1 = worldModel->getWorldObject(WO_OPPONENT1);
            VecPosition temp = opponent1->pos;
		    x = temp.getX()-5;
            y = temp.getY();
            angle = 0;
        }
    else if(pNum == 2){
		    WorldObject* opponent2 = worldModel->getWorldObject(WO_OPPONENT2);
            VecPosition temp = opponent2->pos;
		    x = temp.getX()-5;
            y = temp.getY();
            angle = 0;
    }
    VecPosition target = VecPosition(x,y,0);
    target = ValidateFieldPos(target);
    return SmartGoToTarget(target,0.5); 
}


SkillType NaoBehavior::gotoFieldPosDefensive(){
	double x = -1;
	double y = -1;
	double angle = -1;

    if(worldModel->getUNum() == 1){
		 x = -HALF_FIELD_X ;
    	 y = 0;
    	 angle = 0;
	} 
    else if(worldModel->getUNum() == 2){
		 x = -HALF_FIELD_X +4 ;
    	 y = 2;
    	 angle = 0;
    }

    return SmartGoToTarget(VecPosition(x,y,0),0.5); 

}

SkillType NaoBehavior::gotoFieldPosOffensive(){
	double x = -1;
	double y = -1;
	double angle = -1;

    if(worldModel->getUNum() == 1){
		 x = -HALF_FIELD_X ;
    	 y = 0;
    	 angle = 0;
	} 
    else if(worldModel->getUNum() == 2){
		 x = -HALF_FIELD_X +4 ;
    	 y = 2;
    	 angle = 0;
    }

    return SmartGoToTarget(VecPosition(x,y,0),0.5); 

}


PyObject * convertTeamDistanceToBall(double* teamDistance)
{
    
    int size = sizeof(teamDistance) / sizeof(teamDistance[0]);
    PyObject * distance = PyList_New(size);
    PyObject * pyValue;

    for(int i = 0;i<size;i++)
    {
        double value = teamDistance[i];
        pyValue = Py_BuildValue("i",value);
        PyList_SetItem(distance,i,pyValue);
    }

    return distance;
}


PyObject * sendTeamDistanceToBall(PyObject * self,PyObject* args)
{
    int n;

    if(!PyArg_ParseTuple(args,"i",&n))
    {
        return NULL;
    }

    return teamDistanceFromBall;
}


SkillType NaoBehavior::selectSkill() {


    worldModel->getRVSender()->clear();

    int _playerNumber = worldModel->getUNum();
    std::string SpNum = std::to_string(_playerNumber);
    int _playMode = worldModel->getPlayMode();
    WorldObject* _gameObject = worldModel->getWorldObject(_playerNumber);
    VecPosition _myPos = worldModel->getMyPosition();

    double* _teamMateDistances = NULL;
    double* _opponentDistances = NULL;

    _teamMateDistances = (double *) malloc(sizeof(double) * NUM_AGENTS);
    _opponentDistances = (double *) malloc(sizeof(double) * NUM_AGENTS);

    DistanceToBallArrayTeammates(_playerNumber,_teamMateDistances); 
    DistanceToBallArrayOpponents(_opponentDistances); 

    //Python Objects
    teamDistanceFromBall =  convertTeamDistanceToBall(_teamMateDistances);
    
    int regionX = getXFieldRegion(ball);
    int regionY = getYFieldRegion(ball);
    VecPosition partner = getPartnerPos(_playerNumber); 
    
    return SKILL_STAND;
}



static PyMethodDef myMethods[] = {
    {"sendTeamDistanceToBall",sendTeamDistanceToBall,METH_VARARGS,"sends team distance to ball"},
    {NULL,NULL,0,NULL}
};



static struct PyModuleDef RobocupWrapper = {
    PyModuleDef_HEAD_INIT,
    "RobocupWrapper",
    "Documentation",
    -1,
    myMethods
};

PyMODINIT_FUNC PyInit_RobocupWrapper(void)
{
    return PyModule_Create(&RobocupWrapper);
}




/*
 * Demo behavior where players form a rotating circle and kick the ball
 * back and forth
 */
SkillType NaoBehavior::demoKickingCircle() {
    
    // Parameters for circle
    VecPosition center = VecPosition(-HALF_FIELD_X/2.0, 0, 0);
    double circleRadius = 5.0;
    double rotateRate = 2.5;

    // Find closest player to ball
    int playerClosestToBall = -1;
    double closestDistanceToBall = 10000;
    for(int i = WO_TEAMMATE1; i < WO_TEAMMATE1+NUM_AGENTS; ++i) {
        VecPosition temp;
        int playerNum = i - WO_TEAMMATE1 + 1;
        if (worldModel->getUNum() == playerNum) {
            // This is us
            temp = worldModel->getMyPosition();
        } else {
            WorldObject* teammate = worldModel->getWorldObject( i );
            if (teammate->validPosition) {
                temp = teammate->pos;
            } else {
                continue;
            }
        }
        temp.setZ(0);

        double distanceToBall = temp.getDistanceTo(ball);
        if (distanceToBall < closestDistanceToBall) {
            playerClosestToBall = playerNum;
            closestDistanceToBall = distanceToBall;
        }
    }

    if (playerClosestToBall == worldModel->getUNum()) {
        // Have closest player kick the ball toward the center
        return kickBall(KICK_FORWARD, center);
    } else {
        // Move to circle position around center and face the center
        VecPosition localCenter = worldModel->g2l(center);
        SIM::AngDeg localCenterAngle = atan2Deg(localCenter.getY(), localCenter.getX());

        // Our desired target position on the circle
        // Compute target based on uniform number, rotate rate, and time
        VecPosition target = center + VecPosition(circleRadius,0,0).rotateAboutZ(360.0/(NUM_AGENTS-1)*(worldModel->getUNum()-(worldModel->getUNum() > playerClosestToBall ? 1 : 0)) + worldModel->getTime()*rotateRate);

        // Adjust target to not be too close to teammates or the ball
        target = collisionAvoidance(true /*teammate*/, false/*opponent*/, true/*ball*/, 1/*proximity thresh*/, .5/*collision thresh*/, target, true/*keepDistance*/);

        if (me.getDistanceTo(target) < .25 && abs(localCenterAngle) <= 10) {
            // Close enough to desired position and orientation so just stand
            return SKILL_STAND;
        } else if (me.getDistanceTo(target) < .5) {
            // Close to desired position so start turning to face center
            return goToTargetRelative(worldModel->g2l(target), localCenterAngle);
        } else {
            // Move toward target location
            return goToTarget(target);
        }
    }
}

SkillType NaoBehavior::BasicTree(VecPosition _myPos, int pNum, double* _teamMateDistances, double* _opponentDistances){
    
    //printf("PNUM : %d, X : %f, Y : %f, Z : %f\n",pNum, _myPos.getX(), _myPos.getY(), _myPos.getZ());
    
    std::string SpNum = std::to_string(pNum);

    if (pNum == 1){
        //printf("HERE\n");
        if(isClosestPlayertoBall(pNum, _teamMateDistances, _opponentDistances)){
            if(isSafeToKick(_opponentDistances)){
                if(isShootingRange(_myPos)){
                    worldModel->getRVSender()->drawCircle(SpNum,_myPos.getX(), _myPos.getY(),1,1,0,0); //RED
                    return kickBall(KICK_IK, VecPosition(HALF_FIELD_X, 0, 0));    
                }
                else{
                    VecPosition _closestTeammate = getClosestTeammatePos(pNum,_teamMateDistances);
                    worldModel->getRVSender()->drawCircle(SpNum,_myPos.getX(), _myPos.getY(),1,1,0.5,0); //ORANGE
                    return kickBall(KICK_IK, VecPosition(_closestTeammate.getX(), _closestTeammate.getY() + 5, 0));   
                }
            }
            else{
                worldModel->getRVSender()->drawCircle(SpNum,_myPos.getX(), _myPos.getY(),1,1,0,1); //PINK
                return kickBall(KICK_DRIBBLE, VecPosition(HALF_FIELD_X, 0, 0));
            }
        }
        else{
            worldModel->getRVSender()->drawCircle(SpNum,_myPos.getX(), _myPos.getY(),1,1,1,0); //YELLOW

            if(_teamMateDistances[pNum-1]<1){
                return kickBall(KICK_IK, VecPosition(HALF_FIELD_X, 0, 0));    
            }
            return SmartGoToTarget(ball,0.5);
        }
    }
    else{
        
        if(isClosestPlayertoBall(pNum, _teamMateDistances, _opponentDistances)){
            if(isSafeToKick(_opponentDistances)){
                if(isShootingRange(_myPos)){
                    worldModel->getRVSender()->drawCircle(SpNum,_myPos.getX(), _myPos.getY(),1,0,0.5,1); //BLUE
                    return kickBall(KICK_IK, VecPosition(HALF_FIELD_X, 0, 0));    
                }
                else{
                    VecPosition _closestTeammate = getClosestTeammatePos(pNum,_teamMateDistances);
                    worldModel->getRVSender()->drawCircle(SpNum,_myPos.getX(), _myPos.getY(),1,0,1,0.5); //BLUE-GREEN
                    return kickBall(KICK_IK, VecPosition(_closestTeammate.getX(), _closestTeammate.getY() + 5, 0));   
                }
            }
            else{
                worldModel->getRVSender()->drawCircle(SpNum,_myPos.getX(), _myPos.getY(),1,0,1,1); //CYAN
                return kickBall(KICK_DRIBBLE, VecPosition(HALF_FIELD_X, 0, 0));
            }
        }
        else{
            if(worldModel->distanceToMyGoal(ball) < 15){
                VecPosition target = VecPosition(ball.getX()-5,ball.getY(),0);
                target = ValidateFieldPos(target);
                worldModel->getRVSender()->drawCircle(SpNum,_myPos.getX(), _myPos.getY(),0,0,0,0); // WHITE
                return SmartGoToTarget(target,0.5);
            }
            else{
                VecPosition target = VecPosition(ball.getX()+5,ball.getY()-2,0);
                printf("Pnum = %d,Target x=%f,y=%f,z=%f",pNum,target.getX(),target.getY(),target.getZ());

                target = ValidateFieldPos(target);
                printf("PnumAdjusted = %d,Target x=%f,y=%f,z=%f",pNum,target.getX(),target.getY(),target.getZ());
                worldModel->getRVSender()->drawCircle(SpNum,_myPos.getX(), _myPos.getY(),1,0.5,0,1); //VIOLET
                return SmartGoToTarget(target,0.5);
            }

            /*
            if(isPossesion(_opponentDistances, _teamMateDistances)){
                VecPosition target = VecPosition(ball.getX()+5,ball.getY()-2,0);
                target = ValidateFieldPos(target);
                worldModel->getRVSender()->drawCircle(SpNum,_myPos.getX(), _myPos.getY(),1,0.5,0,1); //VIOLET
                return SmartGoToTarget(target);
            }
            else{
                VecPosition target = VecPosition(ball.getX()-5,ball.getY(),0);
                target = ValidateFieldPos(target);
                worldModel->getRVSender()->drawCircle(SpNum,_myPos.getX(), _myPos.getY(),0,0,0,0); // WHITE
                return SmartGoToTarget(target);
            }
            */
        }
        

    }
    
    worldModel->getRVSender()->drawCircle(SpNum,_myPos.getX(), _myPos.getY(),0,1,1,1); // BLACK
    return SKILL_STAND;

}

void NaoBehavior::DistanceToBallArrayTeammates(int mynum, double* _teamMateDistances){
    for(int i = WO_TEAMMATE1; i<WO_TEAMMATE1+NUM_AGENTS;i++){ //OUR PLAYERS
        WorldObject* teammate = worldModel->getWorldObject(i);
        VecPosition temp;

        if(i == mynum){
            temp = worldModel->getMyPosition();
        }
        else{
            temp = teammate->pos;
        }
        temp.setZ(0);

        float distance = temp.getDistanceTo(ball);
        _teamMateDistances[i-WO_TEAMMATE1] = distance;


        worldModel->getRVSender()->drawText("distTEAM",std::to_string(distance),temp.getX(),temp.getY()+2*mynum,1,1,1);
    }
}

void NaoBehavior::DistanceToBallArrayOpponents(double* _opponentDistances){
    for(int i = WO_OPPONENT1; i<WO_OPPONENT1+NUM_AGENTS;i++){ //OUR PLAYERS
        WorldObject* opponent = worldModel->getWorldObject(i);
        VecPosition temp;
        temp = opponent->pos;
        temp.setZ(0);

        float distance = temp.getDistanceTo(ball);
    
        _opponentDistances[i-WO_OPPONENT1] = distance;

        worldModel->getRVSender()->drawText("distOPP",std::to_string(distance),temp.getX(),temp.getY(),1,1,1);

    }
}

bool NaoBehavior::isClosestPlayertoBall(int pNum, double* _opponentDistances, double* _teamMateDistances){
    int arrlengthOpp = NUM_AGENTS;
    int arrlengthTeam = NUM_AGENTS;

    double minOppDis = MAXFLOAT; 
    for(int z=0;z<arrlengthOpp;++z){

        printf("pNum : %d oppnum : %d distance : %f\t",pNum,z,_opponentDistances[z]);
        if(_opponentDistances[z]< minOppDis){
            minOppDis = _opponentDistances[z];
        } 
	}
    printf("\n");
    double minTeamDis = MAXFLOAT; 
    for(int z=0;z<arrlengthTeam;++z){
        printf("pNum : %d teamnum : %d distance : %f\t",pNum,z,_teamMateDistances[z]);
        if(_teamMateDistances[z]< minTeamDis){
            minTeamDis = _teamMateDistances[z];
        } 
	}
    printf("\n");

    printf("minOpp = %f, minTeam = %f\n", minOppDis+1,minTeamDis);
    if(minOppDis+1 < minTeamDis){
        return false;
    }
    else{
        printf("_teamMateDistances = %f, minTeam = %f\n", _teamMateDistances[pNum-1],minTeamDis);
        if(minTeamDis != _teamMateDistances[pNum-1]){
            return false;
        }
        else{
            return true;
        }
    }
}

bool NaoBehavior::isPossesion(double* _opponentDistances, double* _teamMateDistances){


    int arrlengthOpp = NUM_AGENTS;
    int arrlengthTeam = NUM_AGENTS;

    double minOppDis = MAXFLOAT; 
    for(int z=0;z<arrlengthOpp;++z){
        if(_opponentDistances[z]< minOppDis){
            minOppDis = _opponentDistances[z];
        } 
	}
    double minTeamDis = MAXFLOAT; 
    for(int z=0;z<arrlengthTeam;++z){
        if(_teamMateDistances[z]< minTeamDis){
            minTeamDis = _teamMateDistances[z];
        } 
	}
    if(minOppDis < (minTeamDis*0.8)){   // this is important
        return false;
    }
    return true;
}

bool NaoBehavior::isClosestTeam(int _playerNumber, double* _teamMateDistances){
    int arrlengthTeam = NUM_AGENTS;

    //printf("Size = %d",arrlengthTeam);
    double minTeamDis = MAXFLOAT; 
    int id = -1;
    for(int z=0;z<arrlengthTeam;++z){
        if((_teamMateDistances[z]+1)< minTeamDis){
            minTeamDis = _teamMateDistances[z];
            id = z+1;
        } 
	}
    if(_playerNumber== id){
        return true;
    }
    return false;

}

bool NaoBehavior::isSafeToKick(double* _opponentDistances){
    double minOppDis = MAXFLOAT; 
    int arrlengthOpp = NUM_AGENTS;
    for(int z=0;z<arrlengthOpp;++z){
        if(_opponentDistances[z]< minOppDis){
            minOppDis = _opponentDistances[z];
        } 
	}
    if(minOppDis <1){
        return false;
    }
    return true;

}

bool NaoBehavior::isShootingRange(VecPosition _player){
    
    double distanceToGoal = worldModel->distanceToOppGoal(_player);

    if(distanceToGoal < 5){
        return true;
    }
    return false;

}

VecPosition NaoBehavior::getClosestTeammatePos(int _playerNumber,double* _teamMateDistances){
    int arrlengthTeam = NUM_AGENTS;

    //printf("Size = %d",arrlengthTeam);
    double minTeamDis = MAXFLOAT; 
    int id = -1;
    for(int z=0;z<arrlengthTeam;++z){
        if(_teamMateDistances[z]< minTeamDis){
            if(_playerNumber != z+1){
                minTeamDis = _teamMateDistances[z];
                id = z+1;
            }
        } 
	}

    return worldModel->getWorldObject(id)->pos;
    

}

VecPosition NaoBehavior::ValidateFieldPos(VecPosition target){
    if(target.getX() <= (-1*FIELD_X)/2){
        target.setX(2); 
    }
    else if(target.getX() >= FIELD_X/2 -1){
        target.setX(FIELD_X -2); 
    }

    if(target.getY() <= (-1*FIELD_Y)/2){
        target.setY(2);
    }
    else if(target.getY() >= FIELD_Y/2 -1){
        target.setY(FIELD_Y -2);
    }

    return target;
}

bool NaoBehavior::isFarToBall(int _playerNumber,double* _teamMateDistances){

    double distance = _teamMateDistances[_playerNumber-1];

    if(distance > 5){
        return true;
    }
    return false;

}

SkillType NaoBehavior::SmartGoToTarget(VecPosition target, double proximity){
    SIM::AngDeg localAngle = atan2Deg(ball.getY(), ball.getX());

    // Adjust target to not be too close to teammates or the ball
        target = collisionAvoidance(true /*teammate*/, true/*opponent*/, false/*ball*/, proximity/*proximity thresh*/, .5/*collision thresh*/, target, true/*keepDistance*/);

        if (me.getDistanceTo(target) < .25 && abs(localAngle) <= 10) {
            // Close enough to desired position and orientation so just stand
            return SKILL_STAND;
        } else if (me.getDistanceTo(target) < .5) {
            // Close to desired position so start turning to face ball
            return goToTargetRelative(worldModel->g2l(target), localAngle);
        } else {
            // Move toward target location
            return goToTarget(target);
        }
}

SkillType NaoBehavior::DribblingPairsSmartish() {
	int myNum = worldModel->getUNum();
	
	// Determine which two players are closest to the ball
    int playerClosestToBall = -1;
	int playerSecondClosestToBall = -1;
    double closestDistanceToBall = 10000;
	double SecondclosestDistanceToBall = 10000;
    for(int i = WO_TEAMMATE1; i < WO_TEAMMATE1+NUM_AGENTS; ++i) {
        VecPosition temp;
        int playerNum = i - WO_TEAMMATE1 + 1;
        if (worldModel->getUNum() == playerNum) {
            // This is us
            temp = worldModel->getMyPosition();
        } else {
            WorldObject* teammate = worldModel->getWorldObject( i );
            if (teammate->validPosition) {
                temp = teammate->pos;
            } else {
                continue;
            }
        }
        temp.setZ(0);

        double distanceToBall = temp.getDistanceTo(ball);
		if(distanceToBall < SecondclosestDistanceToBall){
		    if (distanceToBall < closestDistanceToBall) {
				playerSecondClosestToBall = playerClosestToBall;
		        playerClosestToBall = playerNum;

				SecondclosestDistanceToBall = closestDistanceToBall;	
		        closestDistanceToBall = distanceToBall;
		    }
			else{
				SecondclosestDistanceToBall = distanceToBall;
				playerSecondClosestToBall = playerNum;	
			}
		}
    }

    cout << "playerClosestToBall" << playerClosestToBall << endl;
    cout << "playerSecondClosestToBall" << playerSecondClosestToBall << endl;

	// Get the positions of the two closest players
	VecPosition SecondClosestPos = worldModel->getTeammate(playerSecondClosestToBall);
	VecPosition ClosestPos = worldModel->getTeammate(playerClosestToBall);


	VecPosition OppLeftGoalPost = worldModel->getOppLeftGoalPost();
	VecPosition OppRightGoalPost = worldModel->getOppRightGoalPost();

	VecPosition MyPos = worldModel->getMyPosition();
	VecPosition MyLast = worldModel->getMyLastPosition();
	VecPosition PosBetweenClosestAndSecond  = (ClosestPos + SecondClosestPos)/2;
	VecPosition PosBetweenSecondClosestAndTheirGoalPosition  = (OppRightGoalPost + SecondClosestPos)/2;

	cout << "MyPos" << MyPos<< endl;
	cout << "SecondClosestPos" << SecondClosestPos << endl;
	cout << "PosBetweenClosestAndSecond" << PosBetweenClosestAndSecond << endl;

	double distanceBallToGoal = worldModel->distanceToOppGoal(ball);
	
		 
	
	
	cout << "distanceBallToGoal" << distanceBallToGoal << endl;
	if(distanceBallToGoal > 5){
		if (playerClosestToBall == myNum) {
			return kickBall(KICK_FORWARD, PosBetweenSecondClosestAndTheirGoalPosition);
		}
		else{
			if(myNum==1){
				double distanceBetweenMeAndClosestPlayer = MyPos.getDistanceTo(ClosestPos);
				if(distanceBetweenMeAndClosestPlayer < 5){
					if(worldModel->distanceToOppGoal(MyPos) > 3){
						return goToTarget(OppLeftGoalPost);
					}
					else{
						return SKILL_STAND;
					}
				}
				else{
					return SKILL_STAND;
				}
			}
			else{
				double distanceBetweenMeAndClosestPlayer = MyPos.getDistanceTo(ClosestPos);
				if(distanceBetweenMeAndClosestPlayer < 5){
					if(worldModel->distanceToOppGoal(MyPos) > 3){
						return goToTarget(OppRightGoalPost);
					}
					else{
						return SKILL_STAND;
					}
				}
				else{
					return SKILL_STAND;
				}
			}
		}
	}
	else{
		if (playerClosestToBall == myNum) {
			return kickBall(KICK_IK, VecPosition(HALF_FIELD_X, 0, 0));
		}
		else{
			return goToTargetRelative(VecPosition(1,0,0), 15); // Circle
		}
	}
}


bool NaoBehavior::atDestination(VecPosition mypos, VecPosition target){
    double distance =  mypos.getDistanceTo(target);

    if(distance <0.4){
        return true;
    }
    return false;
}

SkillType NaoBehavior::FaceBall(VecPosition mypos){

    double distance, angle;
    getTargetDistanceAndAngle(ball, distance, angle);
    if (abs(angle) > 10) {
      return goToTargetRelative(mypos, angle);
    } else {
      return SKILL_STAND;
    }
}

SkillType NaoBehavior::FaceTarget(VecPosition mypos, VecPosition target){

    double distance, angle;
    getTargetDistanceAndAngle(target, distance, angle);
    if (abs(angle) > 10) {
      return goToTargetRelative(mypos, angle);
    } else {
      return SKILL_STAND;
    }
}



bool NaoBehavior::DangerClose(double* _opponentDistances){
    double minOppDis = MAXFLOAT; 
    int id = -1;
    for(int z=0;z<NUM_AGENTS;++z){
        if(_opponentDistances[z]< minOppDis){
            minOppDis = _opponentDistances[z];
            id = z;
        } 
	}

    id = id + WO_OPPONENT1;    

    if(minOppDis<1){

        WorldObject* closestopponent = worldModel->getWorldObject(id);
        VecPosition closestopponentpos = closestopponent->pos;

        double distogoal1 = closestopponentpos.getDistanceTo(VecPosition(-HALF_FIELD_X, 0, 0));
        double distogoal2 = ball.getDistanceTo(VecPosition(-HALF_FIELD_X, 0, 0));

        if(distogoal1>distogoal2){ //opponent on the right side of the ball to be a threat
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }

}

bool NaoBehavior::isOffensiveStrat(int pNum, double* _opponentDistances, double* _teamMateDistances){
    //return isPossesion(_opponentDistances, _teamMateDistances);

    if(isPossesion(_opponentDistances, _teamMateDistances)){

        if(isClosestTeam(pNum, _teamMateDistances)){
            return true;
        }
        else{
            if(DangerClose(_opponentDistances)){
                return false;
            }
            else{
                return true;
            }
        }


    }
    else{
        return false;
    }

}

int NaoBehavior::getXFieldRegion(VecPosition objpos){
    int x = objpos.getX();
    
    if(x <= -5){
        return 1;
    }
    else if(x <= 0 && x > -5){
        return 2;
    }
    else if(x<5 && x > 0){
        return 3;
    }
    else{
        return 4;
    }
}

int NaoBehavior::getYFieldRegion(VecPosition objpos){
    int y = objpos.getY();
    
    if(y>5){
        return 1;
    }
    else if(y<=5 && y> -5){
        return 2;
    }
    else{
        return 3;
    }
    
}

VecPosition NaoBehavior::getPartnerPos(int pNum){
    if(pNum == 1){
        return worldModel->getWorldObject(WO_TEAMMATE2)->pos;
    }
    else{
        return worldModel->getWorldObject(WO_TEAMMATE1)->pos;
    }
}

bool NaoBehavior::isInNeighbourhood(VecPosition obj, VecPosition target, double threshold){

    double distance =  obj.getDistanceTo(target);
    if(distance < threshold){
        return true;
    }
    return false;
}

VecPosition NaoBehavior::GetDesiredTarget(int pNum, VecPosition mypos, VecPosition partner, int regionX, int regionY, bool closest){
    if(regionX ==1){
        if(regionY ==1){
            if(closest){
                return VecPosition(-5, 8, 0);
            }
            else{
                return VecPosition(5,8,0); 
            }
        }
        else if(regionY ==2){
            if(closest){
                if(mypos.getY() > ball.getY()){
                    ///play downwards
                    return VecPosition(-5, -8, 0);
                }
                else{
                    ///play upwards
                    return VecPosition(-5, 8, 0);
                }
            }
            else{
                if(partner.getY() > ball.getY()){
                    ///play downwards
                    return VecPosition(5,-8,0);
                }
                else{
                    ///play upwards
                    return VecPosition(5,8,0);
                }
            }
        }
        else{
            if(closest){
                return VecPosition(-5, -8, 0);
            }
            else{
                return VecPosition(5,-8,0);
            }
        }
    }
    else if(regionX ==2){
        if(closest){
            if(ball.getY() > 0){
                return VecPosition(5, 8, 0);
            }
            else{
                return VecPosition(5, -8, 0);
            }
        }
        else{
            if(ball.getY() > 0){
                return VecPosition(5, 8, 0);
            }
            else{
                return VecPosition(5, -8, 0);
            }
        }

       
    }
    else if(regionX ==3){
        if(closest){
            return VecPosition(HALF_FIELD_X, 0, 0);
        }
        else{
            return VecPosition(4,FIELD_CENTER_Y,0);
        }
    }
    else{
        if(closest){
            

            if(isInNeighbourhood(partner, VecPosition(4,FIELD_CENTER_Y,0), 2)){
                double distmetogoal = mypos.getDistanceTo(VecPosition(HALF_FIELD_X, 0, 0));
                double partnertogoal = partner.getDistanceTo(VecPosition(HALF_FIELD_X, 0, 0));

                if(partnertogoal<distmetogoal){
                    return VecPosition(partner.getX()+2, partner.getY(), 0);
                }

            }



            if(ball.getY() > 0){
                return VecPosition(HALF_FIELD_X, -0.5, 0);
            }
            else{
                return VecPosition(HALF_FIELD_X, 0.5, 0);
            }


        }
        else{
            return VecPosition(8,FIELD_CENTER_Y,0);
        }
    }
}

bool NaoBehavior::isBetweenTargetAndBall(VecPosition target, VecPosition mypos, double threshold){
    double distanceballtarget = ball.getDistanceTo(target);
    double distanceballmetarget = ball.getDistanceTo(mypos) + mypos.getDistanceTo(target);



    
    double difference = abs(distanceballtarget - distanceballmetarget);
    if(difference < threshold){
        return true;
    }
    return false;
/*
    if (distance(A, C) + distance(B, C) == distance(A, B))
        return true; // C is on the line.
    return false;    // C is not on the line.

    or just:

    return distance(A, C) + distance(B, C) == distance(A, B);

    The way this works is rather simple. If C lies on the AB line, you'll get the following scenario:

    A-C------B

    and, regardless of where it lies on that line, dist(AC) + dist(CB) == dist(AB). For any other case, you have a triangle of some description and 'dist(AC) + dist(CB) > dist(AB)':

    A-----B
     \   /
      \ /
       C
*/

}