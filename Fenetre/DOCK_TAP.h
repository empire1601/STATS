#ifndef DOCK_TAP_H
#define DOCK_TAP_H

#include "Resume/TAP/TAP.h"

class DOCK_TAP : public QDockWidget
{
    Q_OBJECT
    public:
        DOCK_TAP(POPULATION *pop, QWidget *parent=0);
    public slots:
        void Ch_Var(QIntList id);
    private:
        QTableView *table;
        TaP *model;
};

#endif // DOCK_TAP_H
