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
			Eph *eph = new Eph(simulationData.ephBonus);
			
			
			
			GsopNode *sorteado;
			if(roleta.size()==0){
				sorteado = &(*nodes)[key];
			}else{
				random_device rd; 
				mt19937 eng(rd());
				uniform_int_distribution<> distr(0, roleta.size()-1);
				int chosen = distr(eng);//rand()%roleta.size();
				cout<<roleta[chosen]<<" chosen"<<endl;
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
				
			}
			
			
			
		}
		
		
	}
};