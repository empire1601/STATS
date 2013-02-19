#ifndef RESUME_H
#define RESUME_H

/*
 *
 *
 ********************************************
 **             Resume.h                    *
 **             = Resume de la population   *
 **                                         *
 **                                         *
 ********************************************/
    //Classe de tri à plat
    #include "Resume/TAP/TAP.h"
    //
    #include "ResumMulti.h"
    //Classe de population
    #include "Population/POPULATION.h"

    //Classes system
    #include "System/QIntList.h"
class RESUME : public QObject
{
    Q_OBJECT
public :
    RESUME(POPULATION *pop);
    //Accesseurs
    QIntList Cible();

    //Tri à plat
    TaP *tap;
    //Résumés Statistiques
    ResumMulti *res;
    //Nom des variables
    QStringList NomVar;
    //Type des variables
    QIntList TypeVar;
public slots:
    void MAJ(QModelIndex a=QModelIndex(), QModelIndex b=QModelIndex());
    void ChargerNomVar();
    void ChargerTypeVar();
    void clearCible();
    void setCible(int id);
    void addCible(int id);
private:
    POPULATION *population;
    QIntList cible;
};

#endif // RESUME_H
