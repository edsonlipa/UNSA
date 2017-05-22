#include <iostream>
#include <map>
#include <queue>
#include <tuple>
#include <functional>
#include <algorithm>
#include <typeinfo>

using namespace std;


typedef pair<double,string>           T_Arista;
typedef vector<T_Arista>              T_Aristas;
typedef map<string,pair<bool,T_Aristas>> T_Grafo;
struct comparator {
 bool operator()(T_Arista i, T_Arista j) {
 return i.first > j.first;
 }
};
typedef priority_queue <T_Arista, vector<T_Arista>, comparator > minheap;
typedef tuple<string,double,string>    T_Arista_reult;

class Grafo
{
  private:
     T_Grafo  mi_Grafo;
  public:
    Grafo(){};
    void insert_vertex(string nombre)
    {
      auto it1=mi_Grafo.find(nombre);
      if (it1==mi_Grafo.end()) {
        mi_Grafo[nombre]=make_pair(false,T_Aristas());
        }
    }
    double val(string nombre1,string nombre2)
    {
      auto it1=mi_Grafo.find(nombre1);
      auto it2=mi_Grafo.find(nombre2);

      if (it1!=mi_Grafo.end() && it2!=mi_Grafo.end()) {
        for (auto i:it1->second.second ) {
          if (i.second==nombre2) {
            std::cout << i.first<< std::endl;
            return i.first;
            }
          }
      }
      else std::cout << "una de las claves no existe" << std::endl;

    };

    void insert_Arista(string nombre1, string nombre2, double val)
    {
      auto it1=mi_Grafo.find(nombre1);
      auto it2=mi_Grafo.find(nombre2);

      if (it1!=mi_Grafo.end() && it2!=mi_Grafo.end()) {
        T_Arista nueva_arista = make_pair(val,nombre2);
        mi_Grafo[nombre1].second.push_back(nueva_arista);
        nueva_arista = make_pair(val,nombre1);
        mi_Grafo[nombre2].second.push_back(nueva_arista);
      }
    }

    void mostrar()
    {
      for (auto i: mi_Grafo){
        cout<<"Vertice:  "<<i.first<<endl;
          for (auto j:i.second.second) {
            std::cout << "\tdistancia: " << j.first <<"\thacia: " << j.second << std::endl;
          }
        }
    }

    void kruskall() {// Arbol de Expancion Minima MST
      vector<T_Arista_reult> MST;
      minheap heap;
      for (auto j:mi_Grafo.begin()->second.second) {
        heap.push(j);
      }
      while (mi_Grafo.size()-1>MST.size()) {// mietras no visite todos los nodos

      }
    }
    /*bool ciclos(string vertice) {
      for (auto i:mi_Grafo[Vertice].second) {
        if (mi_Grafo[i.second]) {

        }
      }
    }
    *//*
    void heap_prev() {
      minheap heap;
      for (auto j:mi_Grafo.begin()->second.second) {
        heap.push(j);
      }
      std::cout << heap.top().second << std::endl;

    };*/

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
    //grafito.val("arequipa","lima");
    grafito.mostrar();
    //grafito.heap_prev();
    return 0;
}
