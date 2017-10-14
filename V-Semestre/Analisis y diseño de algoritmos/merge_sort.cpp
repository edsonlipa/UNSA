#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
using namespace std;
typedef vector<int> vec;
void print_vector(vec v)
{
    cout << "[";for(auto i:v){
    cout <<i<< ",";}
    cout << "]\n";
}
void merge(vec &arr, int l, int m, int r,int &count)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
        count++;
        std::cout << "contando --------->"<< count << '\n';
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    std::cout << "se hizo merge "<< i<<" "<<j<<""<< k<< '\n';

}
void write_file(vec arr){
  ofstream myfile;
  myfile.open("data_merge.dat");
  for (auto i:arr) {
    myfile<<i<<'\n';
  }
  myfile.close();
}
void mergeSort(vec &arr, int l, int r,int &count)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        // std::cout << "l: "<<l << '\n';
        // std::cout << "m: "<<m << '\n';
        // std::cout << "r: "<<r << '\n';
        int count1=0;
        int count2=0;
        mergeSort(arr, l, m,count1);
        std::cout << "contador1 "<<count << '\n';
        mergeSort(arr, m+1, r,count2);
        std::cout << "contador2 "<<count << '\n';
        count+=count1+count2;
        merge(arr, l, m, r,count);
        // write_file(arr);
        print_vector(arr);
        // system("gnuplot plotmerge.gnp");
    }
}

int main()
{
    vec arr{38,27,43,3,9,11,10,20};
    int arr_size = arr.size();

    printf("Given array is \n");
    print_vector(arr);
    int contador=0;
    mergeSort(arr, 0, arr_size - 1,contador);
    std::cout << "contador final"<<contador << '\n';
    printf("\nSorted array is \n");
    print_vector(arr);
    return 0;
}
