#include <iostream>
#include <fstream>

using namespace std;
int nt,nsf,nsnf;     ///nr tipuri tranziti (litere), nr stari finale, nr stari nefinale

struct stari
{
    int tranzitie[100];     ///starile in care ajunge cu fiecare tip de tranzitie
    int index;              ///indicele starii

}snf[100],sf[100];  ///starile nefinale, starile finale

void citire()       ///citeste tabelul de intrare al starilor, dat de impartirea starilor in nefinale si finale
{
    int i,j;

    ifstream fin("AfdComplet.txt");
    fin>>nsnf>>nsf>>nt;

    for (i=0; i<nsnf; i++)  ///citeste starile nefinale
    {
        fin>>snf[i].index;
        for(j=0; j<nt; j++)
            fin>>snf[i].tranzitie[j];
    }

    for (i=0; i<nsf; i++)   ///citeste starile finale
    {
        fin>>sf[i].index;
        for(j=0; j<nt; j++)
            fin>>sf[i].tranzitie[j];
    }

    fin.close();
}

int verificare(stari s1, stari s2)  ///verifica daca doua stari sunt duplicate
{
    int i;
    for(i=0; i<nt; i++)
    {
        if(s1.tranzitie[i]!=s2.tranzitie[i])
            return 0;
    }
    return 1;
}

void EliminareStare(int s,int poz)  ///sterge din tabel starea duplicat de pe pozitia poz
{
    int i;
    if(s==1)    ///pt starile nefinale
    {
        for(i=poz; i<nsnf-1; i++)
            snf[i]=snf[i+1];

        nsnf--;
    }
    else    ///pt starile finale
    {
        for(i=poz; i<nsf-1; i++)
                sf[i]=sf[i+1];
        nsf--;
    }
}

void ModificareTranz(int s,int x,int y)     ///odata ce starea duplicata x este eliminata, aparitiile ei in tranzitiile altor stari trebuie inlocuita cu cealalta stare duplicat pe care o pastram, y
{
    int i,j;
    if(s==1)    ///pt starile nefinale
    {
        for(i=0; i<nsnf; i++)
            for(j=0; j<nt; j++)
                if(snf[i].tranzitie[j]==x)
                    snf[i].tranzitie[j]=y;
    }
    else    ///pt starile finale
    {
        for(i=0; i<nsf; i++)
            for(j=0; j<nt; j++)
                if(sf[i].tranzitie[j]==x)
                    sf[i].tranzitie[j]=y;
    }
}

void minimal()
{
    int i,j,gasit=1;

    ///pt starile nefinale
    while(gasit==1) ///cat timp s-au mai gasit stari duplicat
    {
        gasit=0;
        for(i=0; i<nsnf-1 && gasit==0; i++)
        {
            for(j=i+1; j<nsnf && gasit==0; j++)
            {
                if(verificare(snf[i],snf[j])==1)    ///daca au aceleasi stari pentru orice tranzitie
                {
                    ModificareTranz(1,snf[j].index,snf[i].index);   ///inlocuieste starea j cu i
                    EliminareStare(1,j);    ///elimina starea dublicat j
                    gasit=1;
                }
            }

        }   ///daca s-a gasit o stare duplicat, cautarea se reia de la inceput pentru ca unele tranzitii se pot modifica
    }

    ///pt starile finale
    gasit=1;
    while(gasit==1)
    {
        gasit=0;
        for(i=0; i<nsf-1 && gasit==0; i++)
        {
            for(j=i+1; j<nsf && gasit==0; j++)
            {
                if(verificare(sf[i],sf[j])==1)
                {
                    ModificareTranz(2,sf[j].index,sf[i].index);
                    EliminareStare(2,j);
                    gasit=1;
                }
            }

        }
    }
}

void afisare()      ///afiseaza tabelul starilor modificat, fara stari duplicate, deci afd ul minimal
{
    int i,j;

    ofstream fout("AfdMinimal.txt");

    fout<<"ADF MINIMAL"<<endl;

    for (i=0; i<nsnf; i++)
    {
        fout<<snf[i].index<<"   ";
        for(j=0; j<nt; j++)
            fout<<snf[i].tranzitie[j]<<"   ";
        fout<<endl;
    }

    for (i=0; i<nsf; i++)
    {
        fout<<sf[i].index<<"   ";
        for(j=0; j<nt; j++)
            fout<<sf[i].tranzitie[j]<<"   ";
        fout<<endl;
    }

    fout.close();
}

int main()
{
    citire();
    minimal();
    afisare();
    return 0;
}
