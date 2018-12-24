#include <iostream>
#include <unistd.h>
#include <thread>
#include "utils/graphParser.cpp"
#include "simulation.cpp"


using namespace std;

int main(int argc, char* argv[]){

	//Default simulation values
	int samples = 1;
	int cycles = 1000;
	int numNodes = 100;
	double ephBonus = 0.04;
	int threads = 1;
	double ephStartRatio = 0.5;
	bool ephPopHistory = false;
	int ephTime = 30;
	
	//Simulation values parsing from argv
	string arg_samples = "samples";
	string arg_cycles = "cycles";
	string arg_numNodes = "numNodes";
	string arg_ephBonus = "ephBonus";
	string arg_threads = "threads";
	string arg_ephStartRatio = "ephStartRatio";
	string arg_ephPopHistory = "ephPopHistory";
	string arg_ephTime = "ephTime";
	
	for(int i = 1; i < argc; i+=2){
		if(arg_samples.compare(argv[i])==0){
			samples = stoi(argv[i+1]);	
		}else if(arg_cycles.compare(argv[i])==0){
			cycles = stoi(argv[i+1]);	
		}else if(arg_numNodes.compare(argv[i])==0){
			numNodes = stoi(argv[i+1]);	
		}else if(arg_ephBonus.compare(argv[i])==0){
			ephBonus = stod(argv[i+1]);	
		}else if(arg_threads.compare(argv[i])==0){
			threads = stoi(argv[i+1]);	
		}else if(arg_ephStartRatio.compare(argv[i])==0){
			ephStartRatio = stod(argv[i+1]);	
		}else if(arg_ephPopHistory.compare(argv[i])==0){
			ephPopHistory = stoi(argv[i+1]);	
		}else if(arg_ephTime.compare(argv[i])==0){
			ephTime = stoi(argv[i+1]);	
		}else {
			cout<<"Wrong option "<<argv[i]<<endl;	
		}
		
	}
	
	cout<<"samples "<<samples<<endl;
	cout<<"cycles "<<cycles<<endl;
	cout<<"numNodes "<<numNodes<<endl;
	cout<<"ephBonus "<<ephBonus<<endl;
	cout<<"threads "<<threads<<endl;
	cout<<"ephStartRatio "<<ephStartRatio<<endl;
	cout<<"ephPopHistory "<<ephPopHistory<<endl;
	cout<<"ephTime "<<ephTime<<endl;
	
	//Parse graph generated by python script or another source
	Parser p;
	GsopGraph *g = p.parse("graph.txt");
	cout<<g->size()<<endl;
	
	//Launch simulation threads according to number of samples
	vector<thread> tl;
	tl.resize(threads);
	vector<bool> tb;
	tb.resize(threads);
	
	int scount = 0;
	
	while(true){
		int ti = 0;
		for(ti = 0; ti < threads; ti++){
			if(tl[ti].joinable()){
				tl[ti].join();
				tb[ti] = false;
			}
		}
		for(ti = 0; ti < threads; ti++){
			if(!tb[ti] && scount!=samples){
				tl[ti] = thread(Simulation::simulationV6,scount);
				tb[ti] = true;
				scount++;
			}
		}
		if(scount==samples){
			bool allover = true;
			for(ti = 0; ti < threads; ti++){
				if(tb[ti]){
					allover = false;
					break;
				}
			}
			if(allover) break;
		}
		usleep(100000);
	}
	
	

    return 0;
}
