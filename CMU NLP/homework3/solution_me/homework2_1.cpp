#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <string.h>
#include <queue>
#include <map>
#include <set>
#include <math.h>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

typedef long long ll;
const double pi = acos(-1.0);
const double eps = 1e-8;

const int dx[8]={1,0,-1,0,-1,-1,1,1};
const int dy[8]={0,1,0,-1,1,-1,1,-1};
const int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
const int leap[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
struct node{
    int a,b,c,d;
    node(){}
    node(int q,int w,int e):a(q),b(w),c(e){}
    bool operator <(const node&n)const{
        if (a<n.a) return true;
        if (a>n.a) return false;        
        if (b<n.b) return true;
        if (b>n.b) return false;        
        if (c<n.c) return true;
        return false;                                
    }
    bool operator ==(const node&n)const{
        return (a==n.a && b==n.b && c==n.c);
    }
};
map<string,map<string,double> > t;
map<pair<int,node>,double> Q;

int main(){
    t.clear();
    string s1,s2,s3;
    int p1,p2,p3,p4;
    double k;
    ifstream tin("alignment_t.in");
    while (tin>>s1>>s2>>k) t[s1][s2]=k;
    tin.close();
    ifstream qin("alignment_q.in");
    while (qin>>p1>>p2>>p3>>p4>>k) Q[make_pair(p1,node(p2,p3,p4))]=k;
    qin.close();
    
    ifstream fin1("test.en");
    ifstream fin2("test.es");
    freopen("alignment_test.p2.out","w",stdout);
    vector<string> v1,v2;    
    int cas=0;
    while (getline(fin1,s1) && getline(fin2,s2)){
//        system("pause");
        ++cas;
        v1.clear();
        istringstream sin1(s1);
        while (sin1>>s3) v1.push_back(s3);
        v1.push_back("NULL");
        
        v2.clear();
        istringstream sin2(s2);
        while (sin2>>s3) v2.push_back(s3);
        
        for (int j=0;j<v2.size();++j){
            int ret=v1.size()-1;
            for (int i=0;i+1<v1.size();++i){
                if (t.find(v1[i])==t.end() || t[v1[i]].find(v2[j])==t[v1[i]].end()) continue;
                pair<int,node> g=make_pair(i,node(j,v1.size(),v2.size()+1));
                if (Q.find(g)==Q.end()) continue;
                if (t[v1[i]][v2[j]]*Q[g]>t[v1[ret]][v2[j]]*Q[make_pair(ret,node(j,v1.size(),v2.size()+1))]) ret=i;
            }
            if (ret!=v1.size()-1) 
                printf("%d %d %d\n",cas,ret+1,j+1);
        }
    }
    return 0;
}
