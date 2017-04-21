#include <iostream>
#include <cmath>

using namespace std;
typedef long double number;

number ErrorAbsoluto(number r_ant,number r)
{
	return abs(r_ant-r)/abs(r);
}

number gfuncion1(number x){
	return 2*x-pow(x,2)+3;
}
number MetodoPuntoFijo(number r,number (*fx)(number),number presicion,number n){
  number r_ant= 0;
  number i = 0;
	do{
		r_ant = r;
		r = gfuncion1(r_ant);
		cout<<i<<"\t"<<r<<endl;
		i++;
	}while((ErrorAbsoluto(r_ant,r) > presicion and i != n) or i == 1);
	cout<<"\"Resultado Final\","<<endl;
}

int main(){
  MetodoPuntoFijo(1,&gfuncion1,pow(10,-5),100);
}
