#ifndef __WORLDMODELWRAP_H
#define __WORLDMODELWRAP_H

#include <iostream>
#include <vector>
#include <cmath>


using namespace std;

class worldmodelWrap{

    private:
    vector<vector<int>> teammates;
    vector<int> myPosition;
    vector<int> ball;
    int UNum;
    int NUMAGENTS;
    
    public:

    worldmodelWrap(vector<vector<int>> teammatesIN, vector<int> myPositionIN, vector<int> ballIN, int UNumIN, int NUMAGENTSIN);

    float getDistanceTo(vector<int>pos1,vector<int>pos2);
    int getUNum();
    vector<vector<int>> getTeammates();
    int getNUMAGENTS();
    vector<int> getMyPosition();
    vector<int> getBall();

};


#endif

