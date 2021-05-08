#include <vector>
#include <cmath>
#include <Python.h>
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

    
    vector<vector<int>> teammates;
    vector<int> myPosition;
    vector<int> ball;
    int UNum;
    int NUMAGENTS;
    
    public:
    worldmodelWrap(vector<vector<int>> teammatesIN,  vector<int> ballIN,  int UNumIN, int NUMAGENTSIN){
        teammates = teammatesIN;
        myPosition =teammatesIN[UNumIN];
        ball = ballIN;
        UNum = UNumIN;
        NUMAGENTS = NUMAGENTSIN;
        
    }


    float getDistanceTo(vector<int>pos1,vector<int>pos2){
        return sqrt( pow( pos1[0] - pos2[0],2) + pow(pos1[1] - pos2[1],2) );
    }

    int getUNum(){
        return UNum;
    }

    vector<vector<int>> getTeammates(){
        return teammates;
    }
    int getNUMAGENTS(){
        return NUMAGENTS;
    }

    vector<int> getMyPosition(){
        return myPosition;
    }

    vector<int> getBall(){
        return ball;
    }

};

worldmodelWrap testWorldModel(){
    vector<vector<int>> teammatesIN(11,vector<int>(2,1)); //coordinates of each player
    vector<int> ballIN(2,0); //ball coordinate
    int UNumIN = 0; //my player number
    int NUMAGENTSIN = 11; //number of players


    worldmodelWrap instance(teammatesIN, ballIN, UNumIN, NUMAGENTSIN);

    return instance;
}

//Strategy cc classes:
void DistanceToBallArrayTeammates(int mynum, double* _teamMateDistances, worldmodelWrap worldmodel){

    vector<vector<int>> worldModelTeammates = worldmodel.getTeammates();
    vector<int> ball = worldmodel.getBall();

    for(int i = 0; i<worldModelTeammates.size();i++){ //OUR PLAYERS

        vector<int>  temp;

        if(i == mynum){
            temp = worldmodel.getMyPosition();
        }
        else{
            temp = worldModelTeammates[i];
        }

        float distance = worldmodel.getDistanceTo(temp,ball);
        _teamMateDistances[i] = distance;

    }
}


//Wrapper methods:
PyObject * convertTeamDistanceToBall(double* teamDistance){

    
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

    PyObject* teamDistanceFromBall;
    worldmodelWrap worldmodel = testWorldModel();
    int NUM_AGENTS = worldmodel.getNUMAGENTS();

    double* _teamMateDistances = new double_t[NUM_AGENTS];
    int _playerNumber = worldmodel.getUNum();

    
    DistanceToBallArrayTeammates(_playerNumber,_teamMateDistances, worldmodel); 

    teamDistanceFromBall =  convertTeamDistanceToBall(_teamMateDistances);
    return teamDistanceFromBall;
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


    