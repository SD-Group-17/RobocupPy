//leave for now

#include "worldmodelWrap.cc"
#include <vector>

using namespace std;

int main(){
    vector<vector<int>> teammatesIN;
    vector<int> myPositionIN;
    vector<int> ballIN;

    //TODO populate above vectors

    WorldModel instance = new WorldModel(teammatesIN,myPositionIN,ballIN);

    return 0;
}