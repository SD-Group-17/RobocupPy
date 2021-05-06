#include <Python.h>
#include <worldModel.h>
#define PY_SSIZE_T_CLEAN


extern int agentBodyType;

/* Global Python Variables
 */
PyObject* world;
PyObject* teamDistanceFromBall;

//calling python code
//PyObject* myModuleString = PyString_FromString((char*)"robopy");
//PyObject* myModule = PyImport_Import(myModuleString);

//PyObject* myFunction = PyObject_GetAttrString(myModule,(char*)"hello");

worldmodelWrap worldmodel = new worldmodelWrap();

void DistanceToBallArrayTeammates(int mynum, double* _teamMateDistances){

    vector<vector<int>> worldModelTeammates = worldmodel->getTeammates();
    vector<int> ball = worldmodel.getBall();

    for(int i = 0; i<worldModelTeammates.size();i++){ //OUR PLAYERS

        vector<int>  temp;

        if(i == mynum){
            temp = worldModel->getMyPosition();
        }
        else{
            temp = worldModelTeammates[i];
        }

        float distance = worldmodel.getDistanceTo(temp,ball);
        _teamMateDistances[i] = distance;

    }
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

//TODO
//figure out how to make this function be called on
void Main() {

    worldModel->getRVSender()->clear();
    NUMAGENTS = worldModel->getNUMAGENTS();

    int _playerNumber = worldModel->getUNum();

    double* _teamMateDistances = NULL;
    double* _opponentDistances = NULL;

    _teamMateDistances = (double *) malloc(sizeof(double) * NUM_AGENTS);

    DistanceToBallArrayTeammates(_playerNumber,_teamMateDistances); 

    //Python Objects
    teamDistanceFromBall =  convertTeamDistanceToBall(_teamMateDistances);
    
    
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


    