#include <iostream>
#include <vector>
#include <cmath>


using namespace std;


 class worldmodelWrap{
     int NUM_AGENTS;
     vector<vector<int>> teammates;
     vector<int> myPosition;
     vector<int> ball;
     int UNum;

     public:
     worldmodelWrap(vector<vector<int>> teammatesIN, vector<int> ballIN,  int UNumIN, int NUMAGENTSIN){
         teammates = teammatesIN;
         myPosition =teammatesIN[UNumIN];
         ball = ballIN;
         UNum = UNumIN;
         NUM_AGENTS = NUMAGENTSIN;
     }

     float getDistance(vector<int>pos1,vector<int>pos2){
         return sqrt( pow( pos1[0] - pos2[0],2) + pow(pos1[1] - pos2[1],2) );
     }

     int getUNum()const{
         return UNum;
     }

     vector<vector<int>> getTeammates()const{
         return teammates;
     }
     int getNUM_AGENTS()const{
         return NUM_AGENTS;
     }

     vector<int> getMyPosition()const{
         return myPosition;
     }

     vector<int> getBall()const{
         return ball;
     }

 };

 worldmodelWrap testWorldModel(){
    
      vector<int> ballIN(2,1); //ball coordinate
      int UNumIN; //my player number
      int NUMAGENTSIN; //number of players

      NUMAGENTSIN = 11;
      UNumIN = 0;
      vector<vector<int>> teammatesIN(NUMAGENTSIN, vector<int>(2, 0)); //coordinates of each player

      worldmodelWrap instance(teammatesIN, ballIN,   UNumIN,  NUMAGENTSIN);
     return instance;
 }

int main(int argc, char **argv){
    worldmodelWrap worldmodel = testWorldModel();

    cout<<"("<<worldmodel.getBall()[0]<<","<<worldmodel.getBall()[1]<<")"<<endl;
    cout<<"("<<worldmodel.getMyPosition()[0]<<","<<worldmodel.getMyPosition()[1]<<")"<<endl;
    cout<<worldmodel.getDistance(worldmodel.getMyPosition(),worldmodel.getBall())<<endl;
    return 0;
}