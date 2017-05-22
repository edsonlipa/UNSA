#include <iostream>
#include <map>
#include <queue>
#include <tuple>

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
  bool empty()
  {
    return map.empty();
  }
  void pop()
  {

    map.erase(heap.top());
    heap.pop();
  }
  void update()
  {
    ret i=map.insert(make_pair("undesafortunadoqueseeliminara",make_pair(" ",-999999)));
    heap.push(i.first);
    heap.pop();
    map.erase("undesafortunadoqueseeliminara");

  }
  itMH find(string a)
  {
    return map.find(a);
  }
  itMH end(){
    return map.end();
  }
  void update_tuple(itMH i,string a,double n) {
    map[i->first]=make_pair(a,n);
    update();

  }
  void show_MH() {
    for (auto i : map ) {
      cout<<i.first<<"\t"<<i.second.second<<"\t"<<i.second.first<<""<<endl;
    }
  }
};
