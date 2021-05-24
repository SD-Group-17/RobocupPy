#include <vector>
#include <cmath>
#include <stdio.h>
#include "pyhelper.hpp"
#include <iostream>
#define PY_SSIZE_T_CLEAN

using namespace std;

/* TODO: Python Variables
 
// PyObject* world;
// PyObject* teamDistanceFromBall;
//calling python code
//PyObject* myModuleString = PyString_FromString((char*)"robopy");
//PyObject* myModule = PyImport_Import(myModuleString);
//PyObject* myFunction = PyObject_GetAttrString(myModule,(char*)"hello");
*/

//support methods and classes:
class worldmodelWrap{

    
    vector<vector<float>> teammates;
    vector<float> myPosition;
    vector<float> ball;
    int UNum;
    int NUMAGENTS;
    
    public:
    worldmodelWrap(vector<vector<float>> teammatesIN,  vector<float> ballIN,  int UNumIN, int NUMAGENTSIN){
        teammates = teammatesIN;
        myPosition =teammatesIN[UNumIN];
        ball = ballIN;
        UNum = UNumIN;
        NUMAGENTS = NUMAGENTSIN;
        
    }


    float getDistance(vector<float>pos1,vector<float>pos2){
        return sqrt( pow( pos1[0] - pos2[0],2) + pow(pos1[1] - pos2[1],2) );
    }

    int getUNum(){
        return UNum;
    }

    vector<vector<float>> getTeammates(){
        return teammates;
    }
    int getNUMAGENTS(){
        return NUMAGENTS;
    }

    vector<float> getMyPosition(){
        return myPosition;
    }

    vector<float> getBall(){
        return ball;
    }

};

worldmodelWrap testWorldModel(){
    vector<vector<float>> teammatesIN(11,vector<float>(2,1.0)); //coordinates of each player
    vector<float> ballIN(2,0.0); //ball coordinate
    int UNumIN = 0; //my player number
    int NUMAGENTSIN = 11; //number of players


    worldmodelWrap instance(teammatesIN, ballIN, UNumIN, NUMAGENTSIN);

    return instance;
}

//Strategy cc classes:



//Wrapper methods:
/*
PyObject * distance(PyObject * self,PyObject* args)
{   

    float pos1x;
    float pos1y;
    float pos2x;
    float pos2y;

    if(!PyArg_ParseTuple(args,"ffff",&pos1x,&pos1y ,&pos2x ,&pos2y))
    {
        return NULL;
    }
    worldmodelWrap worldmodel = testWorldModel();

    vector<float> pos1(2,0.0);
    vector<float> pos2(2,0.0);

    pos1[0] = pos1x;
    pos1[1] = pos1y;
    pos2[0] = pos2x;
    pos2[1] = pos2y;



    return Py_BuildValue("f",worldmodel.getDistance(pos1,pos2) );

}
*/

PyObject * sendTeamDistanceToBall(PyObject * self,PyObject* args)
{
    int n;

    if(!PyArg_ParseTuple(args,"i",&n))
    {
        return NULL;
    }

     //instance features
    vector<float> playersPos;
    
    vector<float> ballIn;
    int uNumIn = 0;
    int NumAgentsIn = 11;
    vector<worldmodelWrap> eachInstance; 

    //Team =(2.0,1.0), ball = (13.0,15.0)
    playersPos = {2.0,1.0};
    vector< vector<float> > teamMatesIn(1, playersPos);
    ballIn = {13.0, 15.0};
    worldmodelWrap wm1 = worldmodelWrap(teamMatesIn,ballIn, uNumIn, NumAgentsIn);
    eachInstance.push_back(wm1);
    

    //Team = (20.0,20.0), ball = (10.0,5.0)
    playersPos = {20.0, 20.0};
    vector< vector<float> > teamMatesIn1(1, playersPos);
    ballIn = {10.0, 5.0};
    worldmodelWrap wm2 = worldmodelWrap(teamMatesIn1,ballIn, uNumIn, NumAgentsIn);
    eachInstance.push_back(wm2);


    //Team = (5.0,18.0), ball = (0.0,20.0)
    playersPos = {5.0, 18.0};
    vector< vector<float> > teamMatesIn2(1, playersPos);
    ballIn = {0.0, 20.0};
    worldmodelWrap wm3 = worldmodelWrap(teamMatesIn2,ballIn, uNumIn, NumAgentsIn);
    eachInstance.push_back(wm3);

    PyObject *teamDisTotal = PyList_New(eachInstance.size());

    for (unsigned k=0; k < eachInstance.size(); k++){
        vector< vector<float> > teamPosC = eachInstance[k].getTeammates(); //[[2.0,1.0]]
        vector<float> ballPosC = eachInstance[k].getBall();
        //PyObject * teamPosPy = PyList_New(teamPosC.size());
        PyObject * value;
        for(unsigned i =0; i<teamPosC.size();++i){
            double distance = eachInstance[k].getDistance(teamPosC[i], ballPosC);
           // ceil(distance)
            value = Py_BuildValue("f",distance);

            //PyList_SetItem(teamPosPy,i,value);
        }
        PyList_SetItem(teamDisTotal,k,value);
    }

    return teamDisTotal;
}

PyObject * sendBallPos(PyObject * self,PyObject* args)
{
    
    int n;
    if(!PyArg_ParseTuple(args,"i",&n))
    {
        return NULL;
    }

    //instance features
    vector<vector< float> > teamMatesIn;
    vector<float> ballIn;
    int uNumIn;
    int NumAgentsIn;
    vector<int> ballPos;

    vector<worldmodelWrap> eachInstance;
    //(2,0)
    vector<float> playersPos(2,0.0);
    playersPos[0] = 2; playersPos[1] = 0.0;
    vector< vector<float> > teamMatesIn1(11, playersPos);
    vector<float> ballIn1{2.0,0.0};
    uNumIn = 0;
    NumAgentsIn = 11;
    worldmodelWrap worldmodel = worldmodelWrap(teamMatesIn1,ballIn1, uNumIn, NumAgentsIn);
    
    eachInstance.push_back(worldmodel);

    //(0,0)
    vector<float> ballIn2{0.0,0.0};
    worldmodelWrap worldmodel2 = worldmodelWrap(teamMatesIn1,ballIn2, uNumIn, NumAgentsIn);
    eachInstance.push_back(worldmodel2);


    //(0,2)
    vector<float> ballIn3{0.0,2.0};
    worldmodelWrap worldmodel3 = worldmodelWrap(teamMatesIn1,ballIn3, uNumIn, NumAgentsIn);
    eachInstance.push_back(worldmodel3);
    
    PyObject *ballPosPyTotal = PyList_New(3);
    for(unsigned i = 0; i < eachInstance.size(); i++){
        worldmodelWrap worldModelInstance = eachInstance[i];

        vector<float> ballPosC = worldModelInstance.getBall();
        PyObject * ballPosPy = PyList_New(ballPosC.size());
        PyObject * pyValue;

        for(unsigned j =0; j<ballPosC.size();++j){
            double value = ballPosC[j];
            pyValue = Py_BuildValue("f",value);
            PyList_SetItem(ballPosPy,j,pyValue);
        }

        

        PyList_SetItem(ballPosPyTotal, i, ballPosPy);

        // PyList_SetItem(ball,0,Py_BuildValue("i",ballx));
        // PyList_SetItem(ball,1,Py_BuildValue("i",bally));

    }
    

    return ballPosPyTotal;
}

PyObject * sendMyPos(PyObject * self,PyObject* args)
{
    int n;
    if(!PyArg_ParseTuple(args,"i",&n))
    {
        return NULL;
    }

    //instance features
    vector<float> playersPos; 
    
    vector<float> ballIn(2, 1.0);
    int uNumIn;
    int NumAgentsIn = 11;
    vector<worldmodelWrap> eachInstance; 
    PyObject * myPlayerPosPyTotal = PyList_New(3);

    
    //my players pos = 0
    playersPos = {2.0, 1.0};
    vector<vector< float> > teamMatesIn(11, playersPos);
    uNumIn = 0;
    worldmodelWrap wmw1 = worldmodelWrap(teamMatesIn,ballIn, uNumIn, NumAgentsIn);
    eachInstance.push_back(wmw1);
    cout << eachInstance.size() << endl;


    //my player pos = 3
    playersPos = {5.0, 10.0};
    for(int i = 0; i<teamMatesIn.size(); i++){
	    teamMatesIn[i] = playersPos;
    }
    uNumIn = 3;
    worldmodelWrap wmw2 = worldmodelWrap(teamMatesIn,ballIn, uNumIn, NumAgentsIn);
    eachInstance.push_back(wmw2);

    //my player pos = 6
    playersPos = {12.0, 4.0};
  
    for(int i = 0; i<teamMatesIn.size(); i++){
	    teamMatesIn[i] = playersPos;
    }
	
    uNumIn = 6;
    worldmodelWrap wmw3 = worldmodelWrap(teamMatesIn,ballIn, uNumIn, NumAgentsIn);
    eachInstance.push_back(wmw3);
   

    for(unsigned k = 0; k < eachInstance.size(); k++){

        worldmodelWrap wmw = eachInstance[k];
        vector<float> myPlayerPosC = wmw.getMyPosition(); //myPlayerPos has 2 values
        PyObject * myPlayerPosPy = PyList_New(myPlayerPosC.size()); 
        PyObject * hold;

        for(unsigned i =0; i<myPlayerPosC.size() ; ++i){
            hold = Py_BuildValue("f",myPlayerPosC[i]);
            PyList_SetItem(myPlayerPosPy, i, hold);
        }

        PyList_SetItem(myPlayerPosPyTotal,k,myPlayerPosPy); 

    }
    
    return myPlayerPosPyTotal; //[[2.0, 1.0], [5.0, 10.0], [12.0, 4.0]]
}

PyObject * sendTeamPos(PyObject * self,PyObject* args)
{
    int n;

    if(!PyArg_ParseTuple(args,"i",&n))
    {
        return NULL;
    }

    //instance features
    vector<float> playersPos;
    vector<vector< float> > teamMatesIn;
    vector<float> ballIn = {1.0, 1.0};
    int uNumIn = 0;
    int NumAgentsIn = 11;
    vector<worldmodelWrap> eachInstance; 

    //(2.0,1.0)
    playersPos = {2.0,1.0};
    teamMatesIn = {1, playersPos};
    worldmodelWrap wm1 = worldmodelWrap(teamMatesIn,ballIn, uNumIn, NumAgentsIn);
    eachInstance.push_back(wm1);
    

    //(8.0,9.0)
    playersPos = {8.0, 9.0};
    teamMatesIn = {1, playersPos};
    worldmodelWrap wm2 = worldmodelWrap(teamMatesIn,ballIn, uNumIn, NumAgentsIn);
    eachInstance.push_back(wm2);


    //(20.0,10.0)
    playersPos = {20.0, 10.0};
    teamMatesIn = {1, playersPos};
    worldmodelWrap wm3 = worldmodelWrap(teamMatesIn,ballIn, uNumIn, NumAgentsIn);
    eachInstance.push_back(wm3);

    PyObject *teamPosTotal = PyList_New(eachInstance.size());

    for(unsigned k = 0; k < eachInstance.size(); k++ ){
        
        worldmodelWrap wmw = eachInstance[k];
        vector<vector< float> > teamPosC = wmw.getTeammates(); //teamPosC has 1 value
        PyObject * teamPosPy = PyList_New(teamPosC.size()); //teamPosPy has 1 value
        PyObject * row;
        PyObject * value;

        for(unsigned i =0; i<teamPosC.size() ; ++i){
            row = PyList_New(teamPosC[i].size()); //2 elements 
            
            for(unsigned j = 0; j < teamPosC[i].size();++j){ //run twice
                value = Py_BuildValue("f",teamPosC[i][j]);
            
                PyList_SetItem(row,j,value); 
            }
            
            PyList_SetItem(teamPosPy,i,row);
        }

        PyList_SetItem(teamPosTotal,k,row); 
    }
    
    
    return teamPosTotal; //[[2.0,1.0],[8.0,9.0],[20.0,10.0]]
}


PyObject * sendUNum(PyObject * self,PyObject* args)
{
    int n;

    //instance features
    vector<float> playersPos = {2.0,1.0};
    vector< vector<float> > teamMatesIn = {11, playersPos};
    vector<float> ballIn = {1.0, 1.0};
    int uNumIn;
    int NumAgentsIn = 11;
    vector<worldmodelWrap> eachInstance;

    if(!PyArg_ParseTuple(args,"i",&n))
    {
        return NULL;
    }

    // playernun = 0
    uNumIn = 0;
    worldmodelWrap wm = worldmodelWrap(teamMatesIn,ballIn, uNumIn, NumAgentsIn);
    eachInstance.push_back(wm);


    // playernum = 5
    uNumIn = 5;
    worldmodelWrap wm1 = worldmodelWrap(teamMatesIn,ballIn, uNumIn, NumAgentsIn);
    eachInstance.push_back(wm1);

    // playernum = 10
    uNumIn = 10;
    worldmodelWrap wm2 = worldmodelWrap(teamMatesIn,ballIn, uNumIn, NumAgentsIn);
    eachInstance.push_back(wm2);        

    PyObject * pyvalue;
    PyObject * totalAgentsPy = PyList_New(eachInstance.size());

    for(unsigned i = 0; i < eachInstance.size(); ++i){
        worldmodelWrap worldmodelInstance = eachInstance[i];
        int uNumC = worldmodelInstance.getUNum();
        pyvalue = Py_BuildValue("i",uNumC);
        PyList_SetItem(totalAgentsPy,i,pyvalue);
    }

    return totalAgentsPy; //[0,5,10]
}

PyObject * sendNUMAGENTS(PyObject * self,PyObject* args)
{
    int n;

    //instance features
    vector<vector< float> > teamMatesIn;
    vector<float> ballIn;
    int uNumIn;
    int NumAgentsIn;

    if(!PyArg_ParseTuple(args,"i",&n))
    {
        return NULL;
    }

    vector<worldmodelWrap> eachInstance;

    // Total players = 11
    vector<float> playersPos = {2.0,1.0};
    teamMatesIn = {11, playersPos};
    ballIn = {1.0,1.0};
    uNumIn = 0;
    NumAgentsIn = 11;
    worldmodelWrap wm = worldmodelWrap(teamMatesIn,ballIn, uNumIn, NumAgentsIn);
    eachInstance.push_back(wm);


    // Total players = 5 
    teamMatesIn = {5, playersPos};
    NumAgentsIn = 5;
    worldmodelWrap wm1 = worldmodelWrap(teamMatesIn,ballIn, uNumIn, NumAgentsIn);
    eachInstance.push_back(wm1);

    // Total players = 0 
    teamMatesIn = {1, playersPos};
    NumAgentsIn = 1;
    worldmodelWrap wm2 = worldmodelWrap(teamMatesIn,ballIn, uNumIn, NumAgentsIn);
    eachInstance.push_back(wm2);        

    PyObject * pyvalue;
    PyObject * totalAgentsPy = PyList_New(eachInstance.size());

  
    for(unsigned i = 0; i < eachInstance.size(); ++i){
        worldmodelWrap worldmodelInstance = eachInstance[i];
        int NUMAGENTS = worldmodelInstance.getNUMAGENTS();
        pyvalue = Py_BuildValue("i",NUMAGENTS);
        PyList_SetItem(totalAgentsPy,i,pyvalue);
    }
    
    return totalAgentsPy; //[11,5,0]
}



//Calls python function selectSkill() in strategy.py and prints the output
int selectSkill(){
    CPyInstance hInstance;

	CPyObject pName = PyUnicode_FromString("strategy"); //name of python file
	CPyObject pModule = PyImport_Import(pName);

	if(pModule)
	{
		CPyObject pFunc = PyObject_GetAttrString(pModule, "selectSkill"); //name of python function
		if(pFunc && PyCallable_Check(pFunc))
		{
			CPyObject pValue = PyObject_CallObject(pFunc, NULL); //output of python function as c++ object

			return (int) PyLong_AsLong(pValue);
		}
		else
		{
			cout << "ERROR: function selectSkill()\n";
            return -1;
		}

	}
	else
	{
		cout << "ERROR: Module not imported\n";
        return -1;
	}
}




/*
TODO
figure out how to make this function be called on
EDIT: this function is no longer called upon
void selectSkill(worldmodelWrap worldmodel) {
    NUMAGENTS = worldModel->getNUMAGENTS();
    int _playerNumber = worldModel->getUNum();
    double* _teamMateDistances = NULL;
    double* _opponentDistances = NULL;
    _teamMateDistances = (double *) malloc(sizeof(double) * NUM_AGENTS);
    DistanceToBallArrayTeammates(_playerNumber,_teamMateDistances, worldmodel); 
    //Python Objects
    teamDistanceFromBall =  convertTeamDistanceToBall(_teamMateDistances);
    
    
}
*/


static PyMethodDef myMethods[] = {
    {"sendTeamDistanceToBall",sendTeamDistanceToBall,METH_VARARGS,"sends team distance to ball"},
    {"sendBallPos",sendBallPos,METH_VARARGS,"sends ball coordinates"},
    {"sendMyPos",sendMyPos,METH_VARARGS,"sends this player's coordinates"},
    {"sendTeamPos",sendTeamPos,METH_VARARGS,"sends team coordinates"},
    {"sendUNum",sendUNum,METH_VARARGS,"sends this player's number "},
    {"sendNUMAGENTS",sendNUMAGENTS,METH_VARARGS,"sends this number of players"},
    {"distance",distance,METH_VARARGS,"returns the float distance between two points"},

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

    