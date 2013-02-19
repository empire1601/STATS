#include "Dock_Indicateurs.h"

DOCK_INDICATEURS::DOCK_INDICATEURS(QString Info, QWidget *parent) : QDockWidget("Indicateurs", parent)
{
    information = Info;
     contenu = new QWidget;
     layout = new QHBoxLayout;
     texte= new QLabel(information);
     layout->addWidget(texte);
     contenu->setLayout(layout);
     setWidget(contenu);
}
void DOCK_INDICATEURS::setInfo(QString Info)
{
    information=Info;
    texte->setText(information);
}
