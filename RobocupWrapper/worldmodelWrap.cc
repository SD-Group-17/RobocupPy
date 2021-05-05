#include <vector>
#include <Math>

using namespace std;

class worldmodelWrap(){
    vector<vector<int>> teammates;
    vector<int> myPosition;
    vector<int> ball;
    int UNum;
    int NUMAGENTS;

    float getDistanceTo(vector<int>pos1,vector<int>pos2){
        return Math.sqrt( (pos1[0] - pos2[0])**2 + (pos1[1] - pos2[1])**2)
    }

    void worldmodelWrap(vector<vector<int>> teammatesIN, vector<int> myPositionIN, vector<int> ballIN, int UNumIN, int NUMAGENTSIN){
        teammates = teammatesIN;
        myPosition =myPositionIN;
        ball = ballIN;
        UNum = UNumIN;
        NUMAGENTS = NUMAGENTSIN;
    }

    int getUNum(){
        return UNum;
    }

    vector<vector<int>> getTeammates(){
        return teammates;
    }
    vector<vector<int>> getNUMAGENTS(){
        return NUMAGENTS;
    }

    vector<int> getMyPosition(){
        return myPosition;
    }

    vector<int> getBall(){
        return ball;
    }

    //TODO
    //initialise world model attributes




}