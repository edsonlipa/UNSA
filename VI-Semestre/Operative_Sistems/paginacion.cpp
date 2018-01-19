#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <unistd.h>
#include <utility>
#include <queue>
#include <vector>


#define Marco_size 20 //kb 
#define Memory 200 //kb
int  N_partitions = Memory/Marco_size;


using namespace std;
class process
 {
 public:
	string name;
	int t_service;
	int size_p;
	int n_marcos;

 	process(){};
 	~process();

};

class marco
 {
 public:
    process * pro;
	bool empty;
 	marco(){this->empty=true;};
 	~marco();

};

 class Memoria{
	private:
	public:
        vector<marco *> marcos;

    void print_marcos(){
		for(int i=0;i<this->marcos.size();i++)
			cout<<"["<<i<<"] "<<this->marcos[i]->empty?this->marcos[i]->pro->name:"vacios(sin uso)";
		}
	}     
	Memoria(int n_marcos){
		
		this->marcos.resize(n_marcos);
	};
	
	~Memoria(){};
};
Memoria::
Memoria RAM(N_partitions);


void planner()
{	int timer=0;
    while(1){

    
        

    for (size_t i = 0 ;i<N_partitions;i++){
        RAM.marcos[i].pro->name;
    }
    
      std::cout  << '\n';
	    
        timer++;
		sleep(1);
	}
}
void wait_to_add()
{
}

void add(vector<process *> &processes,string name,int s_t,int si_p)
{
	//nuevo listo ejecutando terminado
	process * nuevo = new process();
	nuevo->name=name;
    nuevo->t_service=s_t;
	nuevo->size_p=si_p;
  
      processes.push_back(nuevo);
      std::cout << "added " << '\n';
    
}


vector<process *> processes;

int main(){
    add(processes,"p1",0,30);
    add(processes,"p2",0,30);
    add(processes,"p3",0,70);
    add(processes,"p4",0,50);
	
    std::thread first (planner);     // spawn new thread that calls foo()
	std::thread second (wait_to_add);  // spawn new thread that calls bar(0)

	first.join();                // pauses until first finishes
	second.join();               // pauses until second finishes

}