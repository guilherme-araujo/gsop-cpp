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
	double ephStartRatio;
	double ephBirthGenerationChance;
	bool neighborhoodInheritance;
	bool aOnly;
	bool ephPopHistory;
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

	int sampleid;
	vector<string> nodeDetail;
	GsopGraph *g;

};
