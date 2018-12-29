#include <iostream>
#include <unistd.h>
#include <mutex>
#include <vector>
#include "model/SimulationData.cpp"
#include "model/SimulationResults.cpp"
#include "simulationRun.cpp"

mutex out;



class Simulation{
	
	public:
	
		static vector<SimulationResults> simResults;
	
		/*static void simulationV6(int num){
			
			for(int i = 0; i < 100000000; i++) continue;
			out.lock();
			cout<<"thread "<<num<<endl;
			out.unlock();
		}*/
	
		static void simulationV6(SimulationData simulationData){
			SimulationResults simulationResults;
			
			simulationResults = SimulationRun::runSimV6(simulationData);
			
			
			out.lock();
			simResults.push_back(simulationResults);
			out.unlock();
		}
};

vector<SimulationResults> Simulation::simResults;