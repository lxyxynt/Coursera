#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <string.h>
#include <queue>
#include <map>
#include <set>
#include <math.h>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

typedef long long ll;
const double pi = acos(-1.0);
const double eps = 1e-8;

const int dx[8]={1,0,-1,0,-1,-1,1,1};
const int dy[8]={0,1,0,-1,1,-1,1,-1};
const int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
const int leap[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};

map<string,set<string> > M;
map<string,map<string,double> > t;
map<string,double> C1;
map<pair<string,string>,double> C2;

vector<vector<string> > en,es;

void readfile(){
    ifstream ein("corpus.en");
    ifstream fin("corpus.es");
    en.clear();es.clear();
    string s1,s2;    
    vector<string> ret;
    
    int sum1=0,sum2=0;
    while (getline(ein,s1)){
        ret.clear();
        istringstream sin(s1);
        while (sin>>s2) ret.push_back(s2);
        ret.push_back("NULL");
        en.push_back(ret);
        sum1+=ret.size();
    }
    while (getline(fin,s1)){
        ret.clear();
        istringstream sin(s1);
        while (sin>>s2) ret.push_back(s2);
        ret.push_back("NULL");        
        es.push_back(ret);
        sum2+=ret.size();
    }
    
    printf("en: %d\n",sum1);
    printf("es: %d\n",sum2);
    ein.close();fin.close();    
}

void init(){
    puts("init..");
    M.clear();    
    for (int i=0;i<en.size();++i){
        for (int k=0;k<en[i].size();++k)
            for (int j=0;j<es[i].size();++j) 
                M[en[i][k]].insert(es[i][j]);
        if (i%500==0) cout << i << "\n";                        
    }

    puts("init parameter..");
    for (map<string,set<string> >::iterator it=M.begin();it!=M.end();++it)
        for (set<string>::iterator it2=it->second.begin();it2!=it->second.end();++it2)
            t[it->first][(*it2)]=1.0/(it->second.size());
}

inline double cal(int p,int q,int k,double ret){
    if (ret>eps)     
        return t[en[p][k]][es[p][q]]/ret;
    return 0;
}

void process_E(){
    C1.clear();C2.clear();

    for (int k=0;k<en.size();++k){
        for (int i=0;i<es[k].size();++i){
            double ret = 0;
            
            for (int j=0;j<en[k].size();++j)
                if (t[en[k][j]].find(es[k][i])!=t[en[k][j]].end()) 
                    ret+=t[en[k][j]][es[k][i]];
            for (int j=0;j<en[k].size();++j){             
                pair<string,string> tmp = make_pair(es[k][i],en[k][j]);
                double add = cal(k,i,j,ret);
                if (add<eps) continue;
                C1[en[k][j]]+=add;
                C2[tmp]+=add;
            }
        }
        if (k%500==0) cout << k << "\n";        
    }
}

void process_M(){
    t.clear();
    for (map<pair<string,string>,double>::iterator it=C2.begin();it!=C2.end();++it)
        t[(it->first).second][(it->first).first]=(it->second/C1[(it->first).second]);
}

void EM(int _){
    while (_--){
        puts("start....");
        process_E();
        process_M();
        puts("finish.");
    }
}

void output(){
    freopen("alignment_t.in","w",stdout);
    for (map<string,map<string,double> >::iterator it=t.begin();it!=t.end();++it)
        for (map<string,double>::iterator it2=it->second.begin();it2!=it->second.end();++it2)
            printf("%s %s %.12f\n",it->first.c_str(),it2->first.c_str(),it2->second);
}

int main(){
    readfile();
    init();
    EM(5);
    output();
    return 0;
}
