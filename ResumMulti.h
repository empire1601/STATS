#ifndef RESUMMULTI_H
#define RESUMMULTI_H

#include "System/SYSTEM.h"

class ResumMulti : public TablePlus<double>
{
    public:
        QString Ligne(int i)
        {
            return QString(this->nom[i]+" : "+QString().setNum(this->var[i]));
        }
        QString Nom(int i)
        {return this->nom[i];}
        double Value(int i)
        {return this->var[i];}
};

#endif // RESUMMULTI_H
