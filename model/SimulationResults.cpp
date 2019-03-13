#include <vector>
//#include "GsopNode.cpp"

class SimulationResults{
	
	public:
	
	vector<int> typeAPopHistory;
	vector<int> typeBPopHistory;
	vector<int> ephPopHistory;
	vector<int> avgDegree;
	int typeAWithEph;
	int typeBWithEph;
	vector<double> partialFitnessAvg;
	vector<GsopNode> finalNodes;
	double elapsedSeconds;
	double avgCoeff;
	double avgFitness;
	int fixationCycles;
	
	
};