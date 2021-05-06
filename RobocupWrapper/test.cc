//leave for now
#include "test.h"
#include "worldmodelWrap.h"
#include <vector>

using namespace std;

worldmodelWrap testWorldModel(){
    vector<vector<int>> teammatesIN; //coordinates of each player
    vector<int> myPositionIN; //my coordinate
    vector<int> ballIN; //ball coordinate
    int UNumIN; //my player number
    int NUMAGENTSIN; //number of players

    //TODO populate above values with test data

    worldmodelWrap instance(teammatesIN, myPositionIN, ballIN, UNumIN, NUMAGENTSIN);

    return instance;
}