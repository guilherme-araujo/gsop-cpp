#include <string>
#include <set>
#include "Eph.cpp"

using namespace std;

enum NodeState{
  SEARCHING,    //behaviorTimer begins at ephTime
  PRODUCING,    //behaviorTimer begins at ephTime
  USING,        //behavior lasts remaining ephTime (behaviorTimer == 0)
  USING_SHARED  //behavior lasts remaining ephTime (behaviorTimer == 0)

};

class GsopNode{
    public:

    string hash;
    char type;
    int id;
    int val;
    double coeff;
    int fitness;
    Eph *eph;
    int behaviorTimer;
    NodeState behavior;

    vector<int> neighbors;

	GsopNode(){
		this->eph = NULL;
		this->fitness = 0;
	}

  double getCoeff(){
    return this->coeff+this->getBonus();
  }

	double getBonus(){
		if(this->eph != NULL){
			return this->eph->bonus;
		} else return 0;
	}

};
