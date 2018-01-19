#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "rangue_t.h"

#define n_pts 10000000
#define x_limit 100
#define y_limit 100

using namespace std;


bool compare (point<int> *i,point<int> *j){
    return i->first<j->first;
}

int main()
{
    srand(time(NULL));

    vector<point<int> *> in_xs(n_pts);
    vector<point<int> *> in_ys(n_pts);
    for(int i=0;i<n_pts;i++){

        in_xs[i]=new point<int> (i+1,nullptr);
        in_ys[i]=new point<int> (i+1,in_xs[i]);
        in_xs[i]->pointer=in_ys[i];
    }

    sort(in_xs.begin(),in_xs.end(),compare);
    sort(in_ys.begin(),in_ys.end(),compare);



    L_Range_T<int> LRT2D;
    cout << " init build tree   " << endl;

    LRT2D.Build_2D_RT(in_xs,in_ys);
    cout << " tree filalized   " << endl;
    // LRT2D.print();
    LRT2D.Query(1,7,3,7);
    return 0;
}
