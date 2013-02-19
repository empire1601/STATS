#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H



#include "Fenetre/FENETRE_POPULATION.h"
#include "Fenetre/FENETRE_TABLEAU.h"


class FENETRE_TEST : public QMainWindow
{
    public:
        FENETRE_TEST();

};

class FENETRE_PRINCIPALE : public QMainWindow
{
    Q_OBJECT
        public:
                FENETRE_PRINCIPALE(POPULATION *pop=0, QString titre="Sans titre");

                SYSTEM system;

            public slots:
                void aff_mesg(QString txt);


        private:
                FENETRE_POPULATION *fenetrePopulation;
                FENETRE_TABLEAU *fenetreTableau;
                FENETRE_TEST *fenetreTest;

                POPULATION *modele;

                QClipboard *Clipboard;
};



#endif // FENETREPRINCIPALE_H
