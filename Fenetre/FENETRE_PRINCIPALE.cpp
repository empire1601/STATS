#include "FENETRE_PRINCIPALE.h"
#include <QtDebug>

/*
                                        FenetrePrincipale.cpp
        Version 0

*/

//////////////////////////////////////////////FENETRE_PRINCIPALE\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//->Cstr : Créé une fenetre principale avec un titre donné
FENETRE_PRINCIPALE::FENETRE_PRINCIPALE(POPULATION *pop, QString titre)
{
    //Paramètres principaux de la fenêtre
        setStyleSheet("background-color: rgb(255,255,255)");
        setWindowTitle("STATS : "+titre);//Titre
        setGeometry(QRect(75,75,1250,550));
        showMaximized();


        QObject::connect(&system, SIGNAL(message(QString)), this, SLOT(aff_mesg(QString)));
        system.CHRG_LOIS();

        //Création d'une nouvelle population si fichier non chargé
        if(!pop)
        {
            modele =  new POPULATION(this);
        }

    //Paramètres des onglets
        Clipboard = QApplication::clipboard();

    //Zone Centrale

        QMdiArea *zoneCentrale = new QMdiArea;
           setCentralWidget(zoneCentrale);
           fenetrePopulation = new FENETRE_POPULATION(modele);
           fenetreTableau = new FENETRE_TABLEAU(modele);

           QMdiSubWindow *sousFenetre1 = zoneCentrale->addSubWindow(fenetrePopulation);
           QMdiSubWindow *sousFenetre2 = zoneCentrale->addSubWindow(fenetreTableau);

           zoneCentrale->setViewMode(QMdiArea::TabbedView);

}
void FENETRE_PRINCIPALE::aff_mesg(QString txt)
{
    QMessageBox::information(this, "Debug", txt);
}

FENETRE_TEST::FENETRE_TEST()
{
    setStyleSheet("background-color: rgb(255,255,255)");
    setWindowTitle("Test");//Titre
    setGeometry(QRect(75,75,1250,550));

}




