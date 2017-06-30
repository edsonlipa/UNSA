#include<iostream>
#include<time.h>
#include <algorithm>
#include<vector>
using namespace std;
typedef vector<double> vecdo;
void print_vector(vecdo v)
{
    cout << "[";for(auto i:v){
    cout <<i<< ",";}
    cout << "]\n";
}
vecdo merge(vecdo L,vecdo R)
{ vecdo nuevo;
  int i = 0;
  int j = 0;
  while (i<L.size()&&j<R.size()){
      if (L[i] <= R[j]){
          nuevo.push_back(L[i]);
          i++;
      }
      else{
        nuevo.push_back(R[j]);

          j++;
      }
  }
  while (i < L.size())
  {
    nuevo.push_back(L[i]);
      i++;
  }
  while (j < R.size())
  {
      nuevo.push_back(R[j]);
      j++;
  }
  nuevo.erase(unique(nuevo.begin(),nuevo.end() ),nuevo.end());
  return nuevo;
}
void ShellSort(vecdo &a,int n) {
  int i,j,intervalo,temp;
  intervalo=n/2;
  while (intervalo>0) {
    for (size_t i = intervalo; i < n; i++) {
      j=i;
      temp=a[i];
      while (j>=intervalo&&a[j-intervalo]>temp) {
        a[j]=a[j-intervalo];
        j=j-intervalo;
      }
      a[j]=temp;
    }
    intervalo=intervalo/2;
  }
}
void QuickSort(vecdo &a,int l,int r) {
  int i=l,j=r;
  int temp;
  int piv=a[(l+r)/2];
  do {
    while (a[i]<piv)i++;
    while (piv<a[j]) {
      j--;
    }
    if (i<=j) {
      if (i!=j) {
        temp=a[i];
        a[i]=a[j];
        a[j]=temp;
      }
      i++;
      j--;
    }
  } while(i<=j);
  if (l<j) {
    QuickSort(a,l,j);
  }
  if (i>r) {
    QuickSort(a,i,r);
  }
}
int smaller(int a, int b)
{
    return a - b;
}

int bigger(int a, int b)
{
    return b - a;
}
void quicksort(vecdo &tab, int start, int end, int (*comparer)(int, int))
{
    int i=start;
    int j=end;
    int mid = (end / 2 - start / 2) / 2 * 2 + start;
    // std::cout << start<< " "<< mid<< " "<<end << " " << '\n';
    int x=tab[mid];
    do {
        while(comparer(tab[i],x) < 0) i+=2;
        while(comparer(tab[j],x) > 0) j-=2;
        if(i<=j) {
            // std::cout <<i<<"[" <<tab[i]<<"] cambiando "<<j <<" ["<<tab[j]<<"]" << '\n';
            int tmp=tab[i];
            tab[i]=tab[j];
            tab[j]=tmp;
            i+=2;
            j-=2;
        }
    } while(i<=j);
    if(start<j) quicksort(tab,start,j, comparer);
    if(i<end) quicksort(tab,i,end, comparer);
}
vecdo generate(int n){
  vecdo g;
  for (size_t i = 0; i < n; i++) {
    g.push_back(rand()%100+1);
  }
  return g;
}
int main(int argc, char const *argv[]) {
  srand(time(NULL));

  bool run=true;
  vecdo test1=generate(30);
  vecdo test2=generate(30);
  while (run) {

    std::cout  <<"vector a ordenar -----------------------------------"<< '\n';
    // print_vector(test);
    std::cout << "Escoja 1 para resolver con QuickSort" << '\n';
    std::cout << "Escoja 2 para resolver con ShellSort" << '\n';
    std::cout << "Escoja 3 para unir dos arreglso ordenados" << '\n';
    std::cout << "Escoja 4 para ordenar pares acendente y inpares decendentes" << '\n';
    std::cout << "Escoja 0 para salir" << '\n';
    int opt;
    std::cin >> opt ;
    switch (opt) {
      case 0: run=false;break;
      case 1:{QuickSort(test1,0,test1.size()-1);
              std::cout << "ordenamiento con QuickSort" << '\n';
              print_vector(test1);break;}
      case 2:{ShellSort(test1,test1.size());
              std::cout << "ordenamiento con ShellSort" << '\n';
              print_vector(test1);break;}
      case 3:{ShellSort(test1,test1.size());
              QuickSort(test2,0,test2.size()-1);
              print_vector(test1);
              print_vector(test2);

              print_vector(merge(test1,test2));
              break;}
      case 4:{
              print_vector(test2);
              quicksort(test2, 0, test2.size(), &smaller);
              print_vector(test2);
              std::cout << "----------------------------------" << '\n';
              quicksort(test2, 1, test2.size()-1, &bigger);
              print_vector(test2);

              break;}
              default: break;
    }
    std::cout << '\n';

  }
  return 0;
}
