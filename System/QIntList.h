#ifndef QINTLIST_H
#define QINTLIST_H

#include <QtGui>

class QIntList : public QList<int>
{
    public:
        QIntList()
        {

        }
};
class QDoubleList : public QList<double>
{
    public:
        QDoubleList()
        {

        }
        QDoubleList(QStringList text)
        {
            bool ok;
            double d;
            for(int i=0;i<text.size();i++)
            {
                d=text[i].toDouble(&ok);
                if(ok)
                {
                    this->operator +=(d);
                }
            }
        }
};
#endif // QINTLIST_H
