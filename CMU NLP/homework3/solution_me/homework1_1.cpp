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

map<string,map<string,double> > t;

int main(){
    t.clear();
    freopen("alignment_t.in","r",stdin);
    string s1,s2,s3;
    double k;
    while (cin>>s1>>s2>>k) t[s1][s2]=k;
    
    ifstream fin1("test.en");
    ifstream fin2("test.es");
    freopen("alignment_test.p1.out","w",stdout);
    vector<string> v1;    
    int cas=0;
    while (getline(fin1,s1) && getline(fin2,s2)){
        ++cas;
        v1.clear();
        v1.push_back("NULL");
        istringstream sin1(s1);
        while (sin1>>s3) v1.push_back(s3);
        
        istringstream sin2(s2);
        int cas2=0;
        while (sin2>>s3){ 
            int ret=0;
            for (int i=1;i<v1.size();++i){
                if (t.find(v1[i])==t.end() || t[v1[i]].find(s3)==t[v1[i]].end())
                    continue;
                if (t[v1[i]][s3]>t[v1[ret]][s3]) ret=i;
            }
            if (ret) printf("%d %d %d\n",cas,ret,++cas2);
        }
    }
    return 0;
}
