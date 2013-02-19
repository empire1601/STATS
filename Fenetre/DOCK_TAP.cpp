#include "Fenetre/DOCK_TAP.h"

DOCK_TAP::DOCK_TAP(POPULATION *pop, QWidget *parent) : QDockWidget("Tri à plat", parent)
{
    table = new QTableView();
    setWidget(table);
    model = new TaP(pop);
    table->setModel(model);
    table->setColumnWidth(3,130);
    setFixedSize(450,300);
}
void DOCK_TAP::Ch_Var(QIntList id)
{
    qDebug()<<"MAJ du Dock TAP";
    model->setVar(id);
    table->setColumnWidth(3,130);
}
