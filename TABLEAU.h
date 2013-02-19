#ifndef TABLEAU_H
#define TABLEAU_H

#include "Tableau/DIAL_TABLEAU.h"
#include "Tableau/POP_TABLEAU.h"
#include "Graph/Histogram.h"

#include <fstream>
#include <iostream>

class TABLEAU : public QTableView
{
    Q_OBJECT
    public:
        TABLEAU(POPULATION *pop,QWidget *parent=0);
    public slots:
        void Ch_Nom_VAR(int id);
        void Ch_Nom_VAR(QString n);
        void Ch_Valides(QBoolList v);
        void viewEnteteMenu(const QPoint &p);
        void SuppVar();
        void ChTypeVar();
        void ChValManq();
        void GrouperVal();
        void ReactiveVal();
        void EditTypeVar(int i);
        void EditTypeVarOrd(QStringList t);
        void EditTypeVarBin(QStringList t);
        void setSelection(int i, int j);
        void Charger();

    private :
            void keyPressEvent(QKeyEvent *event);
            POPULATION *modele;
            int id_courant;


            QClipboard *Clipboard;

            QAction *actionSupprimer, *actionTrier, *actionChType, *actionValManq;
            QAction *actionReactiValeur, *actionGrouperVal, *actionCharger;

            QItemSelectionModel *selection;
};

#endif // TABLEAU_H
