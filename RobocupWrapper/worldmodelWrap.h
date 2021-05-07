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


#endif

