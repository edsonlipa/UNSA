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
  int size_p;

 	process(){};
 	~process();

 };

#define N_partitions 3
#define Memory 50

queue<process *> processes;
vector<pair<int,queue<process *>>> RAM(N_partitions);

int timer = 0;
bool play = true;

void init_ram(vector<pair<int,queue<process *>>> &RAM, vector<int> s) {
  for (size_t i = 0; i < N_partitions; i++) {
    RAM[i].first=s[i];
    std::cout << "size "<<RAM[i].first<< '\n';

  }

}
void add(vector<pair<int,queue<process *>>> &ram,string name,int a_t,int s_t,int p_p,int si_p)
{
	//nuevo listo ejecutando terminado
	process * nuevo = new process();
	nuevo->name=name;
	nuevo->t_llegada=a_t;
	nuevo->priority=p_p;
  nuevo->t_service=s_t;
	nuevo->size_p=si_p;
  for (int i = 0; i < N_partitions; i++) {
    if (ram[i].first>=si_p) {

      ram[i].second.push(nuevo);
      std::cout << "added " <<i+1<< '\n';
      i=N_partitions;
    }
  }

}


void planner()
{	while(1){

	if (play)
	{
      for (size_t i = 0; i < N_partitions; i++) {
        if (!RAM[i].second.empty()) {
          RAM[i].second.front()->t_service--;
          cout<<timer<<"     partition: "<<i<<"   process: "<<RAM[i].second.front()->name<<"   size process: "<<RAM[i].second.front()->size_p<<endl;

          if (RAM[i].second.front()->t_service==0) {
            RAM[i].second.pop();
          }
        }
        else{
          cout<<timer<<"     partition: "<<i<<"   process: empty"<<endl;
        }
      }
      std::cout  << '\n';
		// cout<<timer<<" "<<colas[colan].front()->name<<"       priority: "<<colan<<endl;timer++;
    timer++;
		sleep(2);
		}
	}
}

void wait_to_add()
{
	string agregar;
	string name;
	int t_service;
  int priority;
	int size;

	while(1){
	if(getline(cin,agregar))
		{
		play=false;
		cin>>name>>t_service>>size;

		add(RAM,name,timer,t_service,0,size);

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
  std::vector<int> sizes_Memory{10,15,25};
  init_ram(RAM,sizes_Memory);
	add(RAM,"p1",0,3,0,9);
	add(RAM,"p2",0,3,0,14);
  add(RAM,"p3",0,2,0,25);
	add(RAM,"p4",0,4,0,24);

  std::cout << "planner started \n";
	std::thread first (planner);     // spawn new thread that calls foo()
	std::thread second (wait_to_add);  // spawn new thread that calls bar(0)

	first.join();                // pauses until first finishes
	second.join();               // pauses until second finishes

	std::cout << "planner finished \n";

  return 0;
}
