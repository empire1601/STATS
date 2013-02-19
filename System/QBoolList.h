#ifndef QBOOLLIST_H
#define QBOOLLIST_H

#include <QtGui>
#include "QtDebug"

class QBoolList : public QList <bool>
{
    public:
        QBoolList()
        {

        }
        int NbTrue()
        {
            int t=0;
            for(int i=0; i<size();i++)
            {
                if(this->operator [](i))
                {t++;}
            }
            return t;
        }

};

#endif // QBOOLLIST_H
