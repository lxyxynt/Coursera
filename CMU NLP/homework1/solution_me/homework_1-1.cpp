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
using namespace std;

typedef long long ll;
const double pi = acos(-1.0);
const double eps = 1e-8;

const int dx[8]={1,0,-1,0,-1,-1,1,1};
const int dy[8]={0,1,0,-1,1,-1,1,-1};
const int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
const int leap[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};

map<string,double> T;
map<string,pair<double,string> > M;

int main(){
    T.clear();M.clear();
    T["O"]=345128;
    T["I-GENE"]=41072;
    ifstream fin1("gene.counts");
    ifstream fin2("gene.test");
    freopen("gene_test.p1.out","w",stdout);
    
    string s1,s2,s3,s4,s5;
    double k;
    while (fin1 >> k >> s3){
        if (s3[0]=='W'){ 
            fin1 >> s1 >> s2;
            pair<double,string> ret;
            ret.first=k/T[s1];
            ret.second=s1;
            if (M.find(s2)==M.end() || M[s2]<ret) M[s2]=ret;
        }
        if (s3[0]=='1'){ 
            fin1 >> s1;
            T[s1]=k;
        }
        if (s3[0]=='2') fin1 >> s1 >> s1;
        if (s3[0]=='3') fin1 >> s1 >> s1 >> s1;
    }
    
    while (getline(fin2,s1)){
        if (s1.size()==0){ 
            printf("\n");
            continue;
        }
        if (M.find(s1)==M.end()) s2="_RARE_";
        else s2=s1;
        printf("%s %s\n",s1.c_str(),M[s2].second.c_str());
    }
    return 0;
}
