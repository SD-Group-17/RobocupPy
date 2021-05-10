#include <vector>
#include <cmath>
#include <stdio.h>
#include <Python.h>
#include <pyhelper.hpp>
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


PyObject * sendTeamDistanceToBall(PyObject * self,PyObject* args)
{
    int n;

    if(!PyArg_ParseTuple(args,"i",&n))
    {
        return NULL;
    }

    
    worldmodelWrap worldmodel = testWorldModel();
    vector<vector<float>> teamPosC = worldmodel.getTeammates();
    vector<float> ballPosC = worldmodel.getBall();
    PyObject * teamPosPy = PyList_New(teamPosC.size());
    PyObject * value;
    for(int i =0; i<teamPosC.size();++i){
        float distance = worldmodel.getDistance(teamPosC[i], ballPosC ) ;
        value = Py_BuildValue("f",distance);
        PyList_SetItem(teamPosPy,i,value);
        
        
    }
    
    return teamPosPy;
}

PyObject * sendBallPos(PyObject * self,PyObject* args)
{
    int n;

    if(!PyArg_ParseTuple(args,"i",&n))
    {
        return NULL;
    }

    
    worldmodelWrap worldmodel = testWorldModel();
    vector<float> ballPosC = worldmodel.getBall();
    PyObject * ballPosPy = PyList_New(ballPosC.size());
    PyObject * pyValue;
    for(int i =0; i<ballPosC.size();++i){
        double value = ballPosC[i];
        pyValue = Py_BuildValue("f",value);
        PyList_SetItem(ballPosPy,i,pyValue);
    }
    
    return ballPosPy;
}

PyObject * sendMyPos(PyObject * self,PyObject* args)
{
    int n;

    if(!PyArg_ParseTuple(args,"i",&n))
    {
        return NULL;
    }

    
    worldmodelWrap worldmodel = testWorldModel();
    vector<float> ballPosC = worldmodel.getMyPosition();
    PyObject * ballPosPy = PyList_New(ballPosC.size());
    PyObject * pyValue;
    for(int i =0; i<ballPosC.size();++i){
        double value = ballPosC[i];
        pyValue = Py_BuildValue("f",value);
        PyList_SetItem(ballPosPy,i,pyValue);
    }
    
    return ballPosPy;
}

PyObject * sendTeamPos(PyObject * self,PyObject* args)
{
    int n;

    if(!PyArg_ParseTuple(args,"i",&n))
    {
        return NULL;
    }

    
    worldmodelWrap worldmodel = testWorldModel();
    vector<vector<float>> teamPosC = worldmodel.getTeammates();
    PyObject * teamPosPy = PyList_New(teamPosC.size());
    PyObject * row;
    PyObject * value;
    for(int i =0; i<teamPosC.size();++i){
        row = PyList_New(teamPosC[i].size());
        for(int j = 0; j < teamPosC[i].size();++j){
            value = Py_BuildValue("f",teamPosC[i][j]);
            PyList_SetItem(row,j,value);
        }
        
        PyList_SetItem(teamPosPy,i,row);
    }
    
    return teamPosPy;
}


PyObject * sendUNum(PyObject * self,PyObject* args)
{
    int n;

    if(!PyArg_ParseTuple(args,"i",&n))
    {
        return NULL;
    }

    worldmodelWrap worldmodel = testWorldModel();
    int UNumC = worldmodel.getUNum();
    return Py_BuildValue("i",UNumC);
}

PyObject * sendNUMAGENTS(PyObject * self,PyObject* args)
{
    int n;

    if(!PyArg_ParseTuple(args,"i",&n))
    {
        return NULL;
    }

    worldmodelWrap worldmodel = testWorldModel();
    int NUMAGENTS = worldmodel.getNUMAGENTS();
    return Py_BuildValue("i",NUMAGENTS);
}

//Calls python function selectSkill() in strategy.py and prints the output
void selectSkill(){
    CPyInstance hInstance;

	CPyObject pName = PyUnicode_FromString("strategy"); //name of python file
	CPyObject pModule = PyImport_Import(pName);

	if(pModule)
	{
		CPyObject pFunc = PyObject_GetAttrString(pModule, "selectSkill"); //name of python function
		if(pFunc && PyCallable_Check(pFunc))
		{
			CPyObject pValue = PyObject_CallObject(pFunc, NULL); //output of python function as c++ object

			cout << "C: selectSkill() = " << PyLong_AsLong(pValue);
		}
		else
		{
			cout << "ERROR: function selectSkill()\n";
		}

	}
	else
	{
		cout << "ERROR: Module not imported\n";
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

int main(){
    selectSkill();
    
    return 0;
}