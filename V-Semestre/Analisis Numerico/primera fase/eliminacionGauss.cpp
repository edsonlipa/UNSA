#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cmath>
using namespace std;
typedef float numero;
typedef vector<numero> row;
typedef vector<numero> colmnMatrix;
typedef vector<row> matrix;
void llenar_matriz(matrix &matriz1)
{	unsigned nM;
	numero valor;
	cout<<"zise of matrix"<<endl;
	cin>>nM;
	for (unsigned i = 0; i < nM; ++i)
	{
		row fila;
		cout<<"los valores se ingresaran por filas"<<endl;
		for (unsigned j = 0; j < nM; ++j)
		{
			cout<<"ingrese el valor: "<<endl;
			cin>>valor;
			fila.push_back(valor);
			cout<<"el valor fue ingresado en la posicion ["<<i+1<<"]["<<j+1<<"]"<<endl;
		}
		matriz1.push_back(fila);
	}
}
void print(matrix &m)
{
	unsigned nM=m.size();
	for (unsigned i = 0; i < nM; ++i)
	{
		for (unsigned j = 0; j < m[i].size(); ++j)
		{
			if(j==0){cout<<"|";}
			if(j!=0){cout<<"\t";}
			cout<<m[i][j];
		}
		cout<<"|"<<endl;
	}
	cout<<endl;
}
void print(row &m)
{
	unsigned nM=m.size();
	for (unsigned j = 0; j < nM; ++j)
	{
		cout<<"|";
		cout<<m[j];
		cout<<"|"<<endl;
	}

	cout<<endl;
}
void multbyRow(row &fila,numero n)
{
//	cout<<"multiplico"<<endl;
	for (unsigned i = 0; i < fila.size(); ++i)
	{
		fila[i]=fila[i]*n;
	}
}
void subtBetweenRow(row &fila1,row fila2) //fila 1 menos la fila2
{
	for (unsigned i = 0; i < fila1.size(); ++i)
	{
		fila1[i]=fila1[i]-fila2[i];
	}
}
row multMatrxandRow(matrix &p,row &b)
{	row pb(p.size());
    float aux=0;
    for(unsigned int i=0; i<p.size(); i++)
    {
        for (unsigned int j=0; j<p.size(); j++)
        {
            aux=aux+p[i][j]*b[j];
        }
        pb[i]=aux;
        aux=0;
    }
    return pb;

}
void sumBetweenRow(row &fila1,row fila2) //fila 1 mas la fila2
{
  for (unsigned i = 0; i < fila1.size(); ++i)
  {
    fila1[i]=fila1[i]+fila2[i];
  }
}
row multandsubt(row fila1,row fila2,numero mult) //fila 1 menos la fila2
{
	row newrow(fila1.size());
	for (unsigned i = 0; i < fila1.size(); ++i)
	{
		newrow[i]=fila1[i]-(fila2[i]*mult);
		//cout<<" "<<newrow[i];
	}
		//cout<<endl;
	return newrow;
}


void maxibyColmns(matrix &matriz,unsigned columna,matrix &L)
{	//cout<<"__________________________________________________________________"<<endl;
	//cout<<"maximo por columan cambiar pivote"<<endl;
	unsigned aux;
	unsigned aux2;
	priority_queue<float> maxheap;
	for (unsigned i = columna; i < matriz.size(); ++i)
	{
		maxheap.push(abs(matriz[i][columna]));
	}
	for (unsigned i = columna; i < matriz.size(); ++i)
	{
		if(abs(matriz[i][columna])==maxheap.top()) aux=i;
	}
	if (abs(matriz[columna][columna])==abs(matriz[aux][columna])){
		return;
	}
	else
	{
		matriz[columna].swap(matriz[aux]);

		L[columna].swap(L[aux]);
	}
}
void upperTriangle(matrix &matriz,matrix &L)
{	//cout<<"triangulo inferior"<<endl;
	numero multip=0;
	for (unsigned i = 0; i < matriz.size(); ++i)//columan
	{
		print(matriz);
    maxibyColmns(matriz,i,L);
    for (unsigned j = i+1; j < matriz[i].size()-1; ++j)//fila
		{
			if(matriz[j][i]!=0)
			{
			multip=(matriz[j][i]/matriz[i][i]);
			L[j][i]=multip;
			//cout<<"multip"<<multip<<endl;
			matriz[j]=multandsubt(matriz[j],matriz[i],multip);
			//multbyRow(matriz[j],multip);
			//subtBetweenRow(matriz[j],matriz[i]);

			}
		}
	}
}
row sustitucion_progresiva(matrix &l,row &b)
{

    row y(b.size());
    float aux=0;

    for(unsigned int i=0; i<l.size(); i++)
    {
        for (unsigned int j=0; j<l.size(); j++)
        {
            if(j<i)
                aux=aux+l[i][j]*y[j];
        }
        y[i]=(b[i]-aux)/l[i][i];
        aux=0;

    }
    return y;
}
row resolver_gauss(matrix &u)
{
	  row x(u.size());
    int y=u[0].size()-1;
    float aux=0;

    for(unsigned int i=u.size(); i>0; i--)
    {
        for (unsigned int j=u.size(); j>0; j--)
        {
            if(j-1>i-1)
                aux=aux+u[i-1][j-1]*x[j-1];
        }
        x[i-1]=(u[i-1][y]-aux)/u[i-1][i-1];
        aux=0;
    }
    return x;
}
int main(int argc, char const *argv[]) {
  // matrix sis_ecu(3,row (4));
  matrix sis_ecu{{1,-2,0.5,-5},{-2,5,-1.5,0},{-0.2,1.75,-1,10}};
  matrix L(sis_ecu.size(),row(sis_ecu.size()-1));
  upperTriangle(sis_ecu,L);
  row Y=resolver_gauss(sis_ecu);
  print(sis_ecu);
  print(Y);
  return 0;
}
