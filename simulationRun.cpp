//#include "model/SimulationData.cpp"
//#include "model/SimulationResults.cpp"
#include <algorithm>
#include <map>
#include <unordered_map>
#include <random>
#include <chrono>
#include "simulationCycles.cpp"

class SimulationRun{

public:

	static SimulationResults runSimV8(SimulationData simulationData, int ti){
		SimulationResults simulationResults;

		simulationResults.fixationCycles = -1;

		vector<GsopNode> nodes = simulationData.g->nodes;

		srand(time(NULL));
		random_device rd;
		array<int, std::mt19937::state_size> seed_data;
		generate_n(seed_data.data(), seed_data.size(), std::ref(rd));
		seed_seq seq(std::begin(seed_data), std::end(seed_data));
		mt19937 eng(seq);
		shuffle(nodes.begin(), nodes.end(), eng);

		unordered_map<int, GsopNode> nodesmap;
		simulationData.aOnly = true;

		for(int i = 0; i < nodes.size(); i++){
			double abrate = 0.5;
			if(simulationData.aOnly){
				abrate = 1;
			}
			if(i < simulationData.initialPop*abrate){
				nodes[i].type = 'A';
				nodes[i].coeff = 1.0;
				if (i < simulationData.initialPop * abrate * simulationData.ephStartRatio) {
					Eph *e = new Eph(simulationData.ephBonus);
					e->time = simulationData.ephTime;
					nodes[i].eph = e;
				}else{
					nodes[i].eph = NULL;
				}
			} else{
				nodes[i].type = 'B';
				nodes[i].coeff = 1.0;
				if(simulationData.bEph){
					if (i < (simulationData.initialPop * abrate * simulationData.ephStartRatio)+(simulationData.initialPop * abrate) ) {
						Eph *e = new Eph(simulationData.ephBonus);
						e->time = simulationData.ephTime;
						nodes[i].eph = e;
					}else{
						nodes[i].eph = NULL;
					}
				}else{
					nodes[i].eph = NULL;
				}
			}
			nodesmap.insert(pair<int,GsopNode>(nodes[i].id,nodes[i]));
		}


		for(int i = 0; i < nodes.size(); i++){
			for(int j = 0; j < nodes[i].neighbors.size(); j++){
				nodesmap[nodes[i].neighbors[j]].neighbors.push_back(nodes[i].id);
			}
		}

		clock_t begin = clock();



		for(int i = 0; i < simulationData.cycles; i++){
			SimulationCycles::cycleV8(&nodesmap, simulationData, &eng);

			int ephCount = 0;
			int typeACount = 0;
			int typeBCount = 0;

			vector<GsopNode> nodeslist;

			int degreeCount = 0;
			for(unordered_map<int, GsopNode>::iterator j = nodesmap.begin(); j != nodesmap.end(); ++j){
				if(j->second.eph != NULL){
					ephCount++;
				}
				if(j->second.type == 'A'){
					typeACount++;
				}else{
					typeBCount++;
				}
				degreeCount += j->second.neighbors.size();

			}

			simulationResults.avgDegree.push_back(degreeCount/nodes.size());
			simulationResults.ephPopHistory.push_back(ephCount);
			simulationResults.typeAPopHistory.push_back(typeACount);
			simulationResults.typeBPopHistory.push_back(typeBCount);

/*
			if(typeACount == 0 || typeBCount == 0){
				simulationResults.fixationCycles = i;
				break;
			}
*/


		}

		clock_t end = clock();

		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

		simulationResults.elapsedSeconds = elapsed_secs;

		return simulationResults;
	}

	static SimulationResults runSimV7(SimulationData simulationData, int ti){
		SimulationResults simulationResults;

		simulationResults.fixationCycles = -1;

		vector<GsopNode> nodes = simulationData.g->nodes;

		srand(time(NULL));
		random_device rd;
		array<int, std::mt19937::state_size> seed_data;
		generate_n(seed_data.data(), seed_data.size(), std::ref(rd));
		seed_seq seq(std::begin(seed_data), std::end(seed_data));
		mt19937 eng(seq);
		shuffle(nodes.begin(), nodes.end(), eng);

		unordered_map<int, GsopNode> nodesmap;

		for(int i = 0; i < nodes.size(); i++){
			double abrate = 0.5;
			if(simulationData.aOnly){
				abrate = 1;
			}
			if(i < simulationData.initialPop*abrate){
				nodes[i].type = 'A';
				nodes[i].coeff = 1.0;
				if (i < simulationData.initialPop * abrate * simulationData.ephStartRatio) {
					Eph *e = new Eph(simulationData.ephBonus);
					e->time = simulationData.ephTime;
					nodes[i].eph = e;
				}else{
					nodes[i].eph = NULL;
				}
			} else{
				nodes[i].type = 'B';
				nodes[i].coeff = 1.0;
				if(simulationData.bEph){
					if (i < (simulationData.initialPop * abrate * simulationData.ephStartRatio)+(simulationData.initialPop * abrate) ) {
						Eph *e = new Eph(simulationData.ephBonus);
						e->time = simulationData.ephTime;
						nodes[i].eph = e;
					}else{
						nodes[i].eph = NULL;
					}
				}else{
					nodes[i].eph = NULL;
				}
			}
			nodesmap.insert(pair<int,GsopNode>(nodes[i].id,nodes[i]));
		}


		for(int i = 0; i < nodes.size(); i++){
			for(int j = 0; j < nodes[i].neighbors.size(); j++){
				nodesmap[nodes[i].neighbors[j]].neighbors.push_back(nodes[i].id);
			}
		}

		clock_t begin = clock();



		for(int i = 0; i < simulationData.cycles; i++){
			SimulationCycles::cycleV7(&nodesmap, simulationData, &eng);

			int ephCount = 0;
			int typeACount = 0;
			int typeBCount = 0;

			vector<GsopNode> nodeslist;

			int degreeCount = 0;
			for(unordered_map<int, GsopNode>::iterator j = nodesmap.begin(); j != nodesmap.end(); ++j){
				if(j->second.eph != NULL){
					ephCount++;
				}
				if(j->second.type == 'A'){
					typeACount++;
				}else{
					typeBCount++;
				}
				degreeCount += j->second.neighbors.size();

			}

			simulationResults.avgDegree.push_back(degreeCount/nodes.size());
			simulationResults.ephPopHistory.push_back(ephCount);
			simulationResults.typeAPopHistory.push_back(typeACount);
			simulationResults.typeBPopHistory.push_back(typeBCount);


			if(typeACount == 0 || typeBCount == 0){
				simulationResults.fixationCycles = i;
				break;
			}



		}


		int typeACount = 0;
		int typeBCount = 0;

		for(unordered_map<int, GsopNode>::iterator j = nodesmap.begin(); j != nodesmap.end(); ++j){
			if(j->second.eph != NULL){
				if(j->second.type == 'A'){
					typeACount++;
				}else{
					typeBCount++;
				}
			}
		}

		simulationResults.typeAWithEph = typeACount;
		simulationResults.typeBWithEph = typeBCount;

		clock_t end = clock();

		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;


		simulationResults.elapsedSeconds = elapsed_secs;

		return simulationResults;
	}

	static SimulationResults runSimV6(SimulationData simulationData, int ti){
		SimulationResults simulationResults;

		simulationResults.fixationCycles = -1;
		//simulationResults.ephPopHistory.resize(simulationData.cycles);
		//simulationResults.typeAPopHistory.resize(simulationData.cycles);
		//simulationResults.typeBPopHistory.resize(simulationData.cycles);

		vector<GsopNode> nodes = simulationData.g->nodes;
		//vector< vector<int> > adjMatrix = simulationData.g->adjMatrix;

		srand(time(NULL));
		random_shuffle(nodes.begin(), nodes.end());

		//Tornar bidirecional a lista de vizinhança de nós

		map<int, GsopNode> nodesmap;
		//random_shuffle
		//Inicializar nós
		for(int i = 0; i < nodes.size(); i++){
			double abrate = 0.5;
			if(simulationData.aOnly){
				abrate = 1;
			}
			if(i < simulationData.initialPop*abrate){
				nodes[i].type = 'A';
				nodes[i].coeff = 1.0;
				if (i < simulationData.initialPop * abrate * simulationData.ephStartRatio) {
					Eph *e = new Eph(simulationData.ephBonus);
					e->time = simulationData.ephTime;
					nodes[i].eph = e;
				}else{
					nodes[i].eph = NULL;
				}
			} else{
				nodes[i].type = 'B';
				nodes[i].coeff = 1.0;
				nodes[i].eph = NULL;
			}
			nodesmap.insert(pair<int,GsopNode>(nodes[i].id,nodes[i]));
		}


		for(int i = 0; i < nodes.size(); i++){
			for(int j = 0; j < nodes[i].neighbors.size(); j++){
				nodesmap[nodes[i].neighbors[j]].neighbors.push_back(nodes[i].id);
			}
		}

		//Início dos ciclos e contagem do tempo
		clock_t begin = clock();

		//random_device rd;
		mt19937 eng(ti*clock());
		//uint32_t state = time(NULL);


		for(int i = 0; i < simulationData.cycles; i++){
			SimulationCycles::cycleV6(&nodesmap, simulationData, &eng);
			//cout<<nodesmap.size()<<" graph size"<<endl;
			int ephCount = 0;
			int typeACount = 0;
			int typeBCount = 0;

			vector<GsopNode> nodeslist;

			int degreeCount = 0;
			for(map<int, GsopNode>::iterator j = nodesmap.begin(); j != nodesmap.end(); ++j){
				if(j->second.eph != NULL){
					ephCount++;
				}
				if(j->second.type == 'A'){
					typeACount++;
				}else{
					typeBCount++;
				}
				degreeCount += j->second.neighbors.size();

			}

			simulationResults.avgDegree.push_back(degreeCount/nodes.size());
			simulationResults.ephPopHistory.push_back(ephCount);
			simulationResults.typeAPopHistory.push_back(typeACount);
			simulationResults.typeBPopHistory.push_back(typeBCount);


			if(typeACount == 0 || typeBCount == 0){
				simulationResults.fixationCycles = i;
				break;
			}



		}

		clock_t end = clock();

		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

		simulationResults.elapsedSeconds = elapsed_secs;

		//out.lock();
		//cout<<"no "<<nodesmap[0].id<<" type "<<nodesmap[0].type<<" coeff "<<nodesmap[0].getCoeff()<<endl;
		//for(vector <GsopNode> :: iterator it = nodes.begin(); it != nodes.end(); ++it){
		//	cout<<"no "<<it->id<<"type "<<it->type<<" coeff "<<it->getCoeff()<<endl;;
		//}
		//cout<<endl<<elapsed_secs<<" elapsed"<<endl;
		//out.unlock();


		return simulationResults;
	}
};
