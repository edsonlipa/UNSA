#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void ingresar_polinomios(vector<vector<float>> &m,vector<float> &res,string &exe){
    int np;
    float const1;
    vector<float> row;
    cout<<"numero de polinomios -> ";
    cin>>np;
    for(int i=0;i<np;i++){
        exe+=",\t ";
        cout<<endl<<"ingrese el polinomio "<<i+1<<" -> ";
        for(int j=0;j<np;j++){
            cout<<endl<<"ingrese la constante "<<j+1<<" -> ";
            cin>>const1;
            row.push_back(const1);
        }
        m.push_back(row);
        cout<<endl<<"ingrese el resultado del polinomio -> ";
        cin>>const1;
        res.push_back(const1);
        row.clear();

    }
}

void mostrar(vector<float> m){
    for(int i=0;i<m.size();i++){
        cout<<m[i]<<" ";

    }
}
void mostrar(vector<vector<float>> m,vector<float>resultado){
    for(int i=0;i<m.size();i++){
        mostrar(m[i]);
        cout<<"= "<<resultado[i];
        cout<<endl;
    }
}
void get_var(vector<float> &var,int tam){
    float X;
    for(int i=0;i<tam;i++){
        cout<<endl<<"ingrese el valor de la variable"<<i+1<<" -> ";
        cin>>X;
        var.push_back(X);
    }
}

int main()
{
    ofstream archivo("gauss.csv");
    string exe="\"i\"";
    //archivo<<i<<","<<a<<","<<fa<<","<<r<<","<<fda<<endl;
    vector<float> var;
    vector<vector<float>> matriz;
    vector<float> resultado;
    ingresar_polinomios(matriz,resultado,exe);
    archivo<<exe<<endl;
    mostrar(matriz,resultado);
    get_var(var,matriz.size());
    for(int k=0;k<3;k++){
    archivo<<k;
        for(int i=0;i<var.size();i++){
        archivo<<","<<var[i];
        }
        for(int i=0;i<var.size();i++){
        float tmp=resultado[i];
        for(int j=0;j<var.size();j++){

            if(i!=j){
                tmp+=matriz[i][j]*var[j];
            }
        }
        var[i]=tmp/matriz[i][i];
    }
    archivo<<endl;
}

    cout<<"archivo guardado con exito";
    archivo.close();

    return 0;
}
