#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <fstream>
#include <string>
#include <vector>

#define umbral 0.005
#define alpha 0.005

using namespace std;
using namespace boost::numeric::ublas;

typedef std::vector<float> vector_float;
typedef std::vector<vector_float> matrix_float;
typedef std::vector<string> vector_string;

float sigmoide(float a){
	return 1/(1+exp(a*(-1)));
}

void printMatrix(matrix<float> m){
	for (unsigned i = 0; i < m.size1 (); ++ i){
        for (unsigned j = 0; j < m.size2 (); ++ j)
            cout<<m (i, j)<<" ";
        cout<<endl;
    }
}

matrix<float> S(matrix<float> i,matrix<float> layer,bool type){
	matrix<float> p=prod(layer,i);
	matrix<float> out;
	int s;

	if(type){out=matrix<float>(p.size1()+1,p.size2());out(0,0)=1;s=1;}
	else {out=matrix<float>(p.size1(),p.size2());s=0;}

	for (unsigned i = 0; i < p.size1 (); ++ i)
        for (unsigned j = 0; j < p.size2 (); ++ j)
            out (i+s, j)=sigmoide(p(i,j));
	return out;
}

matrix<float> createLayer(float n_neu,float n_input){
	matrix<float> m(n_neu,n_input);
	for (unsigned i = 0; i < m.size1 (); ++ i)
        for (unsigned j = 0; j < m.size2 (); ++ j)
            m (i, j) = (rand()%10+1)/10.0;
    return m;
}

float error(matrix<float> so,matrix<float> sd){
	float e=0;
	for (unsigned i = 0; i < so.size1 (); ++ i)
        for (unsigned j = 0; j < so.size2 (); ++ j)
            e += pow((sd(i,j)-so(i,j)),2);
    return e/so.size1();
}

void changeLayerOut(matrix<float> &w,matrix<float> so,matrix<float> sd,matrix<float> &delta_out,matrix<float> sh){
	for (unsigned i = 0; i < w.size1 (); ++ i){
		delta_out(i,0)=(sd(i,0)-so(i,0))*(1-so(i,0))*(so(i,0));
        for (unsigned j = 0; j < w.size2 (); ++ j)
            w(i,j)-=alpha*((-1)*delta_out(i,0)*sh(j,0));
	}
}

void changeLayerHide(matrix<float> &w1,matrix<float> s,matrix<float> input,matrix<float> delta,matrix<float> w2){
	float d;
	for (unsigned i = 0; i < w1.size1 (); ++ i){
		float sum=0;
		for(unsigned k=0 ;k<w2.size1();++k){
			sum+=w2(k,i)*delta(k,0);
		}
		d=sum*(1-s(i,0))*s(i,0);

        for (unsigned j = 0; j < w1.size2 (); ++ j)
            w1(i,j)-=alpha*(d*input(j,0));
	}
}

void RedNeuronal(matrix<float> input,matrix<float> output,matrix<float> &w1,matrix<float> &w2){

	matrix<float> sh=S(input,w1,1);//printMatrix(sh);cout<<endl;
	matrix<float> so=S(sh,w2,0);

	float e=error(so,output);
	matrix<float> delta (so.size1(),so.size2());
	while(e>=umbral){
		changeLayerOut(w2,so,output,delta,sh);//cout<<delta.size1()<<" "<<delta.size2()<<endl;
		changeLayerHide(w1,sh,input,delta,w2);
		sh=S(input,w1,1);
		so=S(sh,w2,0);
		e=error(so,output);
		//cout<<e<<endl;
	}
}

matrix<float> toMatrix(vector_float a,int s){
	matrix<float> r(a.size()+s,1);
	r(0,0)=1;
	for(int i=0;i<a.size();i++){
		r(i+s,0)=a[i];
	}
	return r;
}

bool testeo(matrix<float> &w1,matrix<float> &w2,matrix<float> &input,matrix<float> &output){
	matrix<float> sh=S(input,w1,1);//printMatrix(sh);cout<<endl;
	matrix<float> so=S(sh,w2,0);

	float e=error(so,output);

	if(e>=umbral){return false;}
	else{return true;}
}

void train(matrix_float data_input,matrix_float data_output,vector_float train,vector_float test){

	matrix<float> w1=createLayer(data_input[0].size()*2,data_input[0].size()+1);
	matrix<float> w2=createLayer(3,w1.size1()+1);
	matrix<float> input,output;

	for(int i=0;i<train.size();i++){
		input=toMatrix(data_input[train[i]],1);
		output=toMatrix(data_output[train[i]],0);
		RedNeuronal(input,output,w1,w2);
		cout<<"Entrenamiento -> "<<i+1<<endl;
	}

	int cont=1,buenas=0,malas=0;

	for(int i=0;i<test.size();i++){
		input=toMatrix(data_input[test[i]],1);
		output=toMatrix(data_output[test[i]],0);
		if(testeo(w1,w2,input,output)){buenas++;}
		else{malas++;}
		if(cont==20){cout<<"Buenas: "<<buenas<<" Malas: "<<malas<<endl;cont=0;buenas=0;malas=0;}
		cont++;
	}
}

void leer_data(matrix_float &di, matrix_float &dout,vector_float &data_train,vector_float &data_test){

	ifstream file("data.in");
	char c;string p="";int cont=0;

	vector_float aux;
	vector_float set;set.push_back(1);set.push_back(0);set.push_back(0);
	vector_float ver;ver.push_back(0);ver.push_back(1);ver.push_back(0);
	vector_float vir;vir.push_back(0);vir.push_back(0);vir.push_back(1);

	int act=1;

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

void print_data(matrix_float di,matrix_float dout){
	for(int i=0;i<di.size();i++){
		for(int j=0;j<di[i].size();j++){
			cout<<di[i][j]<<" ";
		}
		cout<<"->"<<dout[i][0]<<" "<<dout[i][1]<<" "<<dout[i][2]<<endl;
	}
}

void print(vector_float a){
	for(int i=0;i<a.size();i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

int main(){
	srand(time(NULL));
	/*matrix<float> input(3,1);input(0,0)=1;input(1,0)=1;input(2,0)=1;
	matrix<float> output(2,1);output(0,0)=1;output(1,0)=1;
	RedNeuronal(input,output,4,3);*/
	matrix_float data_input;
	matrix_float data_out;
	vector_float data_test;
	vector_float data_train;
	leer_data(data_input,data_out,data_train,data_test);
	train(data_input,data_out,data_train,data_test);
	//print_data(data_input,data_out);
	//print(data_train);print(data_test);
	return 0;
}
