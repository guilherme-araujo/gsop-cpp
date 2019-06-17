#include <vector>
#include <string>

class SimulationData{
	
	public:
	
	int initialPop;
	double birthRate;
	double deathRate;
	char type;
	int cycles;
	int plotDensity;
	double ephBonus;
	double ephStartRatio;
	double ephBirthGenerationChance;
	bool neighborhoodInheritance;
	bool aOnly;
	bool ephPopHistory;
	int ephTime;
	//'b' : barabasi-albert. 'e' : erdos-renyi. 'c' : complete. 'r' : regular; 
	char graphType;
	
	int sampleid;
	vector<string> nodeDetail;
	GsopGraph *g;
	
};