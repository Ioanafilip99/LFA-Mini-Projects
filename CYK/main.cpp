#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <map>
#include <string>
using namespace std;

int n;
vector<pair<string,vector<string>>>P;   ///vetorul de productii
vector<vector<string>>M;    ///matricea cyk

string cuv;

void citire()
{
    ifstream fin("date.in");

    fin>>n;

    int i,j,ns;
    string S,x;
    vector<string>s;

    for(i=0; i<n; i++)
    {
        fin>>S>>ns;

        for(j=0; j<ns; j++)
        {
            fin>>x;
            s.push_back(x);
        }

        P.push_back(make_pair(S,s));
        s.erase(s.begin(),s.end());
    }

    fin.close();

}

void afisare()
{
    int i,j;

    for(i=0; i<n; i++)
    {
        cout<<P[i].first<<" -> ";

        for(j=0; j<P[i].second.size()-1; j++)
            cout<<P[i].second[j]<<'/';

        cout<<P[i].second[j];
        cout<<endl;
    }
}
void linie1()
{
    int i,j,k=0;
    vector<string>linie;

    while(k<cuv.length())
    {
        for(i=0; i<n; i++)
            for(j=0; j<P[i].second.size(); j++)
                if(cuv[k]==P[i].second[j][0])
                    linie.push_back(P[i].first);

        M.push_back(linie);
        linie.erase(linie.begin(),linie.end());
        k++;
    }
}

void afisare_matrice()
{
    int i,j;
    for(i=0; i<M.size(); i++)
    {
        for(j=0; j<M[i].size(); j++)
                cout<<M[i][j]<<' ';
        //cout<<endl;
    }
}
int main()
{
    citire();
    afisare();

    cout<<"Introdu cuvantul: "<<endl;
    cin>>cuv;
    linie1();
    afisare_matrice();
    return 0;
}
