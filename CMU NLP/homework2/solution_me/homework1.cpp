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
using namespace std;

typedef long long ll;
const double pi = acos(-1.0);
const double eps = 1e-8;

const int dx[8]={1,0,-1,0,-1,-1,1,1};
const int dy[8]={0,1,0,-1,1,-1,1,-1};
const int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
const int leap[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};

string s;
vector<string> V;
map<string,int> M;
int main(){
    M.clear();
    freopen("parse_train_vert.dat","r",stdin);
    freopen("parse_train2.dat","w",stdout);
    
    while (getline(cin,s)){
        V.push_back(s);
        for (int i=0;i<s.size();++i)
            if (s[i]=='['){
                int pos=s.find(']',i+1);
                if (pos==string::npos) continue;
                string t = s.substr(i+1,pos-i-1);
                int num = 0;
                for (int j=1;j<t.size();++j)
                    if (t[j]==',' && t[j-1]=='\"') ++num;
                if (num!=1) continue;
                int pos2 = s.find(',',i+1);
                M[s.substr(pos2+2,pos-pos2-2)]++;
            }
    }
    for (int p=0;p<V.size();++p){
        s=V[p];
        for (int i=0;i<s.size();++i)
            if (s[i]=='['){
                int pos=s.find(']',i+1);
                if (pos==string::npos) continue;
                string t = s.substr(i+1,pos-i-1);
                int num = 0;
                for (int j=1;j<t.size();++j)
                    if (t[j]==',' && t[j-1]=='\"') ++num;
                if (num!=1) continue;
                int pos2 = s.find(',',i+1);
                if (M[s.substr(pos2+2,pos-pos2-2)]<5)
                    for (int j=0;j<pos-pos2-2;++j) s[pos2+2+j]='@';
            }
//        printf("%s\n",s.c_str());
        string t="";
        bool bi=false;
        for (int i=0;i<s.size();++i){
            if (s[i]!='@'){
                t+=s[i];
                bi=false;
                continue;
            }
            if (!bi) t+="\"_RARE_\"";
            bi=true;
        }
        printf("%s\n",t.c_str());
    }
            
    return 0;
}
