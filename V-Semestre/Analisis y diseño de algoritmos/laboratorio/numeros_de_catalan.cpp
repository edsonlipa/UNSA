#include <iostream>
#include <cstdlib>

using namespace std;

unsigned int Catalan(int n)
{
    if (n <= 0)
        return 1;
    else
        return (2 * (2*n - 1) * Catalan(n - 1)) / (n + 1);
}

unsigned int fibonacci_recursivo(int n)
{
    if (n < 2)
				return n;
		else
        return fibonacci_recursivo(n-2) + fibonacci_recursivo(n-1);
}

long double factorial(int n)
{
    long double fact;
    if (n==0)
        return 1;
    else
         return n*factorial(n-1);
}

int Ackerman(int m, int n)
{
    if(m==0)
      return n+1;
    else
    { if(n==0)
         return Ackerman(m-1, 1);
      else
         return Ackerman(m-1, Ackerman(m, n-1));}
}
int hanoi(int n)
{
    if(n == 1)
        return 1;
    else
        return 2 * hanoi(n-1) + 1;
}
int main()
{
    int n ;
    cout << "\n Numeros de fibonaci \n\n";

    cout << "Ingrese numero: ";
    cin >> n;

    cout<<endl;
    std::cout << "/* fibonaci en la pocicion "<<n<<" : " << fibonacci_recursivo(n)<< '\n';
    cout<<endl;
    std::cout << "///////////////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    cout << "\n Numeros de catalan \n\n";

    cout << "Ingrese numero: ";
    cin >> n;
    cout<<endl;

    std::cout << "/* numero de catalan en la pocicion "<<n<<" : " << Catalan(n)<< '\n';
    cout<<endl;
    std::cout << "///////////////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    cout << "\n Factorial de un numero \n\n";

    cout << "Ingrese numero: ";
    cin >> n;
    cout<<endl;
    std::cout << "/* factorial de " << factorial(n)<< '\n';
    cout<<endl;
    std::cout << "///////////////////////////////////////////////////////////////////////////////////////////////////" << '\n';

    cout << "\n Función de Ackermann \n\n";
    cout << "para la funcion de ackermann se necesitan dos numeros"<<endl;
    cout << "Ingrese numero1: ";
    cin >> n;
    int m ;
    cout << "Ingrese numero2: ";
    cin >> m;
    cout<<endl;
    std::cout << "/* Función de Ackermann con "<<n<<" y "<<m<<" : "<< Ackerman(n,m)<< '\n';
    cout<<endl;
    std::cout << "///////////////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    cout << "\n Torres de hanoi \n\n";
    cout << "Ingrese numero de discos: ";
    cin >> n;
    cout<<endl;
    std::cout << "/* EL numero de movimientos necesarios  con "<<n<<" discos es: "<< hanoi(n)<< '\n';

    return 0;
}
