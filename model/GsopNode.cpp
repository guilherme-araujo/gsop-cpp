#pragma once

#include <string>
#include <set>
#include "Eph.cpp"
#include "SimulationData.cpp"

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

  double getCoeffV8(SimulationData sd){
    double stateCoeff = this->coeff;
    double adjustedBonus = this->getBonus(&sd);

    if(this->behavior == PRODUCING){
      if(this->type == 'A'){
        stateCoeff = sd.buildingBonusA;
      } else{
        stateCoeff = sd.buildingBonusB;
      }
    }

    if(this->behavior == USING_SHARED){
      if(this->type == 'A'){
        adjustedBonus = adjustedBonus * sd.reuseBonusMultiplierA;
      } else{
        adjustedBonus = adjustedBonus * sd.reuseBonusMultiplierB;
      }
    }

    return stateCoeff + adjustedBonus;
  }

	double getBonus(SimulationData *sd = NULL){
		if(this->eph != NULL){   
      if(sd!=NULL && this->type == 'B'){
        return sd->ephBonusB;
      }	else return this->eph->bonus;
		} else return 0;
	}

};
