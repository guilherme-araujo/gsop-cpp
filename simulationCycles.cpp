
class SimulationCycles{

	public:
	
	static void cycleV6(map<int,GsopNode> *nodes, double deathRate, bool neighborhoodInheritance){
		//out.lock();
		//cout<<"no "<<(*nodes)[0].id<<" type "<<(*nodes)[0].type<<" coeff "<<(*nodes)[0].getCoeff()<<endl;
		//out.unlock();
		
		//Sortear mortes
		
		//Sortear nascimentos
		int dieCount = (int) ((double) nodes->size() * (deathRate-1) );
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
		if (neighborhoodInheritance) {
			for (int i = dieCount; i < dieCount*2; i++) {
				selectedKeysDeath.push_back(keys[i]);
			}
		}
		
		//births
		for(int key = 0; key < selectedKeys.size(); key++){
			GsopNode n = nodes[key];
			
			
		}
		
		
	}
};