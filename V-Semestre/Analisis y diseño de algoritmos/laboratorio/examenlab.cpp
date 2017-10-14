#include <iostream>
using namespace std;
int perf(int number,int i)
{
  if (i==number) {
    return 0;
  }
  if(number%i==0)
    return (i)+perf(number,i+1);
  return perf(number,i+1);
}
void list_perf(int start,int end){
  if(start==end)return;
  // std::cout << (start==perf(start)?" es perfecto":" no es perfecto") << '\n';
  if (start==perf(start,1)) {
    std::cout <<start<< " es perfecto " << '\n';
  }
  list_perf(start+1,end);
}
int main(int argc, char const *argv[]) {
  /* code */
  // std::cout << "/* resultado de 28 */ " <<perf(28,1)<< '\n';
  list_perf(5,100000);
  return 0;
}
