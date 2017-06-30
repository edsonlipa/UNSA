#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "CImg.h"

using namespace cimg_library;
using namespace std;
typedef std::vector<float> vecf;
typedef std::vector<vecf> matrix;
typedef std::vector<string> vecs;


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
int main()
{
    fstream file1("nametiff.name");
    string name="";
    while(!file1.eof())
    {
        getline(file1,name);
        if (name!="") {
          std::cout <<"leendo "<< name << '\n';
          string filename ="jaffejpg/"+name;
          CImg<float>   A((char*)filename.c_str());
          // A.display();
          CImg<float>   B =  A.haar(false,4);
          //  B.display();
          CImg<float>   C =  B.crop(0,0,15,15);
          //  C.display();
          // ofstream file("db.txt");
          // file<<(char*)filename.c_str()<<endl;
          std::cout <<C.max()<< " " <<C.min()<<" "<< C.mean()<<" "<<C.median()<<" "<<C.variance()<< '\n';
        }

    }


  //  cimg_forXY(C,x,y)
  //     file<<C(x,y)<<"--- ";
  //  file<<endl;

   return 1;
}
