#include <string>
#include <vector>
#include "Eph.cpp"

using namespace std;

class GsopNode{
    public:

    string hash;
    string type;
    int id;
    int val;
    double coeff;
    int fitness;
    Eph *eph;

    vector<int> neighbors;

	GsopNode(){
		this->eph = NULL;
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