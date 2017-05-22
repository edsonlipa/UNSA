#include <iostream>
#include <fstream>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;
typedef vector<float> vec;
typedef vector<vec> matrix;
#define n 100
#define rangue 1000
void merge(vec &arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(vec &arr, int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}
void print_vector(vec v)
{
  std::cout << "[";for(auto i:v){
    std::cout <<i<< ",";}
    std::cout << "]\n";
  }
void init_matrix(matrix &matriz) {
  srand (time(NULL));
  for(auto &i:matriz){
    for(auto &j:i){
      j = rand()%rangue;
    }
    // print_vector(i);
  }
}
void init_vector(vec &vec1) {
    srand (time(NULL));
    for(auto &j:vec1){
      j = rand()%rangue;
    }
    // print_vector(i);
}
void counting_sort(vec &v) {
  vec buff(rangue);
  vec sorted(v.size());
  for (auto &i:v) {
    buff[i]++;
  }
  for (size_t i = 0; i < buff.size()-1; i++) {
    buff[i+1]=buff[i]+buff[i+1];
  }
  for (size_t i = 0; i < sorted.size(); i++) {
    buff[v[i]]--;
    sorted[buff[v[i]]]=v[i];
  }
  v=sorted;
}
void sort_matrix(matrix &matriz) {
  for(auto &i:matriz){
    counting_sort(i);
    // print_vector(i);
  }
}
void write_file(ofstream& file,float x,float y){
  file<<x<<"\t"<<y<<'\n';
}
float get_averge() {
  ofstream myfile;
  myfile.open("data.dat");

  for (size_t i = 1; i < 1000; i++) {
    int size=n*i;
    std::cout << "/* message */"<< size<< '\n';
    float sum=0;
    vec por_ordenar(size);

    for (size_t j = 0; j < 100; j++) {
      init_vector(por_ordenar);
      auto start = chrono::high_resolution_clock::now();
      mergeSort(por_ordenar,0,size-1);
      // counting_sort(por_ordenar);
      // print_vector(por_ordenar);
      auto finish = chrono::high_resolution_clock::now();
      chrono::duration<float> elapsed = finish - start;
      float  microseconds = elapsed.count()*1000000;
      sum=sum+(elapsed.count());
    }

    // std::cout << "/* es tiempo es: */"<<elapsed.count()<<" segundos." << '\n';
    // std::cout << "/* es tiempo en microsegundos: */"<<microseconds << '\n';
    // prom.push_back(microseconds*0.01);
    write_file(myfile,size,sum/100);
  }
  myfile.close();
  // return sum/n;
}
float get_averge2() {
  ofstream myfile;
  myfile.open("data.dat");

  for (size_t i = 1; i < 200; i++) {
    int size=n*i/2;
    std::cout << "ordenando vector de "<< size<<" espacios"<< '\n';
    float min=999;
    vec por_ordenar(size);

    for (size_t j = 0; j < 100; j++) {
      init_vector(por_ordenar);
      auto start = chrono::high_resolution_clock::now();
      mergeSort(por_ordenar,0,size-1);
      auto finish = chrono::high_resolution_clock::now();
      chrono::duration<float> elapsed = finish - start;
      float  seconds = elapsed.count()*1000000;
      float  microseconds = elapsed.count();
      if (min>microseconds) {
        // std::cout << "el nuevo minimo es "<<j<<" min "<<microseconds << '\n';
          min=microseconds;}
    }
    write_file(myfile,size,min);
  }
    myfile.close();
}
void set_gnp(float promedio) {
  ofstream myfile;
  myfile.open("gnuplot.gnp");
  myfile<<"plot \"data.dat\" using 1:2 with lines"<<"\n";
  myfile<<"pause -1 \"Hit any key to continue\"\n";

  myfile.close();
}
int main(int argc, char const *argv[]) {


  float promedio=get_averge();
  std::cout << "promedio " <<promedio<< '\n';
  // set_gnp(promedio);

  system("gnuplot gnuplot.gnp");

  return 0;
}
