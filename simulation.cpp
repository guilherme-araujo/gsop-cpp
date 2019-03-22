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
	
        static bool simulationV7(SimulationData simulationData, int ti){
			
			SimulationResults simulationResults = SimulationRun::runSimV7(simulationData, ti);
			
			out.lock();
			//simResults.push_back(simulationResults);
			if(simulationData.ephPopHistory){
				for(int i = 0; i < simulationResults.typeAPopHistory.size(); i++){
					//cycle;A;B;ephs;avgDegree
					cout<<i<<";"<<simulationResults.typeAPopHistory[i]<<";"<<simulationResults.typeBPopHistory[i]<<";"<<simulationResults.ephPopHistory[i]<<";"<<simulationResults.avgDegree[i]<<endl;
				}
			}else{
				int fc = simulationResults.fixationCycles;
				//cout<<"fc "<<fc<<endl;
				int numCycles = simulationResults.typeAPopHistory.size()-1;
				//if(fc==-1) fc = simulationResults.typeAPopHistory.size()-1;
				cout<<simulationResults.typeAPopHistory[numCycles]<<";"<<simulationResults.typeBPopHistory[numCycles]<<";"<<fc<<";"<<simulationResults.elapsedSeconds<<endl;
			}
			
			out.unlock();
			
			return true;
		}

		static bool simulationV6(SimulationData simulationData, int ti){
			
			SimulationResults simulationResults = SimulationRun::runSimV6(simulationData, ti);
			
			out.lock();
			//simResults.push_back(simulationResults);
			if(simulationData.ephPopHistory){
				for(int i = 0; i < simulationResults.typeAPopHistory.size(); i++){
					//cycle;A;B;ephs;avgDegree
					cout<<i<<";"<<simulationResults.typeAPopHistory[i]<<";"<<simulationResults.typeBPopHistory[i]<<";"<<simulationResults.ephPopHistory[i]<<";"<<simulationResults.avgDegree[i]<<endl;
				}
			}else{
				int fc = simulationResults.fixationCycles;
				//cout<<"fc "<<fc<<endl;
				int numCycles = simulationResults.typeAPopHistory.size()-1;
				//if(fc==-1) fc = simulationResults.typeAPopHistory.size()-1;
				cout<<simulationResults.typeAPopHistory[numCycles]<<";"<<simulationResults.typeBPopHistory[numCycles]<<";"<<fc<<";"<<simulationResults.elapsedSeconds<<endl;
			}
			
			out.unlock();
			
			return true;
		}
};

vector<SimulationResults> Simulation::simResults;
