#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <fstream>
#include <stdlib.h>

using namespace std;

typedef long double number;
typedef vector<map<char,number>> lista;
typedef vector<pair<number,vector<number>>> funcion;

void llenarcoordenadas(lista &coordenadas)
{
	// coordenadas[0]['x']=0;
	// coordenadas[0]['y']=sin(0);
	//
	// coordenadas[1]['x']=0.3;
	// coordenadas[1]['y']=sin(0.3);
	//
	// coordenadas[2]['x']=0.6;
	// coordenadas[2]['y']=sin(0.6);
	//
	// coordenadas[3]['x']=0.9;
	// coordenadas[3]['y']=sin(0.9);
	//
	// coordenadas[4]['x']=1.2;
	// coordenadas[4]['y']=sin(1.2);
	//
	// coordenadas[5]['x']=1.5;
	// coordenadas[5]['y']=sin(1.2);
	//
		coordenadas[0]['x']=-2;
		coordenadas[0]['y']=1;

		coordenadas[1]['x']=-1;
		coordenadas[1]['y']=0;

		coordenadas[2]['x']=2;
		coordenadas[2]['y']=3;

		coordenadas[3]['x']=3;
		coordenadas[3]['y']=1;

		coordenadas[4]['x']=5;
		coordenadas[4]['y']=-1;


	cout<<"\tPuntos iniciales dados"<<endl;
 for (int i = 0; i < coordenadas.size(); ++i)
 {

 	cout<<"Punto "<<i<<" ("<<coordenadas[i]['x']<<","<<coordenadas[i]['y']<<")"<<endl;
 }
 cout<<endl;
}

void llenarcoordenadas(lista &coordenadas,float desde,float hasta,float inter)
{
	coordenadas[0]['x']=0;
	coordenadas[0]['y']=sin(0);
	int cont=0;
	for (float i = desde; i < hasta; i=i+inter) {

		coordenadas[cont]['x']=i;
		std::cout << "/* message */" <<i<< '\n';
		coordenadas[cont]['y']=sin(coordenadas[cont]['x']);
		cont++;
	}

	cout<<"\tPuntos iniciales dados"<<endl;
 for (int i = 0; i < coordenadas.size(); ++i)
 {

 	cout<<"Punto "<<i<<" ("<<coordenadas[i]['x']<<","<<coordenadas[i]['y']<<")"<<endl;
 }
 cout<<endl;
}
number Mlagramge(lista coordenadas,number x)
{
	number respuesta=0;
	for (int i = 0; i < coordenadas.size(); ++i)
	{	number Rparcial=1;


		//i iterador de multiplicaciones cordenada[i]['y']
		for (int j = 0; j < coordenadas.size(); ++j)
		{
			if (j!=i)
				///////////------------------------------------------
			{
				Rparcial*= (x-coordenadas[j]['x'])/(coordenadas[i]['x']-coordenadas[j]['x']);

			}
		}
		Rparcial=Rparcial*coordenadas[i]['y'];

		respuesta+=Rparcial;
	}
	return respuesta;
}

funcion Ilagramge_generate(lista coordenadas)
{
	funcion funciondeCoordenadas;
	for (int i = 0; i < coordenadas.size(); ++i)
	{
		number divicion=1;
		number coeficionete;
		vector<number> restas;
		restas.clear();
		for (int j = 0; j < coordenadas.size(); ++j)
		{
			if (j!=i)
			{
				restas.push_back(coordenadas[j]['x']);
				divicion*=(coordenadas[i]['x']-coordenadas[j]['x']);
			}
		}
		coeficionete=coordenadas[i]['y']/divicion;
		funciondeCoordenadas.push_back(make_pair(coeficionete,restas));
	}
	return funciondeCoordenadas;

}
void pinrtfunction(funcion fun)
{
	cout<<"\tPolinomio generado por el mateodo de la interpolacion de lagrange"<<endl;
	cout<<endl;
	for (int i = 0; i < fun.size(); ++i)
	{	cout<<to_string(fun[i].first)<<"*";
		for (int j = 0; j < fun[i].second.size(); ++j)
		{
			cout<<"(x-"<<to_string(fun[i].second[j])<<")";
		}
		if (i!=fun.size()-1)cout<<"+"<<endl;

	}
	cout<<endl;
	cout<<endl;
}
number evaluar(funcion funciondeCoordenadas,number x)
{
	number respuesta=0;
	for (int i = 0; i < funciondeCoordenadas.size(); ++i)
	{	number Rparcial=1;

		for (int j = 0; j < funciondeCoordenadas[i].second.size(); ++j)
		{
			Rparcial*= x-funciondeCoordenadas[i].second[j];
		}
		Rparcial=Rparcial*funciondeCoordenadas[i].first;

		respuesta+=Rparcial;
	}
	return respuesta;
}
void llenararchivo(funcion fun,number inicio,number final)
{
	ofstream archivo("interpolacion2.csv");
	for (number i = inicio; i < final; i+=0.1)
	{
		archivo<<i<<" "<<evaluar(fun,i)<<endl;
	}
	archivo.close();
}
int main(int argc, char** argv)
{
	funcion funciondeCoordenadas;

	// lista coordenadas(40);
	lista coordenadas(5);
	llenarcoordenadas(coordenadas);
	// llenarcoordenadas(coordenadas,0,20,0.5);
	funciondeCoordenadas=Ilagramge_generate(coordenadas);
	pinrtfunction(funciondeCoordenadas);

	// llenararchivo(funciondeCoordenadas,-5,30);
	return 0;
}
