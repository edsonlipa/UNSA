#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

class DisjointSet {
    private:
    map<string,string> parent;

    public:
    DisjointSet(){};
    void make_set(vector<string> elements);
    void make_set(string element);
    string find(string element);
    size_t size();
    bool merge(string elment_a,string element_b);
    void mostrar();
    bool joined();

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
  if (parent[element1]==parent[element2]) return false;
  string f1 = find(element1), f2 = find(element2);
  if (f1<f2) {
    parent[f2]=f1;
    cout<<"fi es el menor"<<endl;
    mostrar();

    return true;
  } else {
    parent[f1]=f2;
    mostrar();
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
