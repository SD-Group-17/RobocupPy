#include "naobehavior.h"
#include <Python.h>
#include<chrono>
#include "../rvdraw/rvdraw.h"


extern int agentBodyType;

/*
 * Real game beaming.
 * Filling params x y angle
 */
void NaoBehavior::beam( double& beamX, double& beamY, double& beamAngle ) {

    if(worldModel->getPlayMode() == 0){

        if(worldModel->getUNum() == 1){

		    beamX = -HALF_FIELD_X;
            beamY = 0;
            beamAngle = 0;
        }
        else if(worldModel->getUNum() == 2){
            VecPosition Pos2 = ball.Midpoint(VecPosition(-HALF_FIELD_X, 0, 0));
		    beamX = Pos2.getX();
            beamY = Pos2.getY();
            beamAngle = 0;
        }
        else if(worldModel->getUNum() == 3){
            VecPosition Pos2 = ball.Midpoint(VecPosition(-HALF_FIELD_X, 0, 0));
            VecPosition Pos3 = VecPosition(Pos2.getX()-1, Pos2.getY()+1, 0);
		    beamX = Pos3.getX();
            beamY = Pos3.getY();
            beamAngle = 0;
        }
        else if(worldModel->getUNum() == 4){
            VecPosition Pos2 = ball.Midpoint(VecPosition(-HALF_FIELD_X, 0, 0));
            VecPosition Pos4 = VecPosition(Pos2.getX()-1, Pos2.getY()-1, 0);
		    beamX = Pos4.getX();
            beamY = Pos4.getY();
            beamAngle = 0;
        }
        else if(worldModel->getUNum() == 5){
            VecPosition Pos5 = VecPosition(ball.getX()-1.5, ball.getY()+3 , 0);
		    beamX = Pos5.getX();
            beamY = Pos5.getY();
            beamAngle = 0;
        }
        else if(worldModel->getUNum() == 6){
            VecPosition Pos6 =  VecPosition(ball.getX()-1.5, ball.getY()-3 , 0);
		    beamX = Pos6.getX();
            beamY = Pos6.getY();
            beamAngle = 0;
        }
        else if(worldModel->getUNum() == 7){
            VecPosition Pos7 = VecPosition(ball.getX()-3, ball.getY(),0);
		    beamX = Pos7.getX();
            beamY = Pos7.getY();
            beamAngle = 0;
        }


    }
}


//SkillType NaoBehavior::GoalKeeperBehaviour(){

//}

vector<VecPosition> NaoBehavior::GenerateImportantPositions(int _playMode, int _side, int _playerNumber, int regionX, int regionY){


    vector<VecPosition> ImportantPositions;
    std::string SpNum = std::to_string(_playerNumber);

    VecPosition Pos1 = VecPosition(-HALF_FIELD_X+0.3,0,0); // Our Goal
    VecPosition Pos2 = ball.Midpoint(VecPosition(-HALF_FIELD_X, 0, 0)); // Middle of X formation of defenders
    VecPosition Pos3 = VecPosition(Pos2.getX()-2, Pos2.getY()+2, 0); // Back Up from mid X
    VecPosition Pos4 = VecPosition(Pos2.getX()-2, Pos2.getY()-2, 0); // Back DOwn from mid X
    VecPosition Pos5 = VecPosition(Pos2.getX()+2, Pos2.getY()+2, 0); // Forward Up from mid X
    VecPosition Pos6 = VecPosition(Pos2.getX()+2, Pos2.getY()-2, 0); // Forward DOwn from mid X
    VecPosition Pos7 = VecPosition(ball.getX()+ 3, ball.getY(),0); // Infront of ball

    VecPosition MidBoalGoal = ball.Midpoint(VecPosition(-HALF_FIELD_X, 0, 0));
    double offset = 0;

    SIM::Point2D ballp = SIM::Point2D(ball.getX(), ball.getY());
    SIM::Point2D orgoal = SIM::Point2D(-HALF_FIELD_X,0);
    SIM::Point2D offp = ballp.getPointOnLineFraction(orgoal,offset);
    VecPosition offsetPos = VecPosition(offp.getX(), offp.getY(), 0); 

    if(_playMode == PM_BEFORE_KICK_OFF){
        Pos1 = VecPosition(-HALF_FIELD_X+0.3,0,0); // Our Goal
        Pos2 = MidBoalGoal; // Middle of X formation of defenders
        Pos3 = VecPosition(Pos2.getX()-2, Pos2.getY()+2, 0); // Back Up from mid X
        Pos4 = VecPosition(Pos2.getX()-2, Pos2.getY()-2, 0); // Back DOwn from mid X
        Pos5 = VecPosition(ball.getX()-0.3, ball.getY()+3, 0); // Forward Up from ball
        Pos6 = VecPosition(ball.getX()-0.3, ball.getY()-3, 0); // Forward DOwn from ball
        Pos7 = VecPosition(ball.getX()-3, ball.getY(),0); // Behind ball
    }
    else if(_playMode == PM_KICK_OFF_LEFT){
        if(_side == SIDE_LEFT){
            Pos1 = VecPosition(-HALF_FIELD_X+0.3,0,0); // Our Goal
            Pos2 = MidBoalGoal; // Middle of X formation of defenders
            Pos3 = VecPosition(Pos2.getX()-2, Pos2.getY()+2, 0); // Back Up from mid X
            Pos4 = VecPosition(Pos2.getX()-2, Pos2.getY()-2, 0); // Back DOwn from mid X
            Pos5 = VecPosition(ball.getX()-0.3, ball.getY()+3, 0); // Forward Up from ball
            Pos6 = VecPosition(ball.getX()-0.3, ball.getY()-3, 0); // Forward DOwn from ball
            Pos7 = VecPosition(ball.getX(), ball.getY(),0); // On the ball
        }
        else{
            Pos1 = VecPosition(-HALF_FIELD_X+0.3,0,0); // Our Goal
            Pos2 = MidBoalGoal; // Middle of X formation of defenders
            Pos3 = VecPosition(Pos2.getX()-2, Pos2.getY()+2, 0); // Back Up from mid X
            Pos4 = VecPosition(Pos2.getX()-2, Pos2.getY()-2, 0); // Back DOwn from mid X
            Pos5 = VecPosition(ball.getX()-0.3, ball.getY()+3, 0); // Forward Up from ball
            Pos6 = VecPosition(ball.getX()-0.3, ball.getY()-3, 0); // Forward DOwn from ball
            Pos7 = VecPosition(ball.getX()-3, ball.getY(),0); // Behind ball
        }
    }
    else if(_playMode == PM_KICK_OFF_RIGHT){
        if(_side== SIDE_RIGHT){
            Pos1 = VecPosition(-HALF_FIELD_X+0.3,0,0); // Our Goal
            Pos2 = MidBoalGoal; // Middle of X formation of defenders
            Pos3 = VecPosition(Pos2.getX()-2, Pos2.getY()+2, 0); // Back Up from mid X
            Pos4 = VecPosition(Pos2.getX()-2, Pos2.getY()-2, 0); // Back DOwn from mid X
            Pos5 = VecPosition(ball.getX()-0.3, ball.getY()+3, 0); // Forward Up from ball
            Pos6 = VecPosition(ball.getX()-0.3, ball.getY()-3, 0); // Forward DOwn from ball
            Pos7 = VecPosition(ball.getX(), ball.getY(),0); // On the ball
        }
        else{
            Pos1 = VecPosition(-HALF_FIELD_X+0.3,0,0); // Our Goal
            Pos2 = MidBoalGoal; // Middle of X formation of defenders
            Pos3 = VecPosition(Pos2.getX()-2, Pos2.getY()+2, 0); // Back Up from mid X
            Pos4 = VecPosition(Pos2.getX()-2, Pos2.getY()-2, 0); // Back DOwn from mid X
            Pos5 = VecPosition(ball.getX()-0.3, ball.getY()+3, 0); // Forward Up from ball
            Pos6 = VecPosition(ball.getX()-0.3, ball.getY()-3, 0); // Forward DOwn from ball
            Pos7 = VecPosition(ball.getX()-3, ball.getY(),0); // Behind ball
        }
    }
    else if((_playMode == PM_FREE_KICK_LEFT) || (_playMode == PM_KICK_IN_LEFT) || (_playMode == PM_GOAL_KICK_LEFT)){
        if(_side == SIDE_LEFT){
            Pos1 = VecPosition(-HALF_FIELD_X+0.3,0,0); // Our Goal
            Pos2 = MidBoalGoal; // Middle of X formation of defenders
            Pos3 = VecPosition(Pos2.getX()-2, Pos2.getY()+2, 0); // Back Up from mid X
            Pos4 = VecPosition(Pos2.getX()-2, Pos2.getY()-2, 0); // Back DOwn from mid X
            Pos5 = VecPosition(ball.getX()-1, ball.getY()+2, 0); // Up from ball
            Pos6 = VecPosition(ball.getX()-1, ball.getY()-2, 0); // Down from ball
            Pos7 = VecPosition(ball.getX(), ball.getY(),0); // On ball
        }
        else {
            Pos1 = VecPosition(-HALF_FIELD_X+0.3,0,0); // Our Goal
            Pos2 = MidBoalGoal; // Middle of X formation of defenders
            Pos3 = VecPosition(Pos2.getX()-2, Pos2.getY()+2, 0); // Back Up from mid X
            Pos4 = VecPosition(Pos2.getX()-2, Pos2.getY()-2, 0); // Back DOwn from mid X
            Pos5 = VecPosition(ball.getX()-2, ball.getY()+3, 0); // Forward Up from ball
            Pos6 = VecPosition(ball.getX()-2, ball.getY()-3, 0); // Forward DOwn from ball
            Pos7 = VecPosition(ball.getX()-3, ball.getY(),0); // Behind ball
        }
    }
    else if((_playMode == PM_FREE_KICK_RIGHT) || (_playMode == PM_KICK_IN_RIGHT) || (_playMode == PM_GOAL_KICK_RIGHT)){
        if(worldModel->getSide() == SIDE_RIGHT){
            Pos1 = VecPosition(-HALF_FIELD_X+0.3,0,0); // Our Goal
            Pos2 = MidBoalGoal; // Middle of X formation of defenders
            Pos3 = VecPosition(Pos2.getX()-2, Pos2.getY()+2, 0); // Back Up from mid X
            Pos4 = VecPosition(Pos2.getX()-2, Pos2.getY()-2, 0); // Back DOwn from mid X
            Pos5 = VecPosition(ball.getX()-1, ball.getY()+2, 0); // Up from ball
            Pos6 = VecPosition(ball.getX()-1, ball.getY()-2, 0); // Down from ball
            Pos7 = VecPosition(ball.getX(), ball.getY(),0); // On ball
        }
        else {
            Pos1 = VecPosition(-HALF_FIELD_X+0.3,0,0); // Our Goal
            Pos2 = MidBoalGoal; // Middle of X formation of defenders
            Pos3 = VecPosition(Pos2.getX()-2, Pos2.getY()+2, 0); // Back Up from mid X
            Pos4 = VecPosition(Pos2.getX()-2, Pos2.getY()-2, 0); // Back DOwn from mid X
            Pos5 = VecPosition(ball.getX()-2, ball.getY()+3, 0); // Forward Up from ball
            Pos6 = VecPosition(ball.getX()-2, ball.getY()-3, 0); // Forward DOwn from ball
            Pos7 = VecPosition(ball.getX()-3, ball.getY(),0); // Behind ball
        }
    }
    else{ // PM_PLAY_ON 

        double yValue = MapValueInRangeTo(ball.getY(), -HALF_FIELD_Y, HALF_FIELD_Y, -HALF_GOAL_Y, HALF_GOAL_Y);

        Pos1 = VecPosition(-HALF_FIELD_X+0.3,yValue,0); // Our Goal
        Pos2 = MidBoalGoal; // Middle of X formation of defenders
        Pos3 = VecPosition(Pos2.getX()-2, Pos2.getY()+2, 0); // Back Up from mid X
        Pos4 = VecPosition(Pos2.getX()-2, Pos2.getY()-2, 0); // Back DOwn from mid X
        Pos5 = VecPosition(Pos2.getX()+2, Pos2.getY()+2, 0); // Forward Up from mid X
        Pos6 = VecPosition(Pos2.getX()+2, Pos2.getY()-2, 0); // Forward DOwn from mid X
        Pos7 = VecPosition(ball.getX(), ball.getY(),0); // Infront of ball

        if(regionX ==1){
            if(regionY ==1){

                offset = 0.2;
                offp = ballp.getPointOnLineFraction(orgoal,offset);
                offsetPos = VecPosition(offp.getX(), offp.getY(), 0); 

                Pos2 = offsetPos; // Middle of X formation of defenders
                Pos4 = VecPosition(Pos2.getX()-1, Pos2.getY()-1, 0); // Back DOwn from mid X
                Pos6 = VecPosition(Pos2.getX()+1, Pos2.getY()-1, 0); // Forward DOwn from mid X

                Pos3 = VecPosition(0, 5, 0);
                Pos5 = VecPosition(5,8,0); 
                Pos7 = VecPosition(-5,9,0); 
            }
            else if(regionY ==2){

                offset = 0.08;
                offp = ballp.getPointOnLineFraction(orgoal,offset);
                offsetPos = VecPosition(offp.getX(), offp.getY(), 0); 

                Pos2 = offsetPos; // Middle of X formation of defenders
                Pos3 = VecPosition(Pos2.getX()-0.5, Pos2.getY()+0.5, 0); // Back Up from mid X
                Pos4 = VecPosition(Pos2.getX()-0.5, Pos2.getY()-0.5, 0); // Back DOwn from mid X


                ///play downwards
                Pos6 =  VecPosition(-5, -8, 0);
                ///play upwards
                Pos5 =  VecPosition(-5, 8, 0);
                Pos7 = VecPosition(-5,0,0);
            }
            else{

                offset = 0.2;
                offp = ballp.getPointOnLineFraction(orgoal,offset);
                offsetPos = VecPosition(offp.getX(), offp.getY(), 0); 

                Pos2 = offsetPos; // Middle of X formation of defenders
                Pos3 = VecPosition(Pos2.getX()-1, Pos2.getY()+1, 0); // Back Up from mid X
                Pos5 = VecPosition(Pos2.getX()+1, Pos2.getY()+1, 0); // Forward Up from mid X

                Pos4 = VecPosition(0, -5, 0);
                Pos6 = VecPosition(5,-8,0);
                Pos7 = VecPosition(-5,-9,0); 
            }
        }
        else if(regionX ==2){

            offset = 0.1;
            offp = ballp.getPointOnLineFraction(orgoal,offset);
            offsetPos = VecPosition(offp.getX(), offp.getY(), 0); 

            Pos2 = offsetPos; // Middle of X formation of defenders
            Pos3 = VecPosition(Pos2.getX()-2, Pos2.getY()+2, 0); // Back Up from mid X
            Pos4 = VecPosition(Pos2.getX()-2, Pos2.getY()-2, 0); // Back DOwn from mid X

            float dist = VecPosition(0,0,0).getDistanceTo(ball);
            if(dist < 0.2){
                Pos5 = VecPosition(5, 8, 0);   
                Pos6 = VecPosition(0, 5, 0); 
                Pos7 = VecPosition(3, 3,0); 
            }
            else{
                if(ball.getY() > 0){
                Pos5 = VecPosition(5, 8, 0);   
                Pos6 = VecPosition(0, 5, 0); 
                Pos7 = VecPosition(3, 3,0); 
                }
                else{
                    Pos5 = VecPosition(5, -8, 0);
                    Pos6 = VecPosition(0, -5, 0); 
                    Pos7 = VecPosition(3, -3,0);
                }
            }

            
        }
        else if(regionX ==3){

            offset = 0.2;
            offp = ballp.getPointOnLineFraction(orgoal,offset);
            offsetPos = VecPosition(offp.getX(), offp.getY(), 0); 

            Pos2 = offsetPos; // Middle of X formation of defenders
            Pos3 = VecPosition(Pos2.getX()-2, Pos2.getY()+2, 0); // Back Up from mid X
            Pos4 = VecPosition(Pos2.getX()-2, Pos2.getY()-2, 0); // Back DOwn from mid X


            if(ball.getY() > 0){
                Pos5 = VecPosition(5, 5, 0);
                Pos6 = VecPosition(2, 2, 0);
                Pos7 = VecPosition(10,3,0);
            }
            else{
                Pos5 = VecPosition(5, -5, 0);
                Pos6 = VecPosition(2, -2, 0);
                Pos7 = VecPosition(10,-3,0);
            }
        }
        else{

            offset = 0.2;
            offp = ballp.getPointOnLineFraction(orgoal,offset);
            offsetPos = VecPosition(offp.getX(), offp.getY(), 0); 

            Pos2 = offsetPos; // Middle of X formation of defenders
            Pos3 = VecPosition(Pos2.getX()-2, Pos2.getY()+2, 0); // Back Up from mid X
            Pos4 = VecPosition(Pos2.getX()-2, Pos2.getY()-2, 0); // Back DOwn from mid X

            Pos5 = VecPosition(9, 0, 0);
            Pos6 = VecPosition(12, 2, 0);
            Pos7 = VecPosition(12,-2,0);
        }




    }

    

    

    //Pos1 = ValidateFieldPos(Pos1);
    Pos2 = ValidateFieldPos(Pos2);
    Pos3 = ValidateFieldPos(Pos3);
    Pos4 = ValidateFieldPos(Pos4);
    Pos5 = ValidateFieldPos(Pos5);
    Pos6 = ValidateFieldPos(Pos6);
    Pos7 = ValidateFieldPos(Pos7);

    // worldModel->getRVSender()->drawCircle(SpNum,Pos1.getX(), Pos1.getY(),0.2,1,1,1); //WHITE
    // worldModel->getRVSender()->drawCircle(SpNum,Pos2.getX(), Pos2.getY(),0.2,1,1,1); //WHITE
    // worldModel->getRVSender()->drawCircle(SpNum,Pos3.getX(), Pos3.getY(),0.2,1,1,1); //WHITE
    // worldModel->getRVSender()->drawCircle(SpNum,Pos4.getX(), Pos4.getY(),0.2,1,1,1); //WHITE
    // worldModel->getRVSender()->drawCircle(SpNum,Pos5.getX(), Pos5.getY(),0.2,1,1,1); //WHITE
    // worldModel->getRVSender()->drawCircle(SpNum,Pos6.getX(), Pos6.getY(),0.2,1,1,1); //WHITE
    // worldModel->getRVSender()->drawCircle(SpNum,Pos7.getX(), Pos7.getY(),0.2,1,1,1); //WHITE

    //worldModel->getRVSender()->drawCircle(SpNum,offsetPos.getX(),offsetPos.getY(),0.2,1,0,1); //PINK

    ImportantPositions.push_back(Pos1);
    ImportantPositions.push_back(Pos2);
    ImportantPositions.push_back(Pos3);
    ImportantPositions.push_back(Pos4);
    ImportantPositions.push_back(Pos5);
    ImportantPositions.push_back(Pos6);
    ImportantPositions.push_back(Pos7);

    

    return ImportantPositions;
}




/*  function which calls python functions from python files
 * 
 * 
 */

int pyFunction(PyObject * world_data, VecPosition &pos)
{
    //TODO: Edit this function to pass a PyList over to python
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("import os");
    PyRun_SimpleString("sys.path.append(\".\")");
    PyRun_SimpleString("sys.path.append(os.path.abspath(os.getcwd()) + \"/behaviors\")");
	PyObject *  pName = PyUnicode_FromString("strategyPy");
	PyObject * pModule = PyImport_Import(pName);

	if(pModule)
	{
		PyObject * pFunc = PyObject_GetAttrString(pModule, "selectSkill"); 
       
		if(pFunc && PyCallable_Check(pFunc))
		{
            //TODO, below function should not take "i", should take something else representing a PyList
            PyObject * pReturn = PyObject_CallFunction(pFunc,"O",world_data);
            PyObject * pSkill = PyList_GetItem(pReturn, 0);

            //convert postion to vector position
            PyObject * pyPos = PyList_GetItem(pReturn, 1);

            PyObject * xPy = PyList_GetItem(pyPos,0);
            PyObject * yPy = PyList_GetItem(pyPos,1);

            double x_coord  = PyFloat_AsDouble(xPy);
            double y_coord  = PyFloat_AsDouble(yPy);

            pos = VecPosition(x_coord,y_coord,0);
            int x = (int) PyLong_AsLong(pSkill);
			return x;
		}
		else
		{
            
			cout << "ERROR: function selectSkill()\n"<<endl;
            return -1;
		}

	}
	else
	{
        
		cout << "ERROR: Module not imported"<<endl;
        return -2;
	}

}


//C++ utility functions for python wrapper:
////////////////////////////////////////////////////////////////////////////////////////////
vector<pair<VecPosition, int > > NaoBehavior::teamPositions(int _playerNumber){

    vector<pair<VecPosition, int > > positions;
    
    for(int i = WO_TEAMMATE1; i<WO_TEAMMATE1+NUM_AGENTS;i++){ //OUR PLAYERS
        WorldObject* teammate = worldModel->getWorldObject(i);
        VecPosition temp;
        

        if(i == _playerNumber){
            temp = worldModel->getMyPosition();
        }
        else{
            temp = teammate->pos;
        }
        temp.setZ(0);
        /*
        //Converts VecPosition to vector containing x,y,x coordinates
        vector<double> coordinates;

        coordinates.push_back(temp.getX);
        coordinates.push_back(temp.getY);
        coordinates.push_back(temp.getZ);
        */
        pair<VecPosition, int > position;
        position.first = temp;
        position.second = i;

        positions.push_back(position);
    }
    
    return positions;
}

vector<pair<VecPosition, int > > NaoBehavior::opponentPositions(){

    vector<pair<VecPosition, int > > positions;

    for(int i = WO_OPPONENT1; i<WO_OPPONENT1+NUM_AGENTS;i++){ //OUR PLAYERS
        WorldObject* opponent = worldModel->getWorldObject(i);
        VecPosition temp;
        temp = opponent->pos;
        temp.setZ(0);

        /*
        vector<double> coordinates;

        coordinates.push_back(temp.getX);
        coordinates.push_back(temp.getY);
        coordinates.push_back(temp.getZ);
        */
        pair<VecPosition, int > position;
        position.first = temp;
        position.second = i;

        positions.push_back(position);
        
    }

    return positions;

}

////////////////////////////////////////////////////////////////////////////////////////////

//python wrapper PyObject utility functions:
PyObject * convertVecPos(VecPosition pos)
{
    PyObject * posPy = PyList_New(3);

    //wrapping x
    PyObject * temp = Py_BuildValue("f",pos.getX());
    PyList_SetItem(posPy,0,temp);

    //wrapping y
    temp = Py_BuildValue("f",pos.getY());
    PyList_SetItem(posPy,1,temp);

    //wrapping z
    temp = Py_BuildValue("f",pos.getZ());
    PyList_SetItem(posPy,2,temp);


    return posPy;
}

PyObject * distToball(vector<pair<double,int>> list)
{
    int n = list.size();
    pair<double,int> object;
    PyObject * pyList;
    PyObject* temp;
    PyObject * v1;
    PyObject * v2;

    pyList = PyList_New(n);

    for(int i =0;i<n;i++)
    {
        temp = PyList_New(2);
        object = list[i];

        //value 1
        v1 = Py_BuildValue("f",object.first);
        PyList_SetItem(temp,0,v1);

        //value2
        v2 = Py_BuildValue("i",object.second);
        PyList_SetItem(temp,1,v2);

        //updating list
        PyList_SetItem(pyList,i,temp);
    }

    return pyList;
}

PyObject * convertPlayerPositions(vector<pair<VecPosition, int > > positions)
{
    int n = positions.size();
    pair<VecPosition, int >  vecPos_num;
    VecPosition vecPos;
    int num;
    PyObject * pyList;
    PyObject* tuplePy;
    PyObject * vecPosPy;
    PyObject * numPy;

    pyList = PyList_New(n);

    for(int i =0;i<n;i++)
    {
        tuplePy = PyList_New(2);
        vecPos_num = positions[i];
        vecPos = vecPos_num.first;
        num = vecPos_num.second;

        //Convert vector position to pyobject, add to tuple
        vecPosPy = convertVecPos(vecPos);
        PyList_SetItem(tuplePy,0,vecPosPy);

        //Convert int player number to pyobject, add to tuple
        numPy = Py_BuildValue("i",num);
        PyList_SetItem(tuplePy,1,numPy);

        //append to list
        PyList_SetItem(pyList,i,tuplePy);
    }

    return pyList;
}

PyObject * worldData(PyObject *  _playerNumber,PyObject * _playMode,PyObject * _side,PyObject * posPy,PyObject * ballPy,PyObject *  teamPositionsPy,PyObject *  oppPositionsPy,PyObject * teamDistToBallPy,PyObject * OppDistToBallPy){
    
    //This mirrors constructor for Robocup class in Robocup.py
    
    PyObject * pyList;
    pyList = PyList_New(9);
    PyList_SetItem(pyList,0,_playerNumber);
    PyList_SetItem(pyList,1,_playMode);
    PyList_SetItem(pyList,2,_side);
    PyList_SetItem(pyList,3,posPy);    
    PyList_SetItem(pyList,4,ballPy);
    PyList_SetItem(pyList,5,teamPositionsPy);
    PyList_SetItem(pyList,6,oppPositionsPy);

    PyList_SetItem(pyList,7,teamDistToBallPy);
    PyList_SetItem(pyList,8,OppDistToBallPy);



    return pyList;

}

//////////////////////////////////////////////////////////////////////////////////////////

SkillType NaoBehavior::selectSkill() {

    using namespace std::chrono;
    int n = 0;

   
    // worldModel->getRVSender()->clear();

    int _playerNumber = worldModel->getUNum();
    std::string SpNum = std::to_string(_playerNumber);
    int _playMode = worldModel->getPlayMode();
    WorldObject* _gameObject = worldModel->getWorldObject(_playerNumber);
    VecPosition _myPos = worldModel->getMyPosition();
    _myPos.setZ(0);
    int _side = worldModel->getSide();
    vector<pair<double,int > > TeamDistToBall = GenerateTeamToTargetDistanceVector(_playerNumber, ball);
    vector<pair<double,int > > OppDistToBall = GenerateOppToTargetDistanceVector(ball);
    int regionX = getXFieldRegion(ball);
    int regionY = getYFieldRegion(ball);


    vector<VecPosition> ImportantPositions;
    ImportantPositions = GenerateImportantPositions(_playMode, _side, _playerNumber, regionX, regionY);
    vector<vector<pair<double,int > > > PreferenceToPointArray = GeneratePreferenceArrayForTeam(_playerNumber,ImportantPositions);
    vector<int> PointPreferences = stableMarriage(PreferenceToPointArray);
    

  
    
    //PYTHON LOGIC//
    //===================================================================================================================================================//
    Py_Initialize();
    PyObject * playerNumPy = Py_BuildValue("i",_playerNumber);
    PyObject * playModePy = Py_BuildValue("i",_playMode);
    PyObject * sidePy = Py_BuildValue("i",_side);
    PyObject * posPy = convertVecPos(_myPos);
    PyObject * ballPy = convertVecPos(ball);
    PyObject * teamDistToBallPy = distToball(TeamDistToBall);
    PyObject * OppDistToBallPy = distToball(OppDistToBall);
    PyObject * teamPositionsPy = convertPlayerPositions(teamPositions(_playerNumber));
    PyObject * oppPositionsPy = convertPlayerPositions(opponentPositions());
    PyObject * world_data = worldData(playerNumPy,playModePy,sidePy,posPy,ballPy, teamPositionsPy, oppPositionsPy ,teamDistToBallPy,OppDistToBallPy);
    VecPosition pos;
	n = pyFunction(world_data,pos);
    //==================================================================================================================================================//


    ///////////////////////////////////////C++ INTERFACE///////////////////////////////////////

    switch(n)
    {
        case 0:
            return SKILL_STAND;
        break;

        case 1:
            return goToTarget(pos);
        break;

        case 2:
            return kickBall(KICK_DRIBBLE,pos);
        break;

        case 3:
            return kickBall(KICK_FORWARD,pos);
        break;

        case 4:
            return kickBall(KICK_IK,pos);
        break;
    }


    
    

   
}
/////////////////////////////////////////////////////////////////////////////////////////


bool NaoBehavior::isClosestTeam(int _playerNumber, vector<pair<double,int > > TeamDistToBall){

    if(_playerNumber == TeamDistToBall[0].second){
        return true;
    }
    return false;

}

SkillType NaoBehavior::DetermineAppropriateKick(VecPosition _mypos, vector<pair<double,int > > OppDistToBall, VecPosition target){
    double minOppDis = OppDistToBall[0].first;
    int ClosestOppId = OppDistToBall[0].second;
    VecPosition ClosestOppPos = worldModel->getWorldObject(ClosestOppId)->pos;

    if(minOppDis <0.5){
        //worldModel->getRVSender()->drawCircle("KICK",target.getX(), target.getY(),0.1,0,0.5,1); //blue
        return kickBall(KICK_IK, target);
    }
    else if(minOppDis >4.2){
        //worldModel->getRVSender()->drawCircle("KICK",target.getX(), target.getY(),0.1,0,1,1); //light blue
        return kickBall(KICK_FORWARD, target);
    }
    else{
        if(ClosestOppPos.getX() > _mypos.getX()){
            //worldModel->getRVSender()->drawCircle("KICK",target.getX(), target.getY(),0.1,0,0.5,1); //blue
            return kickBall(KICK_IK, target);
        }
        else{
            //worldModel->getRVSender()->drawCircle("KICK",target.getX(), target.getY(),0.1,0,0,1); //dark blue
            return kickBall(KICK_DRIBBLE, target);
        }
        
    }
}

bool NaoBehavior::isSafeToKick(vector<pair<double,int > > OppDistToBall){
    double minOppDis = OppDistToBall[0].first;
    if(minOppDis <1){
        return false;
    }
    return true;

}


bool NaoBehavior::BallinGoalMouth(){
    double distanceToGoal = worldModel->distanceToOppGoal(ball);
    if(distanceToGoal < 2){

        if((ball.getY() > -HALF_GOAL_Y) && (ball.getY() < HALF_GOAL_Y)){
            return true;
        }

        return false;
    }
    return false;
}

bool NaoBehavior::isShootingRange(VecPosition _player){
    
    double distanceToGoal = worldModel->distanceToOppGoal(_player);

    if(distanceToGoal < 5){
        return true;
    }
    return false;

}

VecPosition NaoBehavior::getClosestTeammatePos(int _playerNumber,vector<pair<double,int > > TeamDistToBall){
    
    // cout << "Player Closest To Ball \n";
    // for (int i = 0; i < TeamDistToBall.size(); i++) {
    //     cout << "("
    //         << TeamDistToBall[i].first << ", "
    //         << TeamDistToBall[i].second << ") ";
    // }
    // cout << "\n"; 

    // cout << _playerNumber << "\n";


    int i=0;
    while(TeamDistToBall[i].second == _playerNumber){
        i++;
        //cout << TeamDistToBall[i].second << "\n";
    }
    //cout << "X=" << worldModel->getWorldObject(TeamDistToBall[i].second)->pos.getX() << "\n";

    return worldModel->getWorldObject(TeamDistToBall[i].second)->pos;
    
}

VecPosition NaoBehavior::ValidateFieldPos(VecPosition target){
    if(target.getX() <= (-1*FIELD_X)/2){
        target.setX((-1*FIELD_X)/2-0.1); 
    }
    else if(target.getX() >= FIELD_X/2){
        target.setX(FIELD_X/2 +0.1); 
    }

    if(target.getY() <= (-1*FIELD_Y)/2){
        target.setY((-1*FIELD_Y)/2-0.1);
    }
    else if(target.getY() >= FIELD_Y/2){
        target.setY(FIELD_Y/2 +0.1);
    }

    return target;
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
    if (abs(angle) > 30) {
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



bool NaoBehavior::DangerClose(vector<pair<double,int > > OppDistToBall){
    double minOppDis = OppDistToBall[0].first; 
    int id = OppDistToBall[0].second; 
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

/*bool NaoBehavior::isOffensiveStrat(int pNum, vector<pair<double,int > > TeamDistToBall, vector<pair<double,int > > OppDistToBall){
    //return isPossesion(_opponentDistances, _teamMateDistances);

    if(isPossesion(TeamDistToBall, OppDistToBall)){

        if(isClosestTeam(pNum, TeamDistToBall)){
            return true;
        }
        else{
            if(DangerClose(OppDistToBall)){
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

}*/

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

bool NaoBehavior::isInNeighbourhood(VecPosition obj, VecPosition target, double threshold){

    double distance =  obj.getDistanceTo(target);
    if(distance < threshold){
        return true;
    }
    return false;
}

bool NaoBehavior::isAnyTeammateInNeighbourhood(int pNum, VecPosition target, double threshold){

    for(int i = WO_TEAMMATE1; i<WO_TEAMMATE1+NUM_AGENTS;i++){ //OUR PLAYERS
        WorldObject* teammate = worldModel->getWorldObject(i);
        VecPosition temp;

        if(i == pNum){
            temp = worldModel->getMyPosition();
        }
        else{
            temp = teammate->pos;
        }
        temp.setZ(0);

        float distance = temp.getDistanceTo(target);
        if(distance < threshold){
            return true;
        }
    }
    return false;
}

VecPosition NaoBehavior::GetDesiredTargetAdvanced(int pNum, VecPosition mypos, int regionX, int regionY, vector<pair<double,int > > TeamDistToBall){
    if(regionX ==1){
        if(regionY ==1){
            return VecPosition(-4.5, 8, 0);
        }
        else if(regionY ==2){

            if(mypos.getY() > ball.getY()){
                ///play downwards
                return VecPosition(-4.5, -8, 0);
            }
            else{
                ///play upwards
                return VecPosition(-4.5, 8, 0);
            }
        }
        else{
            return VecPosition(-4.5, -8, 0);
        }
    }
    else if(regionX ==2){

        float dist = VecPosition(0,0,0).getDistanceTo(ball);
        if(dist < 0.2){
            return VecPosition(5.5, 8, 0);
        }

        if(ball.getY() > 0){
            return VecPosition(5.5, 8, 0);
        }
        else{
            return VecPosition(5.5, -8, 0);
        } 
    }
    else if(regionX ==3){


        VecPosition partner = getClosestTeammatePos(pNum,TeamDistToBall);
        //worldModel->getRVSender()->drawCircle("PASS Partner x3",partner.getX(), partner.getY(),0.7,1,1,0); //Yellow

        float dist = VecPosition(5,10,0).getDistanceTo(ball);
        if(dist < 0.2){
            return VecPosition(8, 3, 0);
        }

        if(ball.getY() > 0){
            return VecPosition(8, 3, 0);
        }
        else{
            return VecPosition(8, -3, 0);
        }

    }
    else{
        VecPosition partner = getClosestTeammatePos(pNum,TeamDistToBall);
        //worldModel->getRVSender()->drawCircle("PASS Partner x4",partner.getX(), partner.getY(),0.7,1,1,0); //Yellow

        if(partner.getX()> mypos.getX()+2 && mypos.getDistanceTo(partner) < 5){
            return VecPosition(partner.getX()+1, partner.getY(), 0);
        }

        if(ball.getY() > 0){
            return VecPosition(HALF_FIELD_X+0.3, -0.5, 0);
        }
        else{
            return VecPosition(HALF_FIELD_X+0.3, 0.5, 0);
        }
    }

    return mypos;
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

vector<pair<double,int > > NaoBehavior::GenerateTeamToTargetDistanceVector(int _playernumber, VecPosition target){

    target.setZ(0);
    vector<pair<double,int> > distances;

    for(int i = WO_TEAMMATE1; i<WO_TEAMMATE1+NUM_AGENTS;i++){ //OUR PLAYERS
        WorldObject* teammate = worldModel->getWorldObject(i);
        VecPosition temp;

        if(i == _playernumber){
            temp = worldModel->getMyPosition();
        }
        else{
            temp = teammate->pos;
        }
        temp.setZ(0);

        

        float distance = temp.getDistanceTo(target);

        if(worldModel->getFallenTeammate(i)){
            distance = distance+10;
        }

        pair<double, int> temppoint = {distance,i};
        distances.push_back(temppoint);


        //worldModel->getRVSender()->drawText("distTEAM",std::to_string(distance),temp.getX(),temp.getY()+2*mynum,1,1,1);

    }

    // if(_playernumber ==1){
    //     cout << "UNSORTED \n";
    //     for (int i = 0; i < distances.size(); i++) {
    //         cout << "("
    //             << distances[i].first << ", "
    //             << distances[i].second << ") ";
    //     }
    //     cout << "\n"; 
    // }
    sort(distances.begin(), distances.end());

    // if(_playernumber ==1){
    //     cout << "SORTED \n";
    //     for (int i = 0; i < distances.size(); i++) {
    //         cout << "("
    //             << distances[i].first << ", "
    //             << distances[i].second << ") ";
    //     }
    //     cout << "\n"; 
    // }

    return distances;


}

vector<pair<double,int > > NaoBehavior::GenerateOppToTargetDistanceVector(VecPosition target){

    vector<pair<double,int> > distances;
    target.setZ(0);

    for(int i = WO_OPPONENT1; i<WO_OPPONENT1+NUM_AGENTS;i++){ //OUR PLAYERS
        WorldObject* opponent = worldModel->getWorldObject(i);
        VecPosition temp;
        temp = opponent->pos;
        temp.setZ(0);

        float distance = temp.getDistanceTo(target);

        pair<double, int> temppoint = {distance,i};
        distances.push_back(temppoint);


        //worldModel->getRVSender()->drawText("distTEAM",std::to_string(distance),temp.getX(),temp.getY()+2*mynum,1,1,1);

    }

    sort(distances.begin(), distances.end());
    /* for (int i = 0; i < distances.size(); i++) {
        cout << "("
             << distances[i].first << ", "
             << distances[i].second << ") ";
    }
    cout << "\n"; */

    return distances;

}

vector<vector<pair<double,int >>> NaoBehavior::GeneratePreferenceArrayForTeam(int _playerNumber, vector<VecPosition> ImportantPositions){

    vector<vector<pair<double,int > > > PreferenceToPointArray;
    
    for(int i = WO_TEAMMATE1; i<WO_TEAMMATE1+NUM_AGENTS;i++){ //OUR PLAYERS
        WorldObject* teammate = worldModel->getWorldObject(i);
        VecPosition temp;

        if(i == _playerNumber){
            temp = worldModel->getMyPosition();
        }
        else{
            temp = teammate->pos;
        }
        temp.setZ(0);
        PreferenceToPointArray.push_back(GeneratePreferenceArrayForAnAgent(ImportantPositions,  temp));
    }
    
    return PreferenceToPointArray;
}




vector<pair<double,int > > NaoBehavior::GeneratePreferenceArrayForAnAgent(vector<VecPosition> ImportantPositions, VecPosition playerpos){
    vector<pair<double, double> > arr;

    for(int i=0;i<NUM_AGENTS;i++){
        pair<double, double> temp = {ImportantPositions[i].getX(),ImportantPositions[i].getY()};
        arr.push_back(temp);
    }
    int n = NUM_AGENTS;
    pair<double, double> p = {playerpos.getX(), playerpos.getY()};

    vector<pair<double,int > > sortedarr;
    sortedarr = sortArr(arr, n, p);
    return sortedarr;
}


// Function to sort the array of
// points by its distance from P
vector<pair<double,int > > NaoBehavior::sortArr(vector<pair<double, double> > arr,int n, pair<double, double> p)
{
  
    // Vector to store the distance
    // with respective elements
    vector<pair<double,int> > vp;
  
    // Storing the distance with its
    // distance in the vector array
    for (int i = 0; i < n; i++) {
  
        double dist
            = pow((p.first - arr[i].first), 2)
              + pow((p.second - arr[i].second), 2);
  
        vp.push_back(make_pair(dist,i));
    }
  
    // Sorting the array with
    // respect to its distance
    sort(vp.begin(), vp.end());
  
    // Output
    /* for (int i = 0; i < vp.size(); i++) {
        cout << "("
             << vp[i].first << ", "
             << vp[i].second << ") ";
    }
    cout << "\n"; */

    return vp;
}


// This function returns true if woman 'w' prefers man 'm1' over man 'm'
bool NaoBehavior::wPrefersM1OverM(int prefer[2*NUM_AGENTS][NUM_AGENTS], int w, int m, int m1)
{
    // Check if w prefers m over her current engagment m1
    for (int i = 0; i < NUM_AGENTS; i++)
    {
        // If m1 comes before m in lisr of w, then w prefers her
        // cirrent engagement, don't do anything
        if (prefer[w][i] == m1)
            return true;
  
        // If m cmes before m1 in w's list, then free her current
        // engagement and engage her with m
        if (prefer[w][i] == m)
           return false;
    }
}
  
// Determines stable matching for N Players and N Points. Players are numbered as 0 to
// N-1. Points are numbereed as N to 2N-1.
vector<int> NaoBehavior::stableMarriage(vector<vector<pair<double,int > > > PreferenceToPointArray)
{
    // Convert vector to 2D array
    int prefer[2*NUM_AGENTS][NUM_AGENTS];

    for(int i=0;i<NUM_AGENTS;i++){
        for(int j=0;j<NUM_AGENTS;j++){
            prefer[i][j] = PreferenceToPointArray[i][j].second;
            prefer[i+NUM_AGENTS][j] = j;
        }
    }

    // Stores partner of Points. This is our output array that
    // stores paring information.  The value of wPartner[i]
    // indicates the partner assigned to Point N+i.  Note that
    // the Points number between N and 2*N-1. The value -1
    // indicates that (N+i)'th point is free
    int wPartner[NUM_AGENTS];
  
    // An array to store availability of Players.  If mFree[i] is
    // false, then player 'i' is free, otherwise engaged.
    bool mFree[NUM_AGENTS];
  
    // Initialize all players and points as free
    memset(wPartner, -1, sizeof(wPartner));
    memset(mFree, false, sizeof(mFree));
    int freeCount = NUM_AGENTS;
  
    //for (int p=0;p<NUM_AGENTS;p++){
    //    cout << wPartner[p] << "\n";
    //}


    // While there are free players
    while (freeCount > 0)
    {
        // Pick the first free player (we could pick any)
        int m;
        for (m = 0; m < NUM_AGENTS; m++)
            if (mFree[m] == false)
                break;
  
        // One by one go to all points according to m's preferences.
        // Here m is the picked free player
        for (int i = 0; i < NUM_AGENTS && mFree[m] == false; i++)
        {
            int w = prefer[m][i];

            // The point of preference is free, w and m become
            // partners (Note that the partnership maybe changed
            // later). So we can say they are engaged not married

            if (wPartner[w] == -1)
            {
                wPartner[w] = m;
                mFree[m] = true;
                freeCount--;
            }
            else  // If w is not free
            {
                // Find current engagement of w
                int m1 = wPartner[w];
  
                // If w prefers m over her current engagement m1,
                // then break the engagement between w and m1 and
                // engage m with w.
                if (wPrefersM1OverM(prefer, w, m, m1) == false)
                {
                    wPartner[w] = m;
                    mFree[m] = true;
                    mFree[m1] = false;
                }
            } // End of Else
        } // End of the for loop that goes to all points in m's list
    } // End of main while loop
  
  
    // Print the solution
    /* cout << "Point   Player" << endl;
    for (int i = 0; i < NUM_AGENTS; i++)
       cout << " " << i << "\t" << wPartner[i] << endl; */


    vector<int> v(std::begin(wPartner), std::end(wPartner));
    return v;   
}

double NaoBehavior::MapValueInRangeTo(double input, double input_start, double input_end, double output_start, double output_end){

    double output = output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start);
    return output;
}
