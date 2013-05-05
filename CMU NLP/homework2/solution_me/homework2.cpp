#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <string.h>
#include <queue>
#include <map>
#include <fstream>
#include <set>
#include <math.h>
#include <sstream>
using namespace std;

typedef long long ll;
const double pi = acos(-1.0);
const double eps = 1e-8;

const int dx[8]={1,0,-1,0,-1,-1,1,1};
const int dy[8]={0,1,0,-1,1,-1,1,-1};
const int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
const int leap[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};

string s,s1,s2,com;
double k;
vector<string> V;
map<string,int> ID;
map<string,double> M1;
map<string,double> Run[188];
double Rel[188][188][188];
string name[188],sentence[111];
int sum;
double f[44][44][188];
int path1[44][44][188],path2[44][44][188],path3[44][44][188];
set<string> NON_RARE;

void print(int s,int len,int k){
//    printf("%d %d %d\n",s,len,k);
//    system("pause");
    if (len==1){
        string ret = "";
        /*
        for (int i=0;i<sentence[s].size();++i)
            if (sentence[s][i]=='\\'){ 
                ret+="\\";
                ret+="\\";
            }else ret+=sentence[s][i];
        printf("[\"%s\", \"%s\"]",name[k].c_str(),ret.c_str());
        */
        printf("[\"%s\", \"%s\"]",name[k].c_str(),sentence[s].c_str());
        return;
    }
    printf("[\"%s\", ",name[k].c_str());
    print(s,path1[s][len][k]-s+1,path2[s][len][k]);
    printf(", ");
    print(path1[s][len][k]+1,len-(path1[s][len][k]-s+1),path3[s][len][k]);
    printf("]");
}

int main(){
    ifstream fin1("parse_train.counts.out");
    ID.clear();M1.clear();NON_RARE.clear();
    sum=0;
    for (int i=0;i<sum;++i)
        for (int j=0;j<sum;++j)        
            for (int k=0;k<sum;++k)        
                Rel[i][j][k]=-1e20;
    while (fin1 >> k >> com){
        if (com[0]=='N'){
            fin1 >> s;
            M1[s]=k;
            ID[s]=sum;
            name[sum]=s;
            Run[sum++].clear();
        }
        if (com[0]=='B'){
            fin1 >> s >> s1 >> s2;
            Rel[ID[s]][ID[s1]][ID[s2]]=log(k/M1[s]);
        }
        if (com[0]=='U'){
            fin1 >> s1 >> s2;
            Run[ID[s1]][s2]=log(k/M1[s1]);
            NON_RARE.insert(s2);
        }
    }
    
    while (getline(cin,s)){
        int n = 0;
        istringstream sin(s);
        while (sin>>s1) sentence[n++]=s1;     
        for (int i=0;i<n;++i)
            for (int j=0;j<=n;++j)        
                for (int k=0;k<sum;++k)        
                    f[i][j][k]=-1e20;
        for (int i=0;i<n;++i)
            if (NON_RARE.find(sentence[i])==NON_RARE.end()){
                for (int j=0;j<sum;++j)
                    if (Run[j].find("_RARE_")!=Run[j].end())
                        f[i][1][j]=Run[j]["_RARE_"];   
            }else{
                for (int j=0;j<sum;++j)
                    if (Run[j].find(sentence[i])!=Run[j].end())
                        f[i][1][j]=Run[j][sentence[i]];
            }             
                       
        for (int len=2;len<=n;++len)
            for (int i=0;i+len-1<n;++i)
                for (int j=0;j<sum;++j)
                    for (int k=i;k<i+len-1;++k)
                        for (int p=0;p<sum;++p)
                            if (f[i][k-i+1][p]>-1e10)
                                for (int q=0;q<sum;++q)
                                    if (f[k+1][i+len-1-k][q]>-1e10)
                                        if (f[i][len][j]<f[i][k-i+1][p]+f[k+1][i+len-1-k][q]+Rel[j][p][q]){
                                            f[i][len][j]=f[i][k-i+1][p]+f[k+1][i+len-1-k][q]+Rel[j][p][q];
                                            path1[i][len][j]=k;
                                            path2[i][len][j]=p;
                                            path3[i][len][j]=q;
                                        }
        print(0,n,ID["SBARQ"]);
        puts("");
    }
    return 0;
}
