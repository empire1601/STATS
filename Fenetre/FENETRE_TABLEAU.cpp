#include "FENETRE_TABLEAU.h"

FENETRE_TABLEAU::FENETRE_TABLEAU(POPULATION *mod)
{
    //Parmètres principaux de la fenêtre
        setStyleSheet("background-color: rgb(255,255,255)");
        setWindowTitle("Tableau");//Titre
        setGeometry(QRect(75,75,1250,550));

        modele = mod;

        Clipboard = QApplication::clipboard();

        QMdiArea *zoneCentrale = new QMdiArea;
           setCentralWidget(zoneCentrale);

        layout = new QHBoxLayout;
        tableau = new TABLEAU(mod,this);
        layout->addWidget(tableau);
        zoneCentrale->setLayout(layout);
}
