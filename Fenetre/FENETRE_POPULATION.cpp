#include "FENETRE_POPULATION.h"


FENETRE_POPULATION::FENETRE_POPULATION(POPULATION *pop)
{
    //Parmètres principaux de la fenêtre
        setStyleSheet("background-color: rgb(255,255,255)");
        setWindowTitle("Populations");//Titre
        setGeometry(QRect(75,75,1250,550));

        QMdiArea *zoneCentrale = new QMdiArea;
           setCentralWidget(zoneCentrale);


        layout = new QHBoxLayout;
        RESUME *r=new RESUME(pop);
        contenu = new DESSIN_POPULATION(r);
        layout->addWidget(contenu);
        zoneCentrale->setLayout(layout);

        dockInd = new DOCK_INDICATEURS("Sélectionnez une variable", this);
        addDockWidget(Qt::LeftDockWidgetArea, dockInd);

        dockTAP = new DOCK_TAP(pop, this);
        addDockWidget(Qt::TopDockWidgetArea, dockTAP);
        dockTAP->move(QPoint(170,0));

        dockGraph = new DOCK_GRAPHDISTRIB(r, this);
        this->addDockWidget(Qt::TopDockWidgetArea,dockGraph);
        dockGraph->move(QPoint(0,0));


        QObject::connect(contenu, SIGNAL(Modif_Info(QString)), dockInd, SLOT(setInfo(QString)));
        QObject::connect(contenu,SIGNAL(Modif_Var_Selec(QIntList)), dockTAP, SLOT(Ch_Var(QIntList)));
        QObject::connect(contenu,SIGNAL(Modif_Var_Selec(QIntList)), dockGraph, SLOT(Ch_Var(QVar)));

}
