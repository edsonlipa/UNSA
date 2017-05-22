#include <iostream>
#include <map>
#include <queue>
#include <tuple>
#include "DisjointSet.h"
#include "mapheap.h"
using namespace std;

#define  INF 9999999
typedef tuple<string,double,string>    T_Arista;
typedef map<string,map<string,double>> T_graph;

struct comparator {
 bool operator()(T_Arista i, T_Arista j) {
 return get<1>(i) > get<1>(j);}
};

typedef priority_queue <T_Arista, vector<T_Arista>, comparator > minheap;

class Grafo
{
  private:
     T_graph graph;
     minheap heap;
  public:
    Grafo(){};
    void insert_vertex(string nombre)
    {
      auto it1=graph.find(nombre);
      if (it1==graph.end()) {
        graph[nombre];
        }
    };
    void insert_Arista(string nombre1, string nombre2, double val)
    {
      auto it1=graph.find(nombre1);
      auto it2=graph.find(nombre2);

      if (it1!=graph.end() && it2!=graph.end()) {
        graph[nombre1][nombre2]=val;
        graph[nombre2][nombre1]=val;
        heap.push(make_tuple(nombre1,val,nombre2));
      }
    };
    void mostrar()
    {
      for (auto i: graph){
        cout<<"Vertice:  "<<i.first<<endl;
          for (auto j:i.second) {
            std::cout << "\tdistancia: " << j.first <<"\thacia: " << j.second << std::endl;
          }
        }
    };
    T_graph kruskal()
    {
      DisjointSet SET;
      T_graph MST;
      for (auto i:graph)
        SET.make_set(i.first);
      while (!SET.joined()) {// mietras no visite todos los nodos
        T_Arista arst=heap.top();
        heap.pop();
        if (SET.merge(get<0>(arst),get<2>(arst))) {
          MST[get<0>(arst)][get<2>(arst)]=get<1>(arst);
        }
      }
      return MST;
    }

    T_graph Prim()
    {   T_graph MST;
        MapHeap MapHeaprim;
        string vertex = graph.begin()->first;
        for (auto i : graph) {
          if (i.first==vertex) {
            /* no hacer nada */
          } else {
            MapHeaprim.insert_tuple(i.first,INF,i.first);
          }
        }
        for (auto i: graph[vertex]) {
          auto it = MapHeaprim.find(i.first);
          if (i.second<it->second.second) {
            MapHeaprim.update_tuple(it,vertex,i.second);
          }
        }
        while (!MapHeaprim.empty()) {
          auto tuple_mapheap=MapHeaprim.top();// top() pointer to min
          string desde=tuple_mapheap->first;
          string hacia=tuple_mapheap->second.first;
          double distancia=tuple_mapheap->second.second;
          MST[desde][hacia]=distancia;
          MapHeaprim.pop();

          for (auto i: graph[desde]) {
            auto it = MapHeaprim.find(i.first);
            if (it!=MapHeaprim.end()) {
              if (i.second<it->second.second) {
                MapHeaprim.update_tuple(it,desde,i.second);
              }
            }
          }
        //  std::cout << "/* -------------------- */"<< std::endl;
          //MapHeaprim.show_MH();
          //std::cout << "/* -------------------- */" <<desde<< std::endl;

        }
        return MST;
    }
    void Dijkstra(string vertex)
    {   MapHeap MapHeapDjktr;
        map<string,pair<double,string>> v_route;
        double min_dist;
        for (auto i : graph) {//ena el mapheap
          if (i.first!=vertex)
            MapHeapDjktr.insert_tuple(i.first,INF,i.first);
        }
        for (auto i: graph[vertex]) {// primera actualizacion
          auto it = MapHeapDjktr.find(i.first);
              MapHeapDjktr.update_tuple(it,vertex,i.second);
        }

        while (!MapHeapDjktr.empty()) {
          auto tuple_mapheap=MapHeapDjktr.top();// top() pointer to min
          string actual=tuple_mapheap->first;
          string desde=tuple_mapheap->second.first;
          double distancia_base=tuple_mapheap->second.second;
          v_route[actual]=make_pair(distancia_base,desde);
          MapHeapDjktr.pop();
          for (auto i: graph[actual]) {
            auto it = MapHeapDjktr.find(i.first);
            if (it!=MapHeapDjktr.end()) {//
              if (i.second+distancia_base<it->second.second) {
                MapHeapDjktr.update_tuple(it,actual,i.second+distancia_base);
              }
            }
          }
        }
        for (auto j:v_route ) {
          cout<<"\t"<<j.first<<"\t desde "<<j.second.second<<"\tdistancia\t"<<j.second.first<<""<<endl;
        }
        
    }
};

int main(int argc, char const *argv[]) {

  Grafo grafito;

  grafito.insert_vertex("cero");
  grafito.insert_vertex("uno");
  grafito.insert_vertex("dos");
  grafito.insert_vertex("tres");
  grafito.insert_vertex("cuatro");
  grafito.insert_vertex("cinco");
  grafito.insert_vertex("seis");
  grafito.insert_vertex("siete");
  grafito.insert_vertex("ocho");
  grafito.insert_Arista("cero","uno",8);
  grafito.insert_Arista("cero","dos",12);
  grafito.insert_Arista("uno","dos",13);
  grafito.insert_Arista("uno","tres",25);
  grafito.insert_Arista("uno","cuatro",9);
  grafito.insert_Arista("dos","seis",21);
  grafito.insert_Arista("dos","tres",14);
  grafito.insert_Arista("tres","seis",12);
  grafito.insert_Arista("tres","cuatro",20);
  grafito.insert_Arista("tres","cinco",8);
  grafito.insert_Arista("tres","siete",12);
  grafito.insert_Arista("tres","ocho",16);
  grafito.insert_Arista("cuatro","cinco",19);
  grafito.insert_Arista("cinco","siete",11);
  grafito.insert_Arista("seis","ocho",11);
  grafito.insert_Arista("siete","ocho",9);

  //grafito.mostrar();
  T_graph MST=grafito.Prim();
  cout<<"********************"<<endl;
  for (auto i: MST){
    cout<<"Vertice:  "<<i.first<<endl;
      for (auto j:i.second) {
        std::cout << "\thacia:" << j.first <<"\tdistancia: \t" << j.second << std::endl;
      }
    }
    grafito.Dijkstra("cero");
  return 0;

}
/*En los casos en los que tengamos un grafo denso, nos convendrá usar el algoritmo de Prim.
En los casos en los que tengamos un grafo disperso, nos convendrá usar el algoritmo de kruskal.

DisjointSet resp;
vector<string> v({"A","B","C","D","E","F"});
resp.make_set(v);

cout <<(resp.merge("A","D")?"BIEN":"MAL") << endl;
resp.merge("B","C");
resp.merge("C","D");
resp.merge("E","F");
cout <<(resp.merge("B","D")?"BIEN":"MAL") << endl;
cout <<(resp.merge("A","B")?"BIEN":"MAL") << endl;
cout <<(resp.merge("C","F")?"BIEN":"MAL") << endl;
cout <<(resp.merge("C","E")?"BIEN":"MAL") << endl;
cout <<(resp.merge("C","E")?"BIEN":"MAL") << endl;
cout <<(joined()?"unido":"auno no esta unido") << endl;

grafito.insert_vertex("A");
grafito.insert_vertex("B");
grafito.insert_vertex("C");
grafito.insert_vertex("D");
grafito.insert_vertex("E");
grafito.insert_vertex("F");
grafito.insert_Arista("A","D",1);
grafito.insert_Arista("A","B",3);
grafito.insert_Arista("B","D",3);
grafito.insert_Arista("B","C",1);
grafito.insert_Arista("D","C",1);
grafito.insert_Arista("D","E",6);
grafito.insert_Arista("C","E",5);
grafito.insert_Arista("C","F",4);
grafito.insert_Arista("E","F",2);


grafito.insert_vertex("cero");
grafito.insert_vertex("uno");
grafito.insert_vertex("dos");
grafito.insert_vertex("tres");
grafito.insert_vertex("cuatro");
grafito.insert_vertex("cinco");
grafito.insert_vertex("seis");
grafito.insert_vertex("siete");
grafito.insert_vertex("ocho");
grafito.insert_Arista("cero","uno",8);
grafito.insert_Arista("cero","dos",12);
grafito.insert_Arista("uno","dos",13);
grafito.insert_Arista("uno","tres",25);
grafito.insert_Arista("uno","cuatro",9);
grafito.insert_Arista("dos","seis",21);
grafito.insert_Arista("dos","tres",14);
grafito.insert_Arista("tres","seis",12);
grafito.insert_Arista("tres","cuatro",20);
grafito.insert_Arista("tres","cinco",8);
grafito.insert_Arista("tres","siete",12);
grafito.insert_Arista("tres","ocho",16);
grafito.insert_Arista("cuatro","cinco",19);
grafito.insert_Arista("cinco","siete",11);
grafito.insert_Arista("seis","ocho",11);
grafito.insert_Arista("siete","ocho",9);


*/
