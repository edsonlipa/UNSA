#include <iostream>
#include <map>
#include <queue>
#include <tuple>
#include "DisjointSet.h"
using namespace std;
typedef tuple<string,double,string>    T_Arista;
typedef map<string,pair<string,double>> mapa;
typedef map<string,pair<string,double>>::iterator itMH;
typedef pair<itMH,bool> ret;
struct compMapHeap {
 bool operator()(itMH i, itMH j) {
 return (*i).second.second > (*j).second.second;}
};

typedef priority_queue <itMH, vector<itMH>, compMapHeap > minheapIT;

class MapHeap{
public:
  MapHeap(){}
  mapa map;
  minheapIT heap;

  void insert_tuple(string a,double n,string b) {
    ret i=map.insert(make_pair(a,make_pair(b,n)));
    heap.push(i.first);
  }
  itMH top()
  {
    return heap.top();
  }
  void pop()
  {
    std::cout << "/* message */"<<heap.top()->first<<" a "<<heap.top()->second.first << std::endl;
    map.erase(heap.top());
    heap.pop();
  }
  void update()
  {

    ret i=map.insert(make_pair("undesafortunadoqueseeliminara",make_pair("",-99999)));
    heap.push(i.first);
    map.erase("undesafortunadoqueseeliminara");
    heap.pop();
  }
  itMH find(string a)
  {
    return map.find(a);
  }
  void update_tuple(itMH i,string a,double n) {
    map[i->first]=make_pair(a,n);
    update();

  }
};
int main(int argc, char const *argv[]) {
  MapHeap mapita;
  mapita.insert_tuple("a",5,"b");
  mapita.insert_tuple("c",2,"b");
  std::cout << "/* message */" <<(mapita.top())->first<<(mapita.top())->second.second<< std::endl;

  mapita.update_tuple(mapita.find("c"),"a",6);
  std::cout << "/* message */" <<(mapita.top())->first<<(mapita.top())->second.second<< std::endl;


  return 0;
}
