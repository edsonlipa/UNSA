#include <iostream>
#include <cmath>
#include <algorithm>  
#include <vector>
#include <queue>

using namespace std;

bool descendente (int i,int j) { return (i>j); }

vector<int> querys;

void scan(vector<int> querys,int init,int prev,int &time){
    if(init>prev&&init!=199||init==0){//acendente ->
        //cout<<"acendente"<<endl;
        sort(querys.begin(),querys.end());
        int inicio=-1;
        int size=querys.size();
        for(int i=0;i<size;i++){
            
            if(init<=querys[i]){
            if(inicio==-1)inicio=i;
            prev=init;
            init=querys[i];
            time+=abs(prev-init);
            cout<<" "<<querys[i]<<endl;
            }
        }
        querys.erase(querys.begin()+inicio,querys.end());
        if(querys.empty()) {return;}
    
           prev=init;
            init=199;       
            time+=abs(prev-init);
            cout<<" "<<199<<endl;
    
    }else if(init<prev&&init!=0||init==199){
        //cout<<"decendente"<<endl;
                
        sort(querys.begin(),querys.end(),descendente);
        int size=querys.size();
        int inicio=-1;
        //cout<<"size "<<size<<   endl;
        for(int i=0;i<size;i++){
            //cout<<"init "<<init<<" i "<<querys[i]<<   endl;
            
            if(init>=querys[i]){
            if(inicio==-1)inicio=i;
            prev=init;
            init=querys[i];
            time+=abs(prev-init);
            cout<<" "<<querys[i]<<endl;
        
            }
            
        }
        
        querys.erase(querys.begin()+inicio,querys.end());
        if(querys.empty()) {return;}
        
            prev=init;
            init=0; 
            time+=abs(prev-init);
            cout<<" "<<0<<endl;
            

        }
        
    scan(querys, init, prev,time);
}

void cscan(vector<int> querys,int init,int prev,int &time){
    if(init>prev&&init!=199||init==0){//acendente ->
        //cout<<"acendente"<<endl;
        if(querys.empty()) {return;}
    
           prev=init;
            init=199;       
            time+=abs(prev-init);
            cout<<" "<<199<<endl;
    
    }else if(init<prev&&init!=0||init==199){
        //cout<<"decendente"<<endl;
                
        sort(querys.begin(),querys.end(),descendente);
        int size=querys.size();
        int inicio=-1;
        //cout<<"size "<<size<<   endl;
        for(int i=0;i<size;i++){
            //cout<<"init "<<init<<" i "<<querys[i]<<   endl;
            
            if(init>=querys[i]){
            if(inicio==-1)inicio=i;
            prev=init;
            init=querys[i];
            time+=abs(prev-init);
            cout<<" "<<querys[i]<<endl;
        
            }
            
        }
        
        querys.erase(querys.begin()+inicio,querys.end());
        if(querys.empty()) {return;}
        
            prev=init;
            init=0; 
            time+=abs(prev-init);
            cout<<" "<<0<<endl;
            

        }
        
    cscan(querys, init, prev,time);
}


int main (){
    int n_querys,new_query;
    int time=0;
    int time1=0;
    cin >> n_querys;
    for(size_t i=0 ; i<n_querys; i++){
        cin>>new_query;
        querys.push_back(new_query);
    }

    scan(querys,53,80,time);
    cout<<time<<endl;
    cout<<endl;
    cscan(querys,53,80,time1);
    cout<<time1<<endl;
    return 0;   
}