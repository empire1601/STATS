#ifndef WIDGET_POPULATION_H
#define WIDGET_POPULATION_H

#include "Population/POPULATION.h"
#include "Resume/Resume.h"

#include "GRAPH.h"
#include "QDeclarativeContext"
#include "qmlapplicationviewer.h"

#include "System/Maths.h"

//#include "tvplot.h"

/*///////////////////////////////////////////////////////////////QGraphicsItemVariable\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
-------------------------------------------------------  Vignette affichée pour les variables --------------------------------------------------
-------------------------------------------------------  ->V 1.0                              ---------------------------------------------------
-------------------------------------------------------  ->Affichage du nom                   ----------------------------------------------------
-------------------------------------------------------  ->Couleur pour le type               -------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------*/

class QGraphicsItemVariable : public QGraphicsRectItem
{
    public:
        QGraphicsItemVariable(QString n, QStringList d, int i, int type=0, QGraphicsItem *parent=0);

    private:
        QGraphicsTextItem *nom;
        int id;
};
/*///////////////////////////////////////////////////////////////GRAPHIC_POPULATION\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
-------------------------------------------------------  Affichage d'une population         -------------------------------------------------
-------------------------------------------------------  ->V 2.0                            --------------------------------------------------
-------------------------------------------------------  ->MAJ des informations automatique ----------------------------------------------------
-------------------------------------------------------  ->Plus de bulle pop                ---------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------*/

class GRAPHIC_POPULATION : public QGraphicsView
{
    Q_OBJECT
    public :
            GRAPHIC_POPULATION(RESUME *res, QGraphicsScene *scene, QWidget *parent=0);
    public slots:
        void Aff_Info(int i);
        void Charg_Nom();
        void Charg_Taille();
        void Charg_Var();
    signals:
        void MAJ_Info(QString info);
    private:
        QGraphicsItemGroup *groupe;

        QGraphicsEllipseItem *Cercle_Pop;
        QGraphicsTextItem *Nom;
        QGraphicsTextItem *Taille;
        QGraphicsItemVariable **Var;

        RESUME * resume;
};
/*//////////////////////////////////////////////////////////////DESSIN_POPULATION\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
-------------------------------------------------------  Dessin de la population           --------------------------------------------------
-------------------------------------------------------  ->V 1.0                           ---------------------------------------------------
-------------------------------------------------------  ->Selection des variables         ----------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------*/

class DESSIN_POPULATION : public QWidget
{
    Q_OBJECT
    public:
        DESSIN_POPULATION(RESUME *res, QWidget *parent=0);
    public slots:
        void Ch_Selection();
        void MAJ_POP(QModelIndex a = QModelIndex(),QModelIndex p=QModelIndex());
    signals:
        void Modif_Info(QString Info);
        void Modif_Var_Selec(QVar var);
        void Modif_Var_Selec(QIntList id);

    private:
        QGraphicsScene *scene;
        GRAPHIC_POPULATION *graph;
        RESUME *resume;
};

#endif // WIDGET_POPULATION_H
