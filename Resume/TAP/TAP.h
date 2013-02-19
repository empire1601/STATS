#ifndef TAP_H
#define TAP_H

#include "Resume/TAP/TAP_Donnes.h"

namespace TriAPlat
{
    enum
    {
        VALEUR, EFFECTIF, FREQUENCE, FREQCUM
    };
}
//Tri à plat classique : ne gère pas les tri croisés
class TaP : public POPULATION
{
    public :
            TaP(POPULATION * pop, QWidget *parent=0);
             QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
             void setVar(QIntList id);
             int TypeVar();
             ResumMulti *Distribution(ResumMulti *older=0);

    public slots :
            void MAJ(const QModelIndex &index, const QModelIndex &value);
    private:

        POPULATION *population;
        int typeVar;

        QVar *var_courante;
};

#endif // TAP_H
