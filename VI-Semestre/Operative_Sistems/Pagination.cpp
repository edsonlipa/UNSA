#include <iostream>       // std::cout
#include <unistd.h>
#include <utility>
#include <queue>
#include <vector>
using namespace std;


#define Marco_size 20 //kb 
#define Memory 200 //kb


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

class Memoria
{
public:
    vector<marco *> marcos;
    size_t size;
    void print_marcos();
    Memoria(size_t size,int n_marcos);
    void run(vector<process *> &processes);
};

Memoria::Memoria(size_t size,int n_marcos){
    this->size=size;
    //this->marcos.resize(n_marcos);
    for(int i=0;i<n_marcos;i++)
	{
  
        this->marcos.push_back(new marco);
    }
    cout<<this->marcos.size()<<endl;
}

void Memoria::print_marcos(){
    cout<<this->marcos.size()<<endl;
    for(int i=0;i<this->marcos.size();i++)
	{
        cout<<"[ marco "<<i<<" ] "<<((this->marcos[i]->empty)?("vacios(sin uso)"):(this->marcos[i]->pro->name))<<endl;
//        cout<<"["<<i<<"] "<<this->marcos[i]->empty<<endl;
    }		
		
}
void Memoria::run(vector<process *> &processes){
    int timer=0;
    while(1){

        
        this->print_marcos();
        cout<<'\n';timer++;sleep(1);
	}
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


int main(){

    int  N_partitions = Memory/Marco_size;
    vector<process *> processes;
    Memoria RAM(Memory,N_partitions);

    add(processes,"p1",8,80);
    add(processes,"p2",10,50);
    add(processes,"p3",7,30);
    add(processes,"p4",5,120);
    add(processes,"p5",4,90);

    RAM.run(processes);

    return 0;
}