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
const double CLS = -1e100;

const int dx[8]={1,0,-1,0,-1,-1,1,1};
const int dy[8]={0,1,0,-1,1,-1,1,-1};
const int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
const int leap[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};

const string Tag[2] = {"O","I-GENE"};

map<string,int> ID;
map<string,double> M[4];
double UniM[2],BiM[4][4],TriM[4][4][4];

double f[1000][4][4];
int path[1000][4][4];
set<string> S;

vector<string> V,P;

bool NU(string s){
    bool bi1=false;
    for (int i=0;i<s.size();++i)
        if (s[i]>='0' && s[i]<='9') bi1=true;
    return bi1;
}

bool AC(string s){
    for (int i=0;i<s.size();++i)
        if (s[i]<'A' || s[i]>'Z') return false;
    return true;
}

bool LC(string s){
    return (s[s.size()-1]>='A' && s[s.size()-1]<='Z');
}

string Ch(string s){
    if (NU(s)) return "__Numeric";
    if (AC(s)) return "__All_Capitals";
    if (LC(s)) return "__Last_Capital";
    return "__Rare";
}

double g(double k){
    return log(k);
}

double cal(int p,string s){
    if (M[p].find(s)==M[p].end()) 
        return M[p][Ch(s)];
    else 
        return M[p][s];
}

void work(){
    int n = V.size();
    for (int i=0;i<=n;++i)
        for (int j=0;j<4;++j)
            for (int k=0;k<4;++k){
                f[i][j][k]=CLS;
                path[i][j][k]=-1;
            }
    f[0][2][2]=0;
    for (int i=0;i<n;++i)
        for (int j=0;j<3;++j)
            for (int k=0;k<3;++k)
                if (f[i][j][k]>CLS)
                    for (int p=0;p<3;++p)
                        if (f[i+1][k][p]<f[i][j][k]+TriM[j][k][p]+cal(p,V[i])){
                            f[i+1][k][p]=f[i][j][k]+TriM[j][k][p]+cal(p,V[i]);
                            path[i+1][k][p]=j;
                        }
    double ans=CLS;
    int a1=0,a2=0;
    for (int i=0;i<3;++i)
        for (int j=0;j<3;++j)
            if (f[n][i][j]+TriM[i][j][3]>ans){
                ans=f[n][i][j]+TriM[i][j][3];
                a1=i;a2=j;
            }
    P.clear();
    for (int i=n;i>0;--i){
        P.push_back(Tag[a2]);
        int t=path[i][a1][a2];
        a2=a1;a1=t;
    }
    for (int i=0;i<n;++i) printf("%s %s\n",V[i].c_str(),P[n-i-1].c_str());
    puts("");
    V.clear();
//    system("pause");
}

int main(){
    M[0].clear();M[1].clear();M[2].clear();M[3].clear();
    ID.clear();ID[Tag[0]]=0; ID[Tag[1]]=1;ID["*"]=2; ID["STOP"]=3;
    ifstream fin1("gene.counts");
    ifstream fin2("gene.test");
    freopen("gene_test.p3.out","w",stdout);
    
    memset(UniM,0,sizeof(UniM));
    memset(BiM,0,sizeof(BiM));
    
    for (int i=0;i<4;++i)
        for (int j=0;j<4;++j)
            for (int k=0;k<4;++k)
                TriM[i][j][k]=CLS;
          
    string s1,s2,s3,s4,s5;
    double k;
    int id1,id2,id3;
    UniM[0]=345128;UniM[1]=41072;
    int num=0;
    S.clear();

    while (fin1 >> k >> s5){
        if (s5[0]=='W'){ 
            fin1 >> s1 >> s2;
            id1=ID[s1];
            M[id1][s2]=g(k/UniM[id1]);
            S.insert(s2);
        }
        if (s5[0]=='1'){ 
            fin1 >> s1;
        }
        if (s5[0]=='2'){ 
            fin1 >> s1 >> s2;
            id1=ID[s1];id2=ID[s2];
            BiM[id1][id2]=k;
        }
        if (s5[0]=='3'){ 
            fin1 >> s1 >> s2 >> s3;
            id1=ID[s1];id2=ID[s2];id3=ID[s3];
            TriM[id1][id2][id3]=g(k/BiM[id1][id2]);
//            printf("%d %d %d: %.4f\n",id1,id2,id3,TriM[id1][id2][id3]);
        }
    }
    V.clear();

    for (set<string>::iterator it=S.begin();it!=S.end();++it){
        if (M[0].find(*it)==M[0].end()) M[0][*it]=CLS;
        if (M[1].find(*it)==M[1].end()) M[1][*it]=CLS;        
    }

    while (getline(fin2,s1)){
        if (s1.size()==0){ 
            work();
        }else V.push_back(s1);
    }
    
    return 0;
}
