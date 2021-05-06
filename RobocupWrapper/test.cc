//leave for now

#include "worldmodelWrap.h"
#include "strategy.cc"
#include <vector>

using namespace std;

int main(){
    vector<vector<int>> teammatesIN;
    vector<int> myPositionIN;
    vector<int> ballIN;
    int UNumIN;
    int NUMAGENTSIN;

    //TODO populate above vectors

    WorldModel instance = new WorldModel(teammatesIN, myPositionIN, ballIN, UNumIN, NUMAGENTSIN);

    return 0;
}