#ifndef FENETRE_POPULATION_H
#define FENETRE_POPULATION_H

#include "Fenetre/DOCK_FENETRE_POPULATION.h"
#include "Widget_POPULATION.h"
#include "Resume/Resume.h"

class FENETRE_POPULATION : public QMainWindow
{
    public :
            FENETRE_POPULATION(POPULATION *pop);
    private :
        DESSIN_POPULATION * contenu;
        QHBoxLayout * layout;
        DOCK_INDICATEURS *dockInd;
        DOCK_TAP *dockTAP;
        DOCK_GRAPHDISTRIB *dockGraph;
};

#endif // FENETRE_POPULATION_H
