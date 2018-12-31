#include <fstream>
#include <string>
#include <sstream>
#include "../model/Graph.cpp"

using namespace std;

class Parser{
	
	//Graph g;
	
	/*Parser(){
		g = new Graph();
	}*/
	
	public:
	
	GsopGraph * parse(string file){
		GsopGraph *g = new GsopGraph();
		
		ifstream in(file);
		ifstream in2("opts_"+file);
		
		string line;
		string line2;
		
		
		getline(in2,line2);
		int numNodes = stoi(line2);
		
		g->nodes.resize(numNodes);
		/*g->adjMatrix.resize(numNodes);
		for(int i = 0; i < numNodes; i++){
			g->adjMatrix[i].resize(numNodes);
			for(int j = 0; j < numNodes; j++){
				g->adjMatrix[i][j] = 0;	
			}
		}*/
		int nindex = 0;
		while(getline(in,line)){
			if(line[0] == '#'){
				continue;
			}else{
				//cout<<"linha: "+line+"\n";
				string nodenum;
				string neighbor;
				istringstream nodelist(line);
				getline(nodelist,nodenum,' ');
				//cout<<"node "+nodenum<<": ";
				GsopNode n;
				while(getline(nodelist,neighbor,' ')){
					//cout<<neighbor<<" ";
					n.neighbors.insert(stoi(neighbor));
				}
				n.id = stoi(nodenum);
				//cout<<endl;
				g->nodes[nindex] = n;
				nindex++;
				
			}
		}
		
		/*
		for(int i = 0; i < numNodes; i++){
			cout<<"node "<<i<<": ";
			for(int j = 0; j < g->nodes[i].neighbors.size(); j++){
				cout<<g->nodes[i].neighbors[j]<<" ";	
			}
			cout<<endl;
		}*/
			  
		return g;
	}
	
};