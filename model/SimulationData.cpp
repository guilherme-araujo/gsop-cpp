#pragma once

#include <vector>
#include <string>
#include "../model/Graph.cpp"

class GsopGraph;

class SimulationData{

	public:

	int initialPop;
	double birthRate;
	double deathRate;
	char type;
	int cycles;
	int plotDensity;
	double ephBonus;
	double ephBonusB;
	double ephStartRatio;
	double ephBuildingRatio;
	double ephReusingRatio;
	double ephBirthGenerationChance;
	bool neighborhoodInheritance;
	bool aOnly;
	bool ephPopHistory;
	bool behaviorHistory;
	int ephTime;
	int behaviorTime;
	double reuseBonusMultiplierA;
	double reuseBonusMultiplierB;
	double buildingBonusA;
	double buildingBonusB;
	bool isAProducer;
	bool isBProducer;
	bool isAReuser;
	bool isBReuser;
	//'b' : barabasi-albert. 'e' : erdos-renyi. 'c' : complete. 'r' : regular;
	char graphType;
	bool bEph;
	bool printPartials;

	int sampleid;
	vector<string> nodeDetail;
	GsopGraph *g;

};
