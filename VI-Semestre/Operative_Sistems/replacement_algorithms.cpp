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
	int id;
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
    int marco_actual=-1;
    int peticion_actual=0;
    int remplaceds=0;
    size_t size;
    void print_marcos();
    bool find(int id);
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
}

void Memoria::print_marcos(){
    for(int i=0;i<this->marcos.size();i++)
	{
//        cout<<"["<<i<<"] "<<((this->marcos[i]->empty)?(0):(this->marcos[i]->pro->id))<<endl;
        cout<<"   "<<((this->marcos[i]->empty)?(0):(this->marcos[i]->pro->id))<<" ";
    }	
    cout<<endl;	
		
}
bool Memoria::find(int id){
    for(int i=0;i<this->marcos.size();i++)
	{
        if(!this->marcos[i]->empty&&this->marcos[i]->pro->id==id){
            return true;
        }
    }
    return false;
}
void Memoria::run(vector<process *> &processes){
    int timer=0;
    while(this->peticion_actual< processes.size()){

        if(!this->find(processes[this->peticion_actual]->id)){
            marco_actual=(marco_actual+1)%this->marcos.size();
            this->marcos[this->marco_actual]->pro=processes[this->peticion_actual];
            if(this->marcos[this->marco_actual]->empty)this->marcos[this->marco_actual]->empty=false;
            else this->remplaceds++;
            
            
        }
        peticion_actual++;
        this->print_marcos();
        timer++;
        //sleep(1);
    }
    cout<<"numero de cambios"<<this->remplaceds<<endl;
        
}
void add(vector<process *> &processes,string name,int id)
{
	//nuevo listo ejecutando terminado
	process * nuevo = new process();
	nuevo->name=name;
    nuevo->id=id;
  
      processes.push_back(nuevo);
      std::cout << "added " << '\n';
    
}


int main(){

    
    int  N_marcos = 4;
    //cout<<"ingrese n marcos"<<endl
    //cin>>n_marcos;
    vector<process *> processes;
    /*cout<<"ingrese n peticiones"<<endl
    int n_peticiones;
    cin>>n_peticiones;
    for(int i=0;i<n_peticiones;i++){
        int id_p;
        cin>>id_p;    
        add(processes,"p",id_p);
            
    }*/
    Memoria RAM(Memory,N_marcos);

    add(processes,"p1",1);
    add(processes,"p4",4);
    add(processes,"p2",2);
    add(processes,"p3",3);
    add(processes,"p2",2);
    add(processes,"p5",5);
    add(processes,"p4",4);
    add(processes,"p1",1);
    add(processes,"p7",7);
    add(processes,"p2",2);
    add(processes,"p8",8);
    add(processes,"p6",6);

    RAM.run(processes);

    return 0;
}