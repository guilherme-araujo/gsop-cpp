

int xorshift32(uint32_t *state)
{
	/* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
	uint32_t x = *state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	*state = x;
	return (int)x;
}

class SimulationCycles{

	public:


    static void cycleV7(unordered_map<int,GsopNode> *nodes, SimulationData simulationData, mt19937 *eng){

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
		shuffle(keys.begin(), keys.end(), *eng);

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
			vector<int> neighborsList = n->neighbors;

			//neighborsList.insert(key);


			for(int i = 0; i < neighborsList.size(); i++){
				GsopNode neighbor = (*nodes)[neighborsList[i]];

				int qtd = (int) (neighbor.getCoeff()*100);
				for(int j = 0; j < qtd; j++){
					roleta.push_back(neighbor.id);
				}
			}


			Eph *eph = NULL;


			GsopNode *sorteado;
			if(roleta.size()==0){
				sorteado = &(*nodes)[key];
			}else{
				uniform_int_distribution<> distr(0, roleta.size()-1);
				int chosen = distr(*eng);//rand()%roleta.size();
				sorteado = &(*nodes)[roleta[chosen]];
			}

			sorteado->fitness++;

			if(!simulationData.neighborhoodInheritance){
				eph = (n->eph);
				n->eph = NULL;
				n->coeff = sorteado->coeff;
				n->type = sorteado->type;
				n->fitness = 0;
				if(simulationData.bEph ||  n->type=='A'){

					uniform_int_distribution<> distr(0, 99);
					int sorteioGeracao = distr(*eng);

					if (sorteioGeracao < (simulationData.ephBirthGenerationChance * 100)) {
						Eph *e = new Eph(simulationData.ephBonus);
						e->time = simulationData.ephTime;
						n->eph = e;
					}
				}
			}else{

				GsopNode *dyingNode = &(*nodes)[selectedKeysDeath[0]];

				int selectedId = dyingNode->id;
				eph = dyingNode->eph;

				//remove dying node from neighbors' neighborhoods
				for(int i = 0; i < dyingNode->neighbors.size(); i++){
					GsopNode *neighbor = &(*nodes)[dyingNode->neighbors[i]];

					vector<int> updatedNList;

					if(neighbor->id!=dyingNode->id){

						vector<int>::iterator it = find(neighbor->neighbors.begin(), neighbor->neighbors.end(), selectedId);
						neighbor->neighbors.erase(it);
					}
				}

				selectedKeysDeath.erase(selectedKeysDeath.begin());
				//generating new node
				GsopNode newNode;
				newNode.id = selectedId;
				newNode.coeff = sorteado->coeff;
				newNode.type = sorteado->type;
				newNode.fitness = 0;
				//new node neighborhood list
				vector<int> newNeighbors = sorteado->neighbors;

				nodes->erase(selectedId);


				newNode.neighbors = newNeighbors;

				if(simulationData.bEph || newNode.type == 'A'){

					uniform_int_distribution<> distr(0, 99);
					int sorteioGeracao = distr(*eng);

					if (sorteioGeracao < (simulationData.ephBirthGenerationChance * 100)) {
						Eph *e = new Eph(simulationData.ephBonus);
						e->time = simulationData.ephTime;
						newNode.eph = e;
					}
				}

				for(int i = 0 ;i < newNode.neighbors.size(); i++){
					unordered_map<int,GsopNode>::iterator it = (*nodes).find(newNode.neighbors[i]);
					if(it != (*nodes).end()){

						it->second.neighbors.push_back(selectedId);
					}
				}

				nodes->insert(pair<int,GsopNode>(selectedId,newNode));

			}

			vector<int> currentKeys;
			for(int i = 0; i < neighborsList.size(); i++){
				currentKeys.push_back(neighborsList[i]);
			}


			shuffle(currentKeys.begin(), currentKeys.end(), *eng);
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

				currentKeys = keys;
				shuffle(currentKeys.begin(), currentKeys.end(), *eng);
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

	static void cycleV6(map<int,GsopNode> *nodes, SimulationData simulationData, mt19937 *eng){
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
		shuffle(keys.begin(), keys.end(), *eng);

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
			vector<int> neighborsList = n->neighbors;

			//neighborsList.insert(key);


			for(int i = 0; i < neighborsList.size(); i++){
				GsopNode neighbor = (*nodes)[neighborsList[i]];

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

			//clock_t begin = clock();

			GsopNode *sorteado;
			if(roleta.size()==0){
				sorteado = &(*nodes)[key];
			}else{
				//int chosen = xorshift32(state)%roleta.size();
				uniform_int_distribution<> distr(0, roleta.size()-1);
				int chosen = distr(*eng);//rand()%roleta.size();
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

					uniform_int_distribution<> distr(0, 99);
					int sorteioGeracao = distr(*eng);
					//int sorteioGeracao = xorshift32(state)%100;
					if (sorteioGeracao < (simulationData.ephBirthGenerationChance * 100)) {
						Eph *e = new Eph(simulationData.ephBonus);
						e->time = simulationData.ephTime;
						n->eph = e;
					}
				}
			}else{

			//clock_t end = clock();

			//double elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC/1000000);
			//cout<<"t0 "<<elapsed_secs;

			//begin = clock();


				GsopNode *dyingNode = &(*nodes)[selectedKeysDeath[0]];
				//cout<<"dying "<<dyingNode->id<<" sorteado "<<sorteado->id<<endl;

				int selectedId = dyingNode->id;
				eph = dyingNode->eph;

				//remove dying node from neighbors' neighborhoods
				for(int i = 0; i < dyingNode->neighbors.size(); i++){
					GsopNode *neighbor = &(*nodes)[dyingNode->neighbors[i]];
					//cout<<"teste dying "<<selectedId<<" de "<<neighbor->id<<endl;
					vector<int> updatedNList;



					if(neighbor->id!=dyingNode->id){
						/*for(int j = 0; j < neighbor->neighbors.size(); j++){
							if(neighbor->neighbors[j]!=selectedId){
								updatedNList.push_back(neighbor->neighbors[j]);
							}
						}
						neighbor->neighbors = updatedNList;*/
					//	cout<<"apagando "<<selectedId<<" de "<<neighbor->id<<endl;
						//neighbor->neighbors.erase(selectedId);
						vector<int>::iterator it = find(neighbor->neighbors.begin(), neighbor->neighbors.end(), selectedId);
						neighbor->neighbors.erase(it);
					}
				}

			//end = clock();

			//elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC/1000000);
			//cout<<"t1 "<<elapsed_secs;

			//begin = clock();
				selectedKeysDeath.erase(selectedKeysDeath.begin());
				//generating new node
				GsopNode newNode;
				newNode.id = selectedId;
				newNode.coeff = sorteado->coeff;
				newNode.type = sorteado->type;
				newNode.fitness = 0;
				//new node neighborhood list
				vector<int> newNeighbors = sorteado->neighbors;
			//end = clock();

			//elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC/1000000);
			//cout<<" t2 "<<elapsed_secs;

			//begin = clock();

				//newNeighbors.push_back(sorteado->id);

				/*for(set<int>::iterator i = sorteado->neighbors.begin(); i != sorteado->neighbors.end(); ++i){
					map<int,GsopNode>::iterator it = (*nodes).find(*i);
					if(it != (*nodes).end()){
						newNeighbors.push_back(*i);
					}
				}*/

				nodes->erase(selectedId);

			//end = clock();
			//elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC/1000000);
			//cout<<" t3 "<<elapsed_secs;
				//map<int,GsopNode>::iterator it = (*nodes).find(sorteado->id);
				//if(it != (*nodes).end()){

				//}
				//set<int> newNeighborsSet(newNeighbors.begin(), newNeighbors.end());

			//begin = clock();

				newNode.neighbors = newNeighbors;
			//cout<<" "<<newNeighbors.size();

				if(newNode.type == 'A'){

					uniform_int_distribution<> distr(0, 99);
					int sorteioGeracao = distr(*eng);
					//int sorteioGeracao = xorshift32(state)%100;
					if (sorteioGeracao < (simulationData.ephBirthGenerationChance * 100)) {
						Eph *e = new Eph(simulationData.ephBonus);
						e->time = simulationData.ephTime;
						newNode.eph = e;
					}
				}

			//end = clock();
			//elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC/1000000);
			//cout<<" t4 "<<elapsed_secs;
			//begin = clock();

				for(int i = 0 ;i < newNode.neighbors.size(); i++){
					map<int,GsopNode>::iterator it = (*nodes).find(newNode.neighbors[i]);
					if(it != (*nodes).end()){
						//GsopNode *neighbor = ;
						it->second.neighbors.push_back(selectedId);
					}
				}

			//end = clock();
			//elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC/1000000);
			//cout<<" t5 "<<elapsed_secs;
			//begin = clock();

				nodes->insert(pair<int,GsopNode>(selectedId,newNode));

			//end = clock();
			//elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC/1000000);
			//cout<<" t6 "<<elapsed_secs<<endl;
			}

			vector<int> currentKeys;
			for(int i = 0; i < neighborsList.size(); i++){
				currentKeys.push_back(neighborsList[i]);
			}

			//begin = clock();

			shuffle(currentKeys.begin(), currentKeys.end(), *eng);
			bool pegou = false;
			for(int i = 0; i < currentKeys.size(); i++){
				int ckey = currentKeys[i];
				if((*nodes)[ckey].eph ==NULL && (*nodes)[ckey].type =='A'){
					(*nodes)[ckey].eph = eph;
					pegou = true;
					break;
				}
			}

			//end = clock();
			//elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC/1000000);
			//cout<<" t7 "<<elapsed_secs<<endl;

			if(!pegou){
				currentKeys.clear();
				//for(map <int, GsopNode> :: iterator it = nodes.begin(); it != nodes.end(); ++it){
				//	currentKeys.push_back(it->first);
				//}
				currentKeys = keys;
				shuffle(currentKeys.begin(), currentKeys.end(), *eng);
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
