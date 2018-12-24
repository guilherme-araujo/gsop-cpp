#include <iostream>
#include <unistd.h>
#include <mutex>

mutex out;

class Simulation{
	
	public:
	
		static void simulationV6(int num){
			
			for(int i = 0; i < 100000000; i++) continue;
			out.lock();
			cout<<"thread "<<num<<endl;
			out.unlock();
		}
};