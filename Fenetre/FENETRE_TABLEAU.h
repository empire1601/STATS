#ifndef FENETRE_TABLEAU_H
#define FENETRE_TABLEAU_H

#include "TABLEAU.h"

class FENETRE_TABLEAU : public QMainWindow
{
    public :
            FENETRE_TABLEAU(POPULATION *mod);
    private :
        QWidget * contenu;
        QHBoxLayout * layout;
        POPULATION *modele;

        TABLEAU *tableau;

        QClipboard *Clipboard;
};

#endif // FENETRE_TABLEAU_H
