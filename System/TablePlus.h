#ifndef TABLEPLUS_H
#define TABLEPLUS_H

#include "QtGui"

/*////////////////////////////////////////////////////////////////////TablePlus\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
-------------------------------------------------------  Liste avec nom de l'entrée        --------------------------------------------------
-------------------------------------------------------  ->V 1.1                           ---------------------------------------------------
-------------------------------------------------------  ->Type de données template        ----------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------*/

template <class T> class TablePlus
{
    public:

        void Ad(QString n, T val)
        {
            nom+=n;
            var+=val;
        }
        int size()
        {return this->nom.size();}

    protected:
        QStringList nom;
        QList<T> var;
};
template <class T, class TP1, class TP2> class TableStat2
{
    public:

        void Ad(TP1 p1, TP2 p2, T val)
        {
            para1+=p1;
            para2+=p2;
            var+=val;
        }
        int size()
        {return this->var.size();}
        T val(TP1 p1, TP2 p2)
        {
            T r=0;
           for(int i=0; i<this->size();i++)
           {
               if(para1[i]==p1 and para2[i]==p2)
               {
                   r=var[i];
                   break;
               }
           }
           return r;
        }

    protected:
        QList<TP1> para1;
        QList<TP2> para2;
        QList<T> var;
};

#endif // TABLEPLUS_H
