#include <iostream>
#include <vector>
using namespace std;

typedef vector<int > veci;
typedef vector<veci > matrix;
typedef vector<vector<veci > > matrixs_vector;

void print_vect(veci v) {
  cout << "[";for(auto i:v){
  cout <<i<< ",";}
  cout << "]\n";
}

void print_matrix(matrix m){
  for (size_t i = 0; i < m.size(); i++) {
    std::cout << "["<<i<<"]";
    print_vect(m[i]);
  }
  std::cout  << '\n';
}

veci matrix_to_vector(matrix matriz) {
  // std::veci convertido(matriz.size()*matriz[0].size());
  veci convertido;
  for (size_t i = 0; i < matriz.size(); i++) {
    for (size_t j = 0; j < matriz.size(); j++) {
      convertido.push_back(matriz[i][j]);
    }
  }
}
matrix vector_to_matrix(veci vec) {
  // std::veci convertido(matriz.size()*matriz[0].size());
  int size=2;
  matrix convertido(size,veci(size));
  int k=0;
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      convertido[i][j]=vec[k]; k++;
    }
  }
  return convertido;
}

matrix multbyinverse(veci v){
  matrix ans(v.size(),veci (v.size()));
  for (size_t i = 0; i < v.size(); i++) {
    for (size_t j = 0; j < v.size(); j++) {
      ans[i][j]=v[i]*v[j];
    }
  }
  return ans;
}

veci operator *(veci v1,matrix m2){
  veci ans(v1.size());
  for (size_t i = 0; i < m2.size(); i++) {
    float sum=0;
    for (size_t j = 0; j < m2[0].size(); j++) {
      sum+=m2[j][i]*v1[j];
    }
    ans[i]=sum;
  }
  return ans;
}matrix operator -(matrix m1,matrix m2){
  matrix ans(m1.size(),veci (m1.size()));
  for (size_t i = 0; i < m1.size(); i++) {
    for (size_t j = 0; j < m1.size(); j++) {
      ans[i][j]=m1[i][j]-m2[i][j];
    }
  }
  return ans;
}
matrix operator +(matrix m1,matrix m2){
  matrix ans(m1.size(),veci (m1.size()));
  for (size_t i = 0; i < m1.size(); i++) {
    for (size_t j = 0; j < m1.size(); j++) {
      ans[i][j]=m1[i][j]+m2[i][j];
    }
  }
  return ans;
}

matrix identidad(int n){
  matrix ans(n,veci (n));
  for (size_t i = 0; i < n; i++) {
    ans[i][i]=1;
  }
  return ans;
}

matrix to_train(matrixs_vector &container,matrix inputs) {
  for ( auto i:inputs ) {
    container.push_back(multbyinverse(i)-identidad(i.size()));
  }
  int size_of_input=inputs[0].size();
  matrix ans(size_of_input,veci(size_of_input));
  for (auto i:container){
    ans=ans+i;
  }
  return ans;
}

veci recordar(veci in,matrix hopfield){
  veci nuevo=in*hopfield;
  for (auto &i:nuevo ) {
    if (i>0) i=1;
    else i=-1;
  }
  return nuevo;
}

int main(int argc, char const *argv[]) {
  veci input1{-1,-1,-1,1};
  matrix inputs{{-1,-1,1,1},{1,1,-1,-1}};
  matrixs_vector container;
  matrix hopfield=to_train(container,inputs);
  print_matrix(hopfield);
  print_vect(recordar(input1,hopfield));
  print_matrix(vector_to_matrix(recordar(input1,hopfield)));
  return 0;
}
