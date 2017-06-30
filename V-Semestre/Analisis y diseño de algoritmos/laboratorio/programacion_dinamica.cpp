#include<iostream>
#include<vector>

using namespace std;
typedef vector<int> vec;

int fib(int n, vec &arr) {
  if (n<=1) {
    return 1;
  }else if (arr[n-1]==-1) {
    arr[n-1]=fib(n-1,arr);
  }else if (arr[n-2]==-1) {
    arr[n-2]=fib(n-2,arr);
  }
  arr[n]=arr[n-1]+arr[n-2];
  std::cout << "n: "<<n-1<<" "<<arr[n] << '\n';
  return arr[n];
}

int main(int argc, char const *argv[]) {
  vec arr(10,-1);

  std::cout << "n: "<<10<<" "<<fib(10 ,arr)<< '\n';
  cout<< '\n';
  for (auto i:arr ) {
    std::cout << "["<< i<<"]" ;
  }
  cout<< '\n';
  return 0;
}
