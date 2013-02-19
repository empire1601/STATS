#include "SYSTEM.h"
#include "qdebug.h"


SYSTEM::SYSTEM():QObject()
{
}
void SYSTEM::CHRG_LOIS()
{
    this->CHRG_KHI();
}
TABLEKHI SYSTEM::TAB_KHI;
void SYSTEM::CHRG_KHI()
{
    ifstream BDD(string("Khi2.txt").c_str(), ios::in | ios::binary);
    // GESTION DES ERREURS
    if(!BDD.is_open())
    {
    }

    // Lecture
    else
    {
            // Taille
            QString t;
            double d;
            int ddl=0;
            double p=0;
            bool test;
            char a;
            for(int i=1;i<30*1000;i++)
            {
                t.clear();
                bool b=false;
                while(!b)
                {
                    BDD.read((char *)&a, sizeof(char));
                    b=(a==' ');
                    if(!b)
                    {
                        t+=a;
                    }
                }
                if(!t.endsWith("\""))
                {
                    d=t.toDouble(&test);
                    if(test)
                    {this->TAB_KHI.Ad(ddl,p/1000,d);}
                }
                else
                {
                    ddl++;
                    p=0;
                }
                p++;
            }
     }


}
double SYSTEM::KHI(int ddl, double p)
{
    return this->TAB_KHI.val(ddl,p);
}

/*

    }*/
