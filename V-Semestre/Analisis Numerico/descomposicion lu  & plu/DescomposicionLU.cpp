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
matrix L;
matrix U;
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
		for (unsigned j = 0; j < nM; ++j)
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
void sumBetweenMatrix(matrix &matriz1,matrix &matriz2)//matriz 1 mas matriz 2
{	//cout<<"suma de matrices"<<endl;
	unsigned count=matriz1.size();
	for (int i = 0; i < count; ++i)//columan 1
	{
		for (int j = 0; j < count; ++j)//row 2
		{
			matriz1[i][j]=matriz1[i][j]+matriz2[i][j];
		}
	}
}
void multBetweenMatrix(matrix &matriz1,matrix &matriz2)
{	//cout<<"producto"<<endl;
	unsigned count=matriz1.size();
	for (int i = 0; i < count; ++i)//columan 1
	{
		for (int j = 0; j < count; ++j)//row 2
		{
			numero ans=0;
			for (int k = 0; k < count; ++k) //iterator
			{
					ans+=matriz1[i][k]*matriz2[k][j];

			}
			if(j==0){cout<<"|";}
			if(j!=0){cout<<"\t";}
			cout<<ans;

		}
			cout<<"|"<<endl;
	}
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
  //cout<<"resta"<<endl;
  for (unsigned i = 0; i < fila1.size(); ++i)
  {
    fila1[i]=fila1[i]+fila2[i];
    //cout<<" pos: "<<i<<" new value: "<<fila1[i]<<" |";
  }
  //cout<<endl;
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

void llenar_Midentidad(matrix &matriz1,unsigned nM)
{
	for (unsigned i = 0; i < nM; ++i)
	{
		row fila;
		for (unsigned j = 0; j < nM; ++j)
		{
			if(i==j)			{
				fila.push_back(1);
			}
			else
			fila.push_back(0);
		}
		matriz1.push_back(fila);
	}
}

void maxibyColmns(matrix &matriz,unsigned columna,matrix &P,matrix &L)
{	//cout<<"__________________________________________________________________"<<endl;
	//cout<<"maximo por columan cambiar pivote"<<endl;
	unsigned aux;
	unsigned aux2;
	priority_queue<float> maxheap;
	for (unsigned i = columna; i < matriz.size(); ++i)
	{
		maxheap.push(matriz[i][columna]);
	}
	for (unsigned i = columna; i < matriz.size(); ++i)
	{
		if(matriz[i][columna]==maxheap.top()) aux=i;

	}
	if (matriz[columna][columna]==matriz[aux][columna]){
		return;
	}
	else
	{
	//	cout<<"el cambio se hiso entre "<<columna<<" y "<<aux<<endl;
		matriz[columna].swap(matriz[aux]);
		P[columna].swap(P[aux]);
		L[columna].swap(L[aux]);
	}
}
void upperTriangle(matrix &matriz,matrix &L)
{	//cout<<"triangulo inferior"<<endl;
	numero multip=0;
	for (unsigned i = 0; i < matriz.size(); ++i)//columan
	{
		//print(matriz);
		for (unsigned j = i+1; j < matriz.size(); ++j)//fila
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
row sustitucion_regresiva(matrix &u,row &y)
{
	row x(y.size());
    float aux=0;

    for(unsigned int i=u.size(); i>0; i--)
    {
        for (unsigned int j=u.size(); j>0; j--)
        {
            if(j-1>i-1)
                aux=aux+u[i-1][j-1]*x[j-1];
        }
        x[i-1]=(y[i-1]-aux)/u[i-1][i-1];
        aux=0;
    }
    return x;
}
void descomponer_enLU(matrix A,matrix &L,matrix &U) ///la descomposicion de A=L.U
{
	matrix ID;
	llenar_Midentidad(ID,A.size());
	//matrix A={{9,2,-3},{1,-4,2},{2,1,9}};
	U=A;
	upperTriangle(U,L);
	sumBetweenMatrix(L,ID);
	cout<<"matriz"<<endl;
	print(A);
	cout<<"---L---"<<endl;
	print(L);
	cout<<"---U---"<<endl;
	print(U);
	//cout<<((strictlyDominatDiag(A))?"es estrictamente dominante":"no es estrictamtnete dominante")<<endl;

}
void resolver_conLU(matrix &A,row &B) {
	matrix U;
  matrix L(A.size(),row(A.size()));
	std::cout << "/*********** Importante: no todas las matrices tienen descompocicion LU ******************/" << '\n';
  descomponer_enLU(A,L,U);
  std::cout << "la ultipliacaion de las matrices L y U" << '\n';
  multBetweenMatrix(L,U);
	row Y(B.size()); // Vector Y Auxiliar donde se guarda la sustitucion progresiva
	row X(B.size()); //Vector de resultados
	Y=sustitucion_progresiva(L,B);
	X=sustitucion_regresiva(U,Y);
	std::cout << "la respuesta X es" << '\n';
	print(X);
}
int main(int argc, char const *argv[]) {
	matrix A{{3,-7,-2},{-3,5,1},{6,-4,0}};
  colmnMatrix B{-7,5,2};
	print(A);
	print(B);
	resolver_conLU(A,B);


  return 0;
}
