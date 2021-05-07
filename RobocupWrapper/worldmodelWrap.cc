#include "worldmodelWrap.h"


#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

worldmodelWrap::worldmodelWrap(vector<vector<int>> teammatesIN, vector<int> myPositionIN, vector<int> ballIN, int UNumIN, int NUMAGENTSIN){
    teammates = teammatesIN;
    myPosition =myPositionIN;
    ball = ballIN;
    UNum = UNumIN;
    NUMAGENTS = NUMAGENTSIN;
    
}

float worldmodelWrap::getDistanceTo(vector<int>pos1,vector<int>pos2){
    return sqrt( pow( pos1[0] - pos2[0],2) + pow(pos1[1] - pos2[1],2) );
}

int worldmodelWrap::getUNum(){
    return UNum;
}

vector<vector<int>> worldmodelWrap::getTeammates(){
    return teammates;
}

int worldmodelWrap::getNUMAGENTS(){
    return NUMAGENTS;
}

vector<int> worldmodelWrap::getMyPosition(){
    return myPosition;
}

vector<int> worldmodelWrap::getBall(){
    return ball;
}



//TODO
//initialise world model attributes


