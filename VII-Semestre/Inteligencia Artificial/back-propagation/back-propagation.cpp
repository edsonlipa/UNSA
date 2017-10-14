#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <vector>
#include <fstream>
#include <string>
#include <unistd.h>
using namespace std;

typedef std::vector<float> vecf;
typedef std::vector<vecf> matrix;
typedef std::vector<string> vecs;
#define umbral 0.05
#define alpha 0.1

void print_vect(vecf v) {
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
float sigmoide(float a){
	return 1/(1+exp(a*(-1)));
}
float dot(vecf vec1,vecf vec2){
  float sum=0;
  if (vec1.size()!=vec2.size()) {
    std::cout <<vec1.size()<< "/* error */ "<<vec2.size() << '\n';
    sleep(1);

  }
  for (size_t i = 0; i < vec1.size(); i++) {
    sum=sum+(vec1[i]*vec2[i]);
  }
  return sum;
}
float error(vecf so,vecf sd){
	float e=0;
  for (unsigned i = 0; i < so.size(); ++ i)
            e += pow((sd[i]-so[i]),2);
    return e/so.size();
}
vecf S(vecf x,matrix layer,bool type){
  vecf producto;
  if (type) {
    producto.push_back(1);
  }
  for (auto i:layer) {
    producto.push_back(dot(x,i));

  }
  for (size_t i = type; i < producto.size(); i++) {
      producto[i]=sigmoide(producto[i]);
  }
  return producto;
}

void leer_data(matrix &di, matrix &dout,vecf &data_train,vecf &data_test){

	ifstream file("database_iris.in");
	char c;string p="";int cont=0;

	vecf aux;
	vecf set;set.push_back(1);set.push_back(0);set.push_back(0);
	vecf ver;ver.push_back(0);ver.push_back(1);ver.push_back(0);
	vecf vir;vir.push_back(0);vir.push_back(0);vir.push_back(1);

	int act=1;
  aux.push_back(1);
	if(file.is_open())
  	{
    	while ( file.get (c) ){
      		if(c!=',' && c!='\n'){p+=c;}
      		else{
      			if(cont<4){
      				aux.push_back(strtof(p.c_str(),0));
      				cont++;
      			}
      			else{
      				di.push_back(aux);
      				if(p=="Iris-setosa"){dout.push_back(set);}
      				else if(p=="Iris-versicolor"){dout.push_back(ver);}
      				else{dout.push_back(vir);}
      				aux.clear();
              aux.push_back(1);
      				cont=0;
      				if(act%2==0 || act%5==0){data_train.push_back(act-1);}
      				else{data_test.push_back(act-1);}
      				act++;
      			}
      			p="";
      		}
    	}
    	file.close();
  	}
}
void print_data(matrix di,matrix dout){
  int count=0;
  for(int i=0;i<di.size();i++){
		for(int j=0;j<di[i].size();j++){

      cout<<di[i][j]<<"   ";
		}
    count++;
		cout<<"\t\t-> \t"<<dout[i][0]<<"--"<<dout[i][1]<<"--"<<dout[i][2]<<endl;
	}
  std::cout << count<<" registros" << '\n';

}
matrix create_layer(float n_neu,float n_input) {
  matrix matriz(n_neu,vecf(n_input));
  for (size_t i = 0; i < n_neu; i++) {
    for (size_t j = 0; j < n_input; j++) {
      matriz[i][j]=(rand()%10+1)/10.0;
    }
  }
  return matriz;
}

void changeLayerOut(matrix &w,vecf so,vecf sd,vecf &delta_out,vecf sh){
	for (unsigned i = 0; i < w.size (); ++ i){
		delta_out[i]=(sd[i]-so[i])*(1-so[i])*(so[i]);
        for (unsigned j = 0; j < w[i].size (); ++ j)
            w[i][j]-=alpha*((-1)*delta_out[i]*sh[j]);
	}
}
void changeLayerHide(matrix &w1,vecf s,vecf input,vecf delta,matrix w2){
	float d;
	for (unsigned i = 0; i < w1.size (); ++ i){
		float sum=0;
		for(unsigned k=0 ;k<w2.size();++k){
			sum+=w2[k][i]*delta[k];
		}
		d=sum*((1-s[i])*s[i]);
    for (unsigned j = 0; j < w1[i].size (); ++ j)
            w1[i][j]-=alpha*(d*input[j]);
	}
}

void RedNeuronal(vecf input,vecf output,matrix &w1,matrix &w2){

  fstream file;
  file.open("errores.dat", std::fstream::in | std::fstream::out | std::fstream::app);
  // print_matrix(w2);
  // print_matrix(w1);
	vecf sh=S(input,w1,1);
	vecf so=S(sh,w2,0);
  // print_vect(sh);
  // print_vect(so);
	float e=error(so,output);
	vecf delta (so.size());
	while(e>=umbral){
		changeLayerOut(w2,so,output,delta,sh);
    changeLayerHide(w1,sh,input,delta,w2);
    // sleep(1);
    sh=S(input,w1,1);
		so=S(sh,w2,0);
		e=error(so,output);
		file<<e<<endl;
	}
  file.close();
}

int testeo(matrix &w1,matrix &w2,vecf &input){
	vecf sh=S(input,w1,1);//printMatrix(sh);cout<<endl;
	vecf so=S(sh,w2,0);

  vecf uno{1,0,0};
  vecf dos{0,1,0};
  vecf tres{0,0,1};

  float e1=error(so,uno);
  // std::cout << "error de testeo "<<e << '\n';
  if(e1<=umbral){return 0;}
  float e2=error(so,dos);
  if(e2<=umbral){return 1;}
  float e3=error(so,tres);
	if(e3<=umbral){return 2;}
}

void pre_train(matrix &w1,matrix &w2,matrix data_input,matrix data_output,vecf train){
  print_matrix(w2);
  print_matrix(w1);

  fstream file;
  file.open("errores.dat", std::fstream::in | std::fstream::out | std::fstream::app);

  float prom=1;
  float e=1;

  while(prom>=umbral){
  for (unsigned i = 0; i < train.size (); ++ i){
      vecf sh=S(data_input[train[i]],w1,1);
      vecf so=S(sh,w2,0);
      vecf delta (so.size());
      changeLayerOut(w2,so,data_output[train[i]],delta,sh);
      changeLayerHide(w1,sh,data_input[train[i]],delta,w2);
      sh=S(data_input[train[i]],w1,1);
      so=S(sh,w2,0);
      e=error(so,data_output[train[i]]);
      prom+=e;
  	}
    prom=prom/w1.size();
    std::cout << "promedio: "<<prom << '\n';
    file<<prom << '\n';
  }
  file.close();
  std::cout << "fin pre train" << '\n';
		// cout<<e<<endl;
}
void train(matrix data_input,matrix data_output,vecf train,vecf test)
{
	matrix w1=create_layer(14,data_input[0].size());
	matrix w2=create_layer(3,w1.size()+1);
  print_matrix(w2);
  print_matrix(w1);
  pre_train(w1,w2,data_input,data_output,train);

	// for(intS
  print_matrix(w2);
  print_matrix(w1);

  float type=-1;
  matrix dispercion(3,vecf(3));
  for (size_t i = 0; i < test.size(); i++) {
    if (i%20==0) {type++;}
    dispercion[type][testeo(w1,w2,data_input[test[i]])]++;
  }
  print_matrix(dispercion);
  float efectividad=0;
        for (size_t i = 0; i < 3; i++) {
          efectividad+=(dispercion[i][i]*100)/20;
          /* code */
        }
std::cout << "efectividad "<<efectividad/3 <<"%"<< '\n';

}
void normalizacion(matrix &data_input,vecf data_train) {
  for (size_t i = 0; i < data_train.size(); i++) {
    float max=0;
    float min=10;
    for (size_t j = 1; j < data_input[i].size(); j++) {
      if (max>data_input[i][j])  max=data_input[i][j];
      if (min<data_input[i][j]) min=data_input[i][j];
    }
    for (size_t j = 1; j < data_input[i].size(); j++) {
      data_input[i][j]=(data_input[i][j]-min)/(max-min);
    }
  }
}
int main(int argc, char const *argv[]) {
  srand(time(NULL));

  matrix data_input;
	matrix data_out;
	vecf data_test;
	vecf data_train;
	leer_data(data_input,data_out,data_train,data_test);
  normalizacion(data_input,data_train);
  // print_data(data_input,data_out);
  train(data_input,data_out,data_train,data_test);

  return 0;
}
