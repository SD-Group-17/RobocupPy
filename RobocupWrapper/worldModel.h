#include <vector>
#include <cmath>

using namespace std;

class worldmodelWrap()
{
    vector<vector<int>> teammates;
    vector<int> myPosition;
    vector<int> ball;
    int UNum;
    int NUMAGENTS;

    worldmodelWrap(vector<vector<int>> teammates,vector<int> myPosition,vector<int> ball,int UNum,int NUMAGENTS);

    ~worldmodelWrap();
    
    float getDistanceTo(vector<int>pos1,vector<int>pos2);

    void worldmodelWrap(vector<vector<int>> teammatesIN, vector<int> myPositionIN, vector<int> ballIN, int UNumIN, int NUMAGENTSIN);

    int getUNum();
    vector<vector<int>> getTeammates();
    vector<vector<int>> getNUMAGENTS();

    vector<int> getMyPosition();

    vector<int> getBall();

};