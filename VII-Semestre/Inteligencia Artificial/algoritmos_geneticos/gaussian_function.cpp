#include <algorithm>    // std::find
#include <map>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <cmath>

using namespace std;
typedef vector<float> vec;
typedef map<char,vec > chromosomes;
typedef vector<chromosomes> population;

#define popu_size    20
#define chromo_size  5
#define generations  100

int BinToDec(vec bits)
{
    int val = 0;
    int value_to_add = 1;

    for (int i = bits.size()-1; i > 0; i--)
    {
        if (bits[i] == 1)
            val += value_to_add;
        value_to_add *= 2;
    }
    return val;
}

void print_chromosome(vec c) {
  std::cout << "[";
  for (auto i:c ) {
    std::cout << " "<<i<<" " ;
  }
  std::cout << "]"<< '\n';
}
void prin_population(population &p) {
  for (auto i:p) {
    print_chromosome(i['x']);
    print_chromosome(i['y']);
    std::cout << "/* */"<<i['f'][0] << '\n';
  }
}
vec get_random_chromosome(int n){
  vec chromo;
  for (size_t i = 0; i < n; i++) {
      chromo.push_back(rand()%2);
  }
  return chromo;
}
float fitnes_function(int x, int y){
  // std::cout << "--------------gaussian_function----------" << '\n';
  return 1/sqrt(0.05*M_PI) * exp(-((x*x) + (y*y))/2);
  // return 1/((1500^2)*sqrt(2*M_PI))*exp(-(pow((x-4096),2)+pow((y-4096)^2))/(2*(1500^2)));
}

void init_population(population &p) {
  std::cout << "--------------init popilation-------------" << '\n';
  for (auto &i:p) {
    i['x']=get_random_chromosome(chromo_size);
    // print_chromosome(i['x']);
    i['y']=get_random_chromosome(chromo_size);
    // print_chromosome(i['y']);
    // std::cout << "decimal "<<BinToDec(i['y']) << '\n';
  }
}

void selection(population &p) {
  int x,y; //feactures [0]=fitnes
  float sum=0;
  for (auto &i:p) {
    x=BinToDec(i['x']);
    y=BinToDec(i['y']);
    // std::cout <<x <<" " <<y<< '\n';
    float fit=fitnes_function(x,y);
    i['f'].push_back(fit);
    // std::cout << "fitnes :"<<i['f'][0] << '\n';
    sum+=fit;
  }
  for (size_t i = 0; i < p.size(); i++) {
    if (i!=0) {
      p[i]['f'].push_back(p[i]['f'][0]/sum);
      p[i]['f'].push_back(p[i-1]['f'][1]+p[i]['f'][1]);
    }else{
      p[i]['f'].push_back(p[i]['f'][0]/sum);
      p[i]['f'].push_back(p[i]['f'][0]/sum);
    }
  }
  vec selected;
  while (selected.size()<popu_size) {

    double random=(((rand()%100)+1)/100);
      for (size_t i = 0; i < popu_size*2; i++) {

        // std::cout << "selected"<<random<<" "<<selected.size() << '\n';
        if (p[i]['f'][1]>random) {
            vec::iterator it;

             it = find (selected.begin(), selected.end(), i);
             if (it == selected.end()){
               selected.push_back(i);
               break;

             }
           }
      }
  }
  population new_population;
  for (size_t i = 0; i < selected.size(); i++) {
    new_population.push_back(p[i]);
  }
  p.clear();
  p=new_population;
  new_population.clear();

}
void crossover(chromosomes a,chromosomes b,chromosomes &c,chromosomes &d) {
  int mid=chromo_size/2;
  c['x']=a['x'];
  c['y']=a['y'];
  d['x']=b['x'];
  d['y']=b['y'];
  for (size_t i = mid; i < chromo_size; i++) {

    swap(c['x'][i],d['x'][i]);
    swap(c['y'][i],d['y'][i]);

  }
}
void new_generation(population &p) {
  for (size_t i = 0; i < popu_size/2; i++) {
    // std::cout << "new_generation" << '\n';
    float padre2random=(rand()%popu_size);
    float padre1random=(rand()%popu_size);
    chromosomes child1;
    chromosomes child2;
    crossover(p[padre1random],p[padre2random],child1,child2);
    p.push_back(child1);
    p.push_back(child2);

  }
}

void mutar(chromosomes a) {
  float chrorandx=(rand()%chromo_size);
  float chrorandy=(rand()%chromo_size);
  if (a['x'][chrorandx]==1) {
    a['x'][chrorandx]=0;
  }else{
    a['x'][chrorandx]=1;
  }
  if (a['y'][chrorandy]==1) {
    a['y'][chrorandy]=0;
  }else{
    a['y'][chrorandy]=1;
  }
}
void mutacion(population &p) {
  for (size_t i = 0; i < popu_size/5; i++) {
    float porand=(rand()%popu_size);
    mutar(p[porand]);
  }
}
int main(int argc, char const *argv[]) {
  srand((int)time(NULL));
  population gaussian_population(popu_size);
  init_population(gaussian_population);
  for (size_t i = 0; i < 1000; i++) {
      new_generation(gaussian_population);
      // std::cout << "gaussian_population"<<gaussian_population.size() << '\n';

      std::cout << "new_generation" << '\n';
      selection(gaussian_population);
      mutacion(gaussian_population);
      std::cout << "gaussian_population"<<gaussian_population.size() << '\n';
      prin_population(gaussian_population);

  }
  return 0;
}
