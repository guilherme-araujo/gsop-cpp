#include <random>

class SimulationCycles{

	public:
	
	static void cycleV6(map<int,GsopNode> *nodes, SimulationData simulationData){
		//out.lock();
		//cout<<"no "<<(*nodes)[0].id<<" type "<<(*nodes)[0].type<<" coeff "<<(*nodes)[0].getCoeff()<<endl;
		//out.unlock();
		
		//Sortear mortes
		
		//Sortear nascimentos
		int dieCount = (int) ((double) nodes->size() * (simulationData.deathRate-1) );
		if(dieCount==0) dieCount++;
		vector<int> selectedKeys;
		vector<int> selectedKeysDeath;
		vector<int> keys;
		keys.resize(nodes->size());
		for(int i = 0; i < nodes->size(); i++){
			keys[i] = i;
		}
		random_shuffle(keys.begin(), keys.end());
		
		//deaths		
		for(int i = 0; i < dieCount; i++){
			selectedKeys.push_back(keys[i]);	
		}
		
		//deaths in case of neighborhood inheritance
		if (simulationData.neighborhoodInheritance) {
			for (int i = dieCount; i < dieCount*2; i++) {
				selectedKeysDeath.push_back(keys[i]);
			}
		}
		
		//births
		for(int keyi = 0; keyi < selectedKeys.size(); keyi++){
			int key = selectedKeys[keyi];
			GsopNode *n = &(*nodes)[key];
			
			vector<int> roleta;
			set<int> neighborsList = n->neighbors;
			
			neighborsList.insert(key);
			
			
			for(set<int>::iterator i = neighborsList.begin(); i != neighborsList.end(); ++i){	
				GsopNode neighbor = (*nodes)[*i];
				
				int qtd = (int) (neighbor.getCoeff()*100);
				for(int j = 0; j < qtd; j++){
					roleta.push_back(neighbor.id);
				}
			}
			
			/*out.lock();
			cout<<"no "<<n->id<<endl;
			for(set<int>::iterator i = neighborsList.begin(); i != neighborsList.end(); ++i){
				cout<<"no "<<(*nodes)[*i].id<<" type "<<(*nodes)[*i].type<<" coeff "<<(*nodes)[*i].getCoeff()<<endl;
			}
			cout<<"roleta has "<<roleta.size()<<endl;
			out.unlock();
			*/
			Eph *eph = NULL;//new Eph(simulationData.ephBonus);
			
			
			
			GsopNode *sorteado;
			if(roleta.size()==0){
				sorteado = &(*nodes)[key];
			}else{
				random_device rd; 
				mt19937 eng(rd());
				uniform_int_distribution<> distr(0, roleta.size()-1);
				int chosen = distr(eng);//rand()%roleta.size();
				//cout<<roleta[chosen]<<" chosen"<<endl;
				sorteado = &(*nodes)[roleta[chosen]];
			}
			
			sorteado->fitness++;
			
			if(!simulationData.neighborhoodInheritance){
				eph = (n->eph);
				n->eph = NULL;
				n->coeff = sorteado->coeff;
				n->type = sorteado->type;
				n->fitness = 0;
				if(n->type=='A'){
					random_device rd; 
					mt19937 eng(rd());
					uniform_int_distribution<> distr(0, 99);
					int sorteioGeracao = distr(eng);
					if (sorteioGeracao < (simulationData.ephBirthGenerationChance * 100)) {
						Eph *e = new Eph(simulationData.ephBonus);
						e->time = simulationData.ephTime;
						n->eph = e;
					}
				}
			}else{
								GsopNode *dyingNode = &(*nodes)[selectedKeysDeath[0]];
				//cout<<"dying "<<dyingNode->id<<endl;
				int selectedId = dyingNode->id;
				eph = dyingNode->eph;
				
				//remove dying node from neighbors' neighborhoods
				for(set<int>::iterator i = dyingNode->neighbors.begin(); i != dyingNode->neighbors.end(); ++i){
					GsopNode *neighbor = &(*nodes)[*i];
					if(!neighbor->id==dyingNode->id){
						neighbor->neighbors.erase(selectedId);
					}
				}
				
				nodes->erase(selectedId);
				selectedKeysDeath.erase(selectedKeysDeath.begin());
				//generating new node
				GsopNode newNode;
				newNode.id = selectedId;
				newNode.coeff = sorteado->coeff;
				newNode.type = sorteado->type;
				newNode.fitness = 0;
				//new node neighborhood list
				set<int> newNeighbors;
				for(set<int>::iterator i = sorteado->neighbors.begin(); i != sorteado->neighbors.end(); ++i){
					map<int,GsopNode>::iterator it = (*nodes).find(*i);
					if(it != (*nodes).end()){
						newNeighbors.insert(*i);
					}
				}
				map<int,GsopNode>::iterator it = (*nodes).find(sorteado->id);
				if(it != (*nodes).end()){
					newNeighbors.insert(sorteado->id);
				}
				newNode.neighbors = newNeighbors;
				
				if(newNode.type == 'A'){
					random_device rd; 
					mt19937 eng(rd());
					uniform_int_distribution<> distr(0, 99);
					int sorteioGeracao = distr(eng);
					if (sorteioGeracao < (simulationData.ephBirthGenerationChance * 100)) {
						Eph *e = new Eph(simulationData.ephBonus);
						e->time = simulationData.ephTime;
						newNode.eph = e;
					}
				}
				
				for(set<int>::iterator i = newNode.neighbors.begin(); i != newNode.neighbors.end(); ++i){
					it = (*nodes).find(*i);
					if(it != (*nodes).end()){
						//GsopNode *neighbor = ;
						it->second.neighbors.insert(selectedId);
					}
				}
				
				nodes->insert(pair<int,GsopNode>(selectedId,newNode));
				
			}
			
			vector<int> currentKeys;
			for(set<int>::iterator i = neighborsList.begin(); i != neighborsList.end(); ++i){
				currentKeys.push_back(*i);
			}
			
			random_shuffle(currentKeys.begin(), currentKeys.end());
			bool pegou = false;
			for(int i = 0; i < currentKeys.size(); i++){
				int ckey = currentKeys[i];
				if((*nodes)[ckey].eph ==NULL && (*nodes)[ckey].type =='A'){
					(*nodes)[ckey].eph = eph;
					pegou = true;
					break;
				}
			}
			
			if(!pegou){
				currentKeys.clear();
				//for(map <int, GsopNode> :: iterator it = nodes.begin(); it != nodes.end(); ++it){
				//	currentKeys.push_back(it->first);
				//}
				currentKeys = keys;
				random_shuffle(currentKeys.begin(), currentKeys.end());
				for(int i = 0; i < currentKeys.size(); i++){
					int ckey = currentKeys[i];
					if((*nodes)[ckey].eph ==NULL && (*nodes)[ckey].type =='A'){
						(*nodes)[ckey].eph = eph;
						pegou = true;
						break;
					}
				}
			}
			
			if(!pegou) delete eph;
			
		}
		
		
		for(int i = 0; i < keys.size(); i++){
			int keyi = keys[i];
			GsopNode *n = &(*nodes)[keyi];
			if(n->eph != NULL){
				if(n->eph->time == 1){
					delete n->eph;
					n->eph = NULL;
				}else{
					n->eph->time -= 1;
				}
			}
		}
		
		
	}
};