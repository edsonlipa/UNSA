#include <iostream>
#include <vector>
using namespace std;
void ejercicio1(/* arguments */) {
  float real;
  std::cout << "ingrese un numero real" << '\n';
  std::cin >> real;
  std::cout << "el numero contiene horas:minutos:segundos:decimas de segundos " << '\n';
  std::cout << real<<':'<<real*60<<':'<<real*60*60<<':'<<real*60*60*10 << '\n';
  // std::cout << real*60<<':'<<real*60*60<<':'<<real*60*60*60<<':'<<real*60*60*60*10 << '\n';
}

void ejercicio2(/* arguments */) {
  float tam;
  std::cout << "the size is(Kb):" << '\n';
  std::cin >> tam;
  int pagesize = 10*300;
  std::cout << "the size of page(byts) is: "<<pagesize << '\n';
  int byts=tam*1024;
  std::cout << "the size on (byts) is: "<<byts << '\n';
  std::cout << "is posibel save "<< byts/pagesize <<"in this memory space" << '\n';

}
void ejercicio3()
{
  float monto;
  std::cout << "ingrese el monto :" << '\n';
  std::cin >> monto;
  int monto_entero=(int)monto;
  float monto_decimal=monto-monto_entero;
  int billetes[4]={20,10,5,1};
  float monedas[4]={0.5,0.20,0.10,0.05};
  for (size_t i = 0; i < 4; i++) {
    std::cout <<monto_entero/billetes[i]<< " billetes de " <<billetes[i] << '\n';
    monto_entero=monto_entero-((monto_entero/billetes[i])*billetes[i]);
  }
  std::cout << "lkhdlk " <<monto_decimal<< '\n';
  for (size_t i = 0; i < 4; i++) {
    std::cout <<monto_decimal/monedas[i]<< " monedas de " <<monedas[i] << '\n';
    monto_decimal=monto_decimal-((monto_decimal/monedas[i])*monedas[i]);
  }
}
void ejercicio4() {
  float saldo=20;
  std::cout << "ingrese el capital existente :" << '\n';
  std::cin >> saldo;
  float prestamo=0;
  if (saldo<=0) {
    std::cout << "su capital es :"<<saldo << '\n';
    prestamo=(saldo-10000)*(-1);
    saldo=10000;
    std::cout << "el saldo prestado es :"<<prestamo << '\n';
    std::cout << "su capital ahora es :"<<saldo<< '\n';
  }
  else if(saldo>0){
    std::cout << "su capital es :"<<saldo << '\n';
    prestamo=10000-saldo;
    saldo=20000;
    std::cout << "el saldo prestado es :"<<prestamo << '\n';
    std::cout << "su capital ahora es :"<<saldo<< '\n';
  }
  else if(saldo>20000){
    std::cout << "su capital es :"<<saldo << '\n';
    prestamo=0;
    std::cout << "el saldo prestado es :"<<prestamo << '\n';
  }
  saldo-=7000;
  std::cout << "se utiliza 5000 en equipo de computo" << '\n';
  std::cout << "se utiliza 2000 en equipo de computo" << '\n';
  std::cout << "se utiliza "<<saldo/2<<" en equipo de computo" << '\n';
  std::cout << "se utiliza "<<saldo/2<<" en equipo de computo" << '\n';


}
int main(int argc, char const *argv[]) {
  // std::cout << "ejercicio1" << '\n';
  // ejercicio1();
  // std::cout << "ejercicio2" << '\n';
  // ejercicio2();
  // std::cout << "ejercicio3" << '\n';
  // ejercicio3();
  std::cout << "ejercicio4" << '\n';
  ejercicio4();
  return 0;
}
