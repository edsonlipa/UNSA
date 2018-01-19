#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <unistd.h>
#include <utility>   
#include <queue>   
#include <vector>

using namespace std;



class process
 {
 public:
	string name;
	int t_llegada;
	int t_service;
	int priority;
	int t_final;
	int t_retorno;
	int t_espera;

 	process(){};
 	~process();
 	
 }; 

//vector<string> queue;
vector<queue<process *>> colas(10);
int timer = 0;
bool play = true;


void add(vector<queue<process *>> &processes,string name,int a_t,int s_t,int p_p)
{
	//nuevo listo ejecutando terminado
	process * nuevo = new process();
	nuevo->name=name;
	nuevo->t_llegada=a_t;
	nuevo->priority=p_p;
	nuevo->t_service=s_t;

	while(!processes[1].empty()){
		processes[0].push(processes[1].front());
		processes[1].pop();
	}
	processes.erase(processes.begin()+1);
	processes.push_back(queue<process*>());
	processes[p_p].push(nuevo);
	

}


void planner() 
{	while(1){

//	cout<<"process "<<(processes[Queue]).second[1]<<endl;
	//if(timer==(processes[Queue]).second[1]){
//	cout<<processes[Queue].first<<endl;}
	int colan=0;
	while (colas[colan].empty())
	{
		colan++;colan=colan%10;
	}

	if (play)
	{
		colas[colan].front()->t_service--;
		
		cout<<timer<<" "<<colas[colan].front()->name<<"       priority: "<<colan<<endl;timer++;
			if (colas[colan].front()->t_service==0)
			{
				colas[colan].pop();
			}
		sleep(1);
		}
	}
}

void wait_to_add()
{
	string agregar;
	string name;
	int t_service;
	int priority;

	while(1){
	if(getline(cin,agregar))
		{
		play=false;
		cin>>name>>t_service>>priority;

		add(colas,name,timer,t_service,priority);
		cout<<"added"<<endl;
		
		getline(cin,agregar);
		play=true;
		}
	}		
}

void show(string)
{

}

int main() 
{

	add(colas,"p1",0,3,0);
	add(colas,"p2",0,3,1);
	add(colas,"p3",0,2,2);

	std::thread first (planner);     // spawn new thread that calls foo()
	std::thread second (wait_to_add);  // spawn new thread that calls bar(0)
	std::cout << "planner started \n";

		//std::this_thread::sleep_for(std::chrono::milliseconds(100000));
	    
		// synchronize threads:
	first.join();                // pauses until first finishes
	second.join();               // pauses until second finishes

	std::cout << "planner finished \n";

  return 0;
}