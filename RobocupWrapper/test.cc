//leave for now
#include "test.h"
#include "worldmodelWrap.h"
#include <vector>

using namespace std;

worldmodelWrap testWorldModel(){
    vector<vector<int>> teammatesIN;
    vector<int> myPositionIN;
    vector<int> ballIN;
    int UNumIN;
    int NUMAGENTSIN;

    //TODO populate above vectors

    worldmodelWrap instance(teammatesIN, myPositionIN, ballIN, UNumIN, NUMAGENTSIN);

    return instance;
}