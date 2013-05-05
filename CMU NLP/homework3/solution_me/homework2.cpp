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
#include<ext/hash_map>
using namespace std;

typedef long long ll;
const double pi = acos(-1.0);
const double eps = 1e-12;

const int dx[8]={1,0,-1,0,-1,-1,1,1};
const int dy[8]={0,1,0,-1,1,-1,1,-1};
const int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
const int leap[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};

struct node{
    int a,b,c;
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
/*
using namespace __gnu_cxx;
struct orz_hash{
    size_t operator () (const node& a) const {
        unsigned int tmp = a.a;
        tmp = tmp*500009+a.b;
        tmp = tmp*500009+a.c;
        tmp = tmp*500009+a.d;
        return (size_t)(tmp);
    }
};
struct orz_compare{
    bool operator () (const pair<int,int>& a,const pair<int,int>& b) const {
        return a==b;
    }
};
hash_map<node ,double, orz_hash, orz_compare> Q;
*/
map<pair<int,node>,double> Q;
map<string,map<string,double> > t;
map<string,double> C1;
map<pair<string,string>,double> C2;

map<node,double> C3;
map<pair<int,node>,double> C4;
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
    ein.close();fin.close();    
}

void init(){
    puts("init parameter..");    
    Q.clear();
    for (int i=0;i<en.size();++i)
        for (int j=0;j<en[i].size();++j)
            for (int k=0;k<es[i].size();++k)
                Q[make_pair(j,node(k,en[i].size(),es[i].size()))]=1.0/(en[i].size());
    t.clear();
    string s1,s2,s3;
    double k;
    ifstream fin("alignment_t.in");
    while (fin>>s1>>s2>>k) t[s1][s2]=k;
    fin.close();
}

inline double cal(int k,int p,int q,int sp,int sq,double ret){
    double tmp=0;
    pair<int,node> g=make_pair(q,node(p,sq,sp));
    if (Q.find(g)!=Q.end()) tmp=Q[g];
    if (t[en[k][q]].find(es[k][p])!=t[en[k][q]].end()) tmp*=t[en[k][q]][es[k][p]];
    else tmp=0;
    
    if (ret>eps) return tmp/ret;
    return 0;
}

void process_E(){
    C1.clear();C2.clear();
    C3.clear();C4.clear();
    for (int k=0;k<en.size();++k){
        for (int i=0;i<es[k].size();++i){
            double ret = 0;
            
            for (int j=0;j<en[k].size();++j)
                if (t[en[k][j]].find(es[k][i])!=t[en[k][j]].end()) {
                    double tmp=0;
                    pair<int,node> g=make_pair(j,node(i,en[k].size(),es[k].size()));
                    if (Q.find(g)!=Q.end()) tmp=Q[g];
                    ret+=t[en[k][j]][es[k][i]]*tmp;
                }
            for (int j=0;j<en[k].size();++j){             
                pair<string,string> tmp = make_pair(es[k][i],en[k][j]);
                double add = cal(k,i,j,es[k].size(),en[k].size(),ret);
                if (add<eps) continue;
                C1[en[k][j]]+=add;
                C2[tmp]+=add;
                node g(i,en[k].size(),es[k].size());
                C3[g]+=add;
                C4[make_pair(j,g)]+=add;
            }
        }
        if (k%500==0) cout << k << "\n";        
    }
}

void process_M(){
    t.clear();
    for (map<pair<string,string>,double>::iterator it=C2.begin();it!=C2.end();++it)
        t[(it->first).second][(it->first).first]=(it->second/C1[(it->first).second]);
    Q.clear();
    for (map<pair<int,node>,double>::iterator it=C4.begin();it!=C4.end();++it)
        Q[it->first]=it->second/C3[it->first.second];
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
    freopen("alignment_q.in","w",stdout);
    for (map<pair<int,node>,double>::iterator it=Q.begin();it!=Q.end();++it)
        printf("%d %d %d %d %.12f\n",it->first.first,it->first.second.a,it->first.second.b,it->first.second.c,it->second);
}

int main(){
    readfile();
    init();
    EM(5);
    output();
    return 0;
}
