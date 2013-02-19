#include "Widget_POPULATION.h"

QGraphicsItemVariable::QGraphicsItemVariable(QString n, QStringList d, int i, int type, QGraphicsItem *parent) : QGraphicsRectItem (parent)
{
    id=i;
    QPen pen(Qt::black);
    switch(type)
    {
        case TYPES::INCONNU :
                    pen.setBrush(Qt::black);
                    break;
        case TYPES::BINOMIAL :
                    pen.setBrush(Qt::cyan);
                    break;
        case TYPES::QUALITATIF_ORDINAL :
                    pen.setBrush(Qt::blue);
                    break;
        case TYPES::QUALITATIF_PURE :
                    pen.setBrush(Qt::green);
                    break;
        case TYPES::QUANTITATIF_DISCRET :
                    pen.setBrush(Qt::yellow);
                    break;
        case TYPES::QUANTITATIF_CONTINU_PURE :
                    pen.setBrush(Qt::red);
                    break;
        case TYPES::QUANTITATIF_CONTINU_BORNE :
                    pen.setBrush(Qt::magenta);
                    break;

    }
    setPen(pen);
    setRect(0,0,90,30);

    nom = new QGraphicsTextItem(n,this);
    nom->setHtml("<center>"+n+"</center>");
    nom->setPos(22.5,7.5);

    setFlag(QGraphicsItem::ItemIsSelectable);
}

GRAPHIC_POPULATION::GRAPHIC_POPULATION(RESUME *res, QGraphicsScene *scene, QWidget *parent) : QGraphicsView (scene,parent)
{
    resume=res;
    groupe=0;

    Charg_Var();

}
void GRAPHIC_POPULATION::Charg_Nom()
{
}
void GRAPHIC_POPULATION::Charg_Taille()
{
    /*QString t;
    t.setNum(population->Taille());
    Taille = new QGraphicsTextItem(Cercle_Pop);
    Taille->setScale(3);
    Taille->setPos(0,150);
    Taille->setHtml("<center>"+t+"</center>");*/
}
void GRAPHIC_POPULATION::Charg_Var()
{
    scene()->clear();
    int nbVar = this->resume->NomVar.count();
    Var = new QGraphicsItemVariable *[nbVar];
    for(int i=0;i<nbVar;i++)
    {
        Var[i] = new QGraphicsItemVariable(this->resume->NomVar.at(i), QStringList(), i, this->resume->TypeVar.at(i));
        Var[i]->setPos((-(nbVar-1)*90)/2+i*(90+20), 400);
        scene()->addItem(Var[i]);
    }
}
void DESSIN_POPULATION::MAJ_POP(QModelIndex a, QModelIndex p)
{
    /*Cercle_Pop = new QGraphicsEllipseItem();
    Cercle_Pop->setRect(0,0,300,300);
    Cercle_Pop->setFlag(QGraphicsItem::ItemIsSelectable);*/

    this->graph->Charg_Var();

    //scene()->addItem(/*Cercle_Pop*/);


}
void GRAPHIC_POPULATION::Aff_Info(int i)
{
    //emit MAJ_Info(population->headerData(i, Qt::Horizontal).toString());
}
DESSIN_POPULATION::DESSIN_POPULATION(RESUME *res, QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    scene = new QGraphicsScene;
    graph = new GRAPHIC_POPULATION(res,scene);
    this->resume=res;
    layout->addWidget(graph);
    setLayout(layout);
    QObject::connect(scene, SIGNAL(selectionChanged()), this, SLOT(Ch_Selection()));
}
void DESSIN_POPULATION::Ch_Selection()
{
    if(scene->selectedItems().size())
    {
        int x = scene->selectedItems().at(scene->selectedItems().size()-1)->x();
        x+=((this->resume->NomVar.count()-1)*90)/2;
        x=x/110;
        if(scene->selectedItems().size()==1)
        {
            if(scene->selectedItems().at(scene->selectedItems().size()-1)->y()==400)
            {
                qDebug()<<"Selection de la variable"<<x;
                this->resume->setCible(x);
                /*QString nbValide;
                nbValide.setNum(population->NbValide(x));
                emit Modif_Var_Selec(population->Var(x));
                emit Modif_Var_Selec(x);
                if(nbValide=="0")
                {emit Modif_Info("Nom : "+population->headerData(x, Qt::Horizontal).toString() + "\n"+ "Nombre de la valeurs valides : "+ nbValide);}
                else
                {
                    TAP_DONNEES tap;
                    tap.Charger(population->pVar(x));
                    QStringList mode (tap.Mode());
                    QString chMode("");
                    if(mode.size())
                    {
                        chMode+=mode.at(0);
                    }
                    for(int i=1;i<mode.size();i++)
                    {chMode+=" ; "+mode.at(i);}



                    switch(population->Type(x))
                    {
                        case TYPES::INCONNU :
                                    emit Modif_Info("Nom : "+population->headerData(x, Qt::Horizontal).toString() + "\n"+ "Nombre de valeurs valides : "+ nbValide);
                                    break;
                        case TYPES::BINOMIAL :
                                    emit Modif_Info("Nom : "+population->headerData(x, Qt::Horizontal).toString() + "\n"+ "Nombre de valeurs valides : "+ nbValide);
                                    break;
                        case TYPES::QUALITATIF_ORDINAL :
                                    emit Modif_Info("Nom : "+population->headerData(x, Qt::Horizontal).toString() + "\n"+ "Nombre de valeurs valides : "+ nbValide);
                                    break;
                        case TYPES::QUALITATIF_PURE :
                                    emit Modif_Info("Nom : "+population->headerData(x, Qt::Horizontal).toString() + "\n"+ "Nombre de valeurs valides : "+ nbValide + "\nMode(s) : "+ chMode);
                                    break;
                        case TYPES::QUANTITATIF_DISCRET :
                                    emit Modif_Info("Nom : "+population->headerData(x, Qt::Horizontal).toString() + "\n"+ "Nombre de valeurs valides : "+ nbValide + "\nMode(s) : "+ chMode+"\nMoyenne : "+QString().number(population->Moyenne(x), 'f', 4)+"\tVariance : "+QString().number(population->Variance(x), 'f', 4) + "\nMinimum : " + QString().number(population->Min(x),'f', 4) + "\tMaximum : " + QString().number(population->Max(x), 'f', 4));
                                    break;
                        case TYPES::QUANTITATIF_CONTINU_PURE :
                                    emit Modif_Info("Nom : "+population->headerData(x, Qt::Horizontal).toString() + "\n"+ "Nombre de valeurs valides : "+ nbValide + "\nMode(s) : "+ chMode+"\nMoyenne : "+QString().number(population->Moyenne(x), 'f', 4)+"\tVariance : "+QString().number(population->Variance(x), 'f', 4) + "\nMinimum : " + QString().number(population->Min(x),'f', 4) + "\tMaximum : " + QString().number(population->Max(x), 'f', 4));
                                    break;
                        case TYPES::QUANTITATIF_CONTINU_BORNE :
                                    emit Modif_Info("Nom : "+population->headerData(x, Qt::Horizontal).toString() + "\n"+ "Nombre de valeurs valides : "+ nbValide + "\nMode(s) : "+ chMode);
                                    break;

                    }
                }*/

            }
        }
        else
        {
            this->resume->addCible(x);
        }
        ResumMulti *p = resume->res;
        QString texte("");
        for(int i=0;i<p->size();i++)
        {texte+="\n";texte+=p->Ligne(i);}
        emit Modif_Info(texte);
    }
}
