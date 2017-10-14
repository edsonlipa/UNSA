#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

typedef vector<int> vec;

int getMax(vec A, int n)
{
    int max = A[0];
    for (int i = 1; i < n; i++)
        if (A[i] > max)
            max = A[i];
    return max;
}
/*
 * count sort of A[]
 */
void countSort(vec &A, int n, int exp)
{
    int output[n];
    int i, count[10] = {0};
    for (i = 0; i < n; i++)
        count[(A[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(A[i] / exp) % 10] - 1] = A[i];
        count[(A[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++)
        A[i] = output[i];
}
/*
 * sorts A[] of size n using Radix Sort
 */
void radixsort(vec &A, int n)
{
    int m = getMax(A, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(A, n, exp);
}

/*
 * Main
 */
int main()
{
    vec A = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = A.size();
    radixsort(A, n);
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    std::cout  << '\n';
    return 0;
}
