#include "Resume.h"

RESUME::RESUME(POPULATION *pop)
{
    //Population cible
        population=pop;
        ChargerNomVar();
        ChargerTypeVar();
    //Tri à plat
        tap=new TaP(pop);
    //Resumes
        res=new ResumMulti;

        QWidget::connect(population, SIGNAL(dataChanged(QModelIndex,QModelIndex)),this, SLOT(MAJ(QModelIndex,QModelIndex)));
}
QIntList RESUME::Cible()
{
    return cible;
}
void RESUME::setCible(int id)
{
    //remise à 0 de la cible
    cible.clear();
    addCible(id);
    MAJ();
}
void RESUME::clearCible()
{
    cible.clear();
}

void RESUME::addCible(int id)
{
    cible+=id;
}
void RESUME::ChargerNomVar()
{
    this->NomVar.clear();
    for(int i=0;i<population->columnCount();i++)
    {
        this->NomVar+=this->population->headerData(i, Qt::Horizontal).toString();
    }
}
void RESUME::ChargerTypeVar()
{
    this->TypeVar.clear();
    for(int i=0;i<population->columnCount();i++)
    {
        this->TypeVar+=this->population->Type(i);
    }
}

void RESUME::MAJ(QModelIndex a, QModelIndex b)
{
    //Mises à jour classiques
    ChargerNomVar();
    ChargerTypeVar();
    //Mise à jour du tri à plat
    tap->setVar(cible);
    //Mise à jour des résumés statistiques
    delete this->res;
    res=this->population->Resumes(cible);
}
