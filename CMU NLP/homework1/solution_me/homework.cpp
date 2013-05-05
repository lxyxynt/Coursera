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

map<string,int> M,M2;
set<string> N;

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
//    return "_RARE_";
    if (NU(s)) return "__Numeric";
    if (AC(s)) return "__All_Capitals";
    if (LC(s)) return "__Last_Capital";
    return "__Rare";
}

int main(){
    ifstream fin1("gene.train");
    ifstream fin2("gene.train");
    freopen("gene.train1","w",stdout);
    M.clear();N.clear();M2.clear();
    string s1,s2;
    while (fin1 >> s1 >> s2){ 
        M[s1]++;
        M2[s2]++;
    }
    for (map<string,int>::iterator it=M.begin();it!=M.end();++it)
        if ((it->second) < 5) N.insert(it->first);
//    for (map<string,int>::iterator it=M2.begin();it!=M2.end();++it) cout << it->first << ' ' << it->second << endl;
    string s;
    while (getline(fin2,s)){
        if (s.size()==0){ 
            cout << endl;
            continue;
        }
        istringstream sin(s);
        sin >> s1 >> s2 ;
        if (N.find(s1)==N.end()) cout << s1 << ' ' << s2 << endl;
        else cout << Ch(s1) << ' ' << s2 << endl;
    }
    return 0;
}
