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
    Eph eph;

    vector<int> neighbors;

    double getCoeff(){
        return this->coeff+this->eph.bonus;
    }
};