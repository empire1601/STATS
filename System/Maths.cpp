#include "Maths.h"

using namespace std;

/*
    Version.0.2
    Maths.h :
    -> Division entière
    -> Carre d'un réel
*/

/*/-FctDiv----->Retourne le résultat de la division entière-\*/
int Div(int N, int D)
{
    int R = N % D;
    N=N-R;
    return N/D;
}
/*/-FctCarre----->Retourne le carré de N-\*/
int Carre(int N)
{return N*N;}
double Carre(double N)
{return N*N;}

double Min(double a, double b)
{
    if(a>b)
    {
        return b;
    }
    else
    {
        return a;
    }
}
int Min(int a, int b)
{
    if(a>b)
    {
        return b;
    }
    else
    {
        return a;
    }
}

