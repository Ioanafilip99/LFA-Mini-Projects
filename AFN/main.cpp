#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

ifstream fin("date1.in");

unsigned int si,sf[100],nsf,ntr,ok;       ///si=starea initiala, sf=starile finale, nsf=nr de stari finale, ntr=nr de tranzitii(muchii)
char cuvant[100];
struct graf
{
    unsigned int s1,s2;     ///cele doua stari
    char c;                 ///tranzitia/caracterul
}G[100];

void cautare(unsigned int stare,unsigned int poz, char cuvant[])       ///stare=starea/nodul curent, poz=pozitia in cuvant
{
    unsigned int i,j,n;

    n=strlen(cuvant)-1;

    for(i=0; i<ntr; i++)
    {
        if(stare==G[i].s1 && cuvant[poz]==G[i].c && poz<=n)     ///daca prima stare este cea cautata si are caracterul corespunzator pozitionarii in cuvant si nu s-a depasit lungimea cuvantului
        {
            if(poz==n)      ///daca s-a ajuns la finalul cuvantului
            {
                for(j=0; j<nsf; j++)
                    if(G[i].s2==sf[j])      ///verifica daca a doua stare este finala
                    {
                        ok=1;               ///daca da, atunci este un cuvant bun
                        return;
                    }
            }
            else            ///altfel se continua cautarea
                cautare(G[i].s2,poz+1,cuvant);
        }
    }
    ///daca cuvantul nu a fost bun, atunci la sfarsitul for ului se iese din functie si ok ramane 0
}

bool AFN()
{
    unsigned int i,n,j;

    n=strlen(cuvant);

    if(n==1)        ///cazul in care cuvantul este format dintr-un singur caracter sau cel in care este cuvantul vid
    {
        if(cuvant[0]=='0')      ///conventie: '0'==cuvantul vid==lamda
        {
            strcpy(cuvant,"lamda");
            if(G[0].s1==sf[0])      ///verifica daca limbajul accepta cuvantul vid
                ok=1;
        }
        else
        {
            for(i=0; i<ntr; i++)    ///cazul in care cuvantul nu este vid dar are un singur caracter
            {
                if(G[i].s1==si && G[i].c==cuvant[0])    ///daca se gaseste o stare initiala din care sa plece caracterul din cuvant
                    for(j=0; j<nsf; j++)                ///daca starea in care pleaca este finala
                        if(G[i].s2==sf[j])
                            ok=1;
            }
        }
    }
    else
    {
        for(i=0; i<ntr; i++)                          ///pot exista mai multe tranzitii din starea initiala
            if(G[i].s1==si && G[i].c==cuvant[0])      ///daca starea curenta este una de inceput si caracterul care pleaca din aceasta se afla la inceputul cuvantului
                cautare(G[i].s2,1,cuvant);                ///atunci de aici se incepe parcurgerea
    }
    if (ok==1)
        return true;
    return false;
}

int main()
{
    unsigned int i;

    fin>>cuvant;
    fin>>si;
    fin>>ntr>>nsf;

    for(i=0; i<nsf; i++)
        fin>>sf[i];

    for(i=0; i<ntr; i++)
        fin>>G[i].s1>>G[i].s2>>G[i].c;

    if(AFN()==true)
        cout<<"Cuvantul "<<cuvant<<" apartine limbajului recunoscut de automat!";
    else cout<<"Cuvantul "<<cuvant<<" NU apartine limbajului recunoscut de automat!";

    return 0;
}
