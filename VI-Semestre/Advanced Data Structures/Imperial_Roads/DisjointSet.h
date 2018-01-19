#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>

using namespace std;
typedef tuple<string,double,string>    T_Arista;
struct comparator {
        bool operator()(T_Arista i, T_Arista j) {
                return get<1>(i) > get<1>(j);}
              };
            

typedef priority_queue <T_Arista, vector<T_Arista>, comparator > minheap;
class DisjointSet {
    private:
    map<string,string> parent;

    public:
    DisjointSet(int n_sets){
      for(int i=1;i<=n_sets;i++)
      this->make_set(to_string(i));
    }
    void make_set(vector<string> elements);
    void make_set(string element);
    string find(string element);
    size_t size();
    bool merge(string elment_a,string element_b);
    void mostrar();
    bool joined();
    int mst(string ele1,string ele2,int roads, minheap arist);

};
void DisjointSet::make_set(vector<string> elements)
{
  for (auto i:elements) parent[i]=i;
}
void DisjointSet::make_set(string element)
{
  parent[element]=element;
}
string DisjointSet::find(string element)
{
  if (parent[element]==element) {
    return element;
  }
  return parent[element]=find(parent[element]);
}

bool DisjointSet::merge(string element1,string element2)
{
  string f1 = find(element1), f2 = find(element2);
  
  if (f1==f2) return false;
  if (f1<f2) {
    parent[f2]=f1;
    //cout<<"fi es el menor"<<endl;
    //mostrar();
//
    return true;
  } else {
    parent[f1]=f2;
    //mostrar();
    return true;
  }
}
bool DisjointSet::joined()
{
  string senior_father=parent.begin()->first;
  for (auto i:parent ) {
    if (find(i.first)!=senior_father) {
      return false;
    }
  }
  return true;
}
size_t DisjointSet::size()
{
  return parent.size();
}
void DisjointSet::mostrar()
{
  cout<<"-------------------------------"<<endl;
  for (auto i:parent) {
    cout<<i.first<<" : "<<i.second<<endl;
  }
}
int DisjointSet::mst(string ele1,string ele2,int roads, minheap arists)
{
  int cost=0;
  if(this->merge(ele1,ele2)){
  }
  int size=arists.size();
  for(int i=0;i<size;i++){
 //   cout<<" size"<<arists.size()<<endl;
  T_Arista arst=arists.top();
  arists.pop();
   //     cout<<"---------------------"<<get<0>(arst)<<" "<<get<2>(arst)<<endl;
        if (this->merge(get<0>(arst),get<2>(arst))) {
          cost+=get<1>(arst);
     //     cout<<"merge"<<get<0>(arst)<<" "<<get<2>(arst)<<endl;
        }
        else if((get<0>(arst)==ele1&&get<2>(arst)==ele2)||(get<0>(arst)==ele2&&get<2>(arst)==ele1))
        {
          cost+=get<1>(arst);
       //   cout<<"encontro "<<get<0>(arst)<<get<2>(arst)<<endl;
        }
      }
      return cost;
}
