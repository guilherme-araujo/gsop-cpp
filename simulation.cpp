#include <iostream>
#include <unistd.h>
#include <mutex>
#include <vector>
#include "model/SimulationData.cpp"
#include "model/SimulationResults.cpp"

mutex out;
#include "simulationRun.cpp"





class Simulation{
	
	public:
	
		static vector<SimulationResults> simResults;
	
		/*static void simulationV6(int num){
			
			for(int i = 0; i < 100000000; i++) continue;
			out.lock();
			cout<<"thread "<<num<<endl;
			out.unlock();
		}*/
	
		static void simulationV6(SimulationData simulationData, vector<bool> *tb, int ti){
			
			SimulationResults simulationResults = SimulationRun::runSimV6(simulationData);
			
			out.lock();
			//simResults.push_back(simulationResults);
			if(simulationData.ephPopHistory){
				for(int i = 0; i < simulationResults.typeAPopHistory.size(); i++){
					cout<<"cycle "<<i<<" A: "<<simulationResults.typeAPopHistory[i]<<" B: "<<simulationResults.typeBPopHistory[i]<<" Ephs: "<<simulationResults.ephPopHistory[i]<<endl;
				}
			}else{
				int fc = simulationResults.fixationCycles;
				//cout<<"fc "<<fc<<endl;
				if(fc==-1) fc = simulationResults.typeAPopHistory.size()-1;
				cout<<simulationResults.typeAPopHistory[fc]<<";"<<simulationResults.typeBPopHistory[fc]<<";"<<fc<<";"<<simulationResults.elapsedSeconds<<endl;
			}
			(*tb)[ti] = false;
			out.unlock();
		}
};

vector<SimulationResults> Simulation::simResults;