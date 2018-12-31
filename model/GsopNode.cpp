#include <string>
#include <set>
#include "Eph.cpp"

using namespace std;

class GsopNode{
    public:

    string hash;
    char type;
    int id;
    int val;
    double coeff;
    int fitness;
    Eph *eph;

    set<int> neighbors;

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