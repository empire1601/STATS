#ifndef TAP_DONNES_H
#define TAP_DONNES_H

#include <QtGui>
#include "Population/POPULATION.h"

class TAP_DONNEES
{
    public:
        TAP_DONNEES();
        void Charger(QVar *variable);
        void Supprimer();
        QStringList Modalites();
        QStringList Effectifs();
        QStringList Frequences();
        QStringList FrequencesCumulees();
        QStringList Mode();
    private :
        QStringList modalites;
        QStringList effectifs;
        QStringList frequences;
        QStringList frequencesCumulees;
        void Trier(QIntList *eff, QStringList *ordre =0);
};

#endif // TAP_DONNES_H
