#include <unistd.h>
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
row subtabsBetRow(row fila1,row fila2) //fila 1 menos la fila2
{
  row ans(fila1.size());
  for (unsigned i = 0; i < fila1.size(); ++i)
	{
		ans[i]=abs(fila1[i]-fila2[i]);
	}
  return ans;
}
row subtBetweenRow(row fila1,row fila2) //fila 1 menos la fila2
{
  row ans(fila1.size());
  for (unsigned i = 0; i < fila1.size(); ++i)
	{
		ans[i]=fila1[i]-fila2[i];
	}
  return ans;
}
bool operator <(row a,numero n)
{
  for (auto i:a) {
    if(i<n)return true;
  }
  return false;
}
bool minthat(row a,row ant,numero n)
{
  row subs=subtabsBetRow(a,ant);
	numero sum=0;
	for (auto i:subs) {
		sum+=pow(i,2);
	}
	if(sum>n)return false;
  return true;
}

bool strictlyDominatDiag(matrix matriz)
{
	for (int i = 0; i < matriz.size(); ++i)//fila
	{
		numero filas=0;
		numero columnas=0;

		for (int j = 0; j < matriz.size(); ++j)
		{
			filas+=abs(matriz[i][j]);
			columnas+=abs(matriz[j][i]);
		}
		if (abs(matriz[i][i])<=filas-abs(matriz[i][i])&&abs(matriz[i][i])<=columnas-abs(matriz[i][i]))
		{
			return false;
		}
	}
	return true;
}
int main(int argc, char const *argv[]) {
  // matrix sis_ecu(3,row (4));
  matrix sis_ecu{{13,4,-1,1},{2,-9,1,-3},{1,2,-13,-1},{-3,1,1,7}};
  colmnMatrix b{17,-9,-11,6};
	// matrix A{{13,4,-1,1},{2,-9,1,-3},{1,2,-13,-1},{-3,1,1,7}};
	// colmnMatrix B{17,-9,-11,6};

  if (strictlyDominatDiag(sis_ecu)) {
    std::cout << "es estrictamtnete dominadte" << '\n';
  }
  colmnMatrix ans_ant(3);
  colmnMatrix ansXYZ(3);
  colmnMatrix temp(3);
  for (size_t i = 0; i < 3; i++) {
    numero subs=0;
    for (size_t j = 0; j < 3; j++) {
      if (i!=j) {
        subs-=sis_ecu[i][j]*ansXYZ[j];
      }
    }
		// temp[i]=(b[i]+subs)/sis_ecu[i][i];
    ansXYZ[i]=(b[i]+subs)/sis_ecu[i][i];

		// print(temp);
  }
  // ansXYZ=temp;
  print(ansXYZ);

  while (!minthat(ans_ant,ansXYZ,pow(10,-2))) {
    ans_ant=ansXYZ;
    for (size_t i = 0; i < 3; i++) {
      numero subs=0;
      for (size_t j = 0; j < 3; j++) {
        if (i!=j) {
          subs-=sis_ecu[i][j]*ansXYZ[j];
        }
      }
      // temp[i]=(b[i]+subs)/sis_ecu[i][i];
			ansXYZ[i]=(b[i]+subs)/sis_ecu[i][i];
    }
    // ansXYZ=temp;
    print(ansXYZ);
    // sleep(3);
  }

  return 0;
}
