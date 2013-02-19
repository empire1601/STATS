#include "TABLEAU.h"
#include "qdebug.h"

TABLEAU::TABLEAU(POPULATION *pop, QWidget *parent):QTableView(parent)
{
    qDebug()<<"Creation d'un tableau";
    setModel(pop);
    modele=pop;
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    id_courant=0;
    Clipboard = QApplication::clipboard();
    horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(horizontalHeader(), SIGNAL(sectionDoubleClicked(int)), this, SLOT(Ch_Nom_VAR(int)));
    QObject::connect(horizontalHeader(), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(viewEnteteMenu(QPoint)));

    actionTrier = new QAction("Trier", this);
    actionChType = new QAction("Changer de type", this);
    actionSupprimer = new QAction("Supprimer", this);
    actionValManq = new QAction("Masquer les valeurs non valides", this);

    actionReactiValeur = new QAction("Activer cette valeur", this);
    actionGrouperVal = new QAction("Grouper les valeurs identiques", this);
    actionCharger = new QAction("Charger des valeurs depuis un csv", this);//A placer dans une barre d'outils

    QObject::connect(actionSupprimer, SIGNAL(triggered()),this, SLOT(SuppVar()));
    QObject::connect(actionChType, SIGNAL(triggered()), this, SLOT(ChTypeVar()));
    QObject::connect(actionValManq, SIGNAL(triggered()),this, SLOT(ChValManq()));
    QObject::connect(actionReactiValeur, SIGNAL(triggered()),this, SLOT(ReactiveVal()));
    QObject::connect(actionGrouperVal, SIGNAL(triggered()),this, SLOT(GrouperVal()));
    QObject::connect(actionCharger, SIGNAL(triggered()),this, SLOT(Charger()));

}
void TABLEAU::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_C and event->modifiers()==Qt::ControlModifier)
    {
        //Copie
    }
    if(event->key()==Qt::Key_V and event->modifiers()==Qt::ControlModifier)
    {
        QString pressePapier = Clipboard->text(); //On stocke le contenu du Presse-Papier
        int size=pressePapier.size(); //Taille du texte contenu
        //pressePapier.resize(size);
        QChar saut('\n');
        QChar tab('\t');
        QModelIndexList select = selectedIndexes();
        if(pressePapier[size-1]==saut and select.size())
        {
            //Copie valide
                int i=0;
                int ligne=select.at(0).row();
                int colonne=select.at(0).column();

                while(i<size)
                {
                    QString text("");
                    for(i ;pressePapier[i]!=saut and pressePapier[i]!=tab;i++)
                    {
                        text+=pressePapier[i];
                    }

                    modele->setData(modele->createIndex(ligne, colonne,0), text);
                    if(pressePapier[i]==tab)
                    {colonne++;}
                    if(pressePapier[i]==saut)
                    {colonne=select.at(0).column();ligne++;}
                    i++;
                }
        }
    }
    QModelIndexList select = selectedIndexes();
    if(select.size()  and event->modifiers()!=Qt::ControlModifier and ((event->key()>=Qt::Key_0 and event->key()<=Qt::Key_9) or (event->key()>=Qt::Key_A and event->key()<=Qt::Key_Z)))
    {
        edit(select.at(0));
    }
    if(select.size()  and event->modifiers()!=Qt::ControlModifier and ((event->key()>=Qt::Key_Left and event->key()<=Qt::Key_Down)))
    {
        switch(event->key())
        {
            case Qt::Key_Left :
                if(select.at(0).column())
                {setSelection(select.at(0).column()-1, select.at(0).row());}
                break;
            case Qt::Key_Right :
                if(select.at(0).column()<modele->columnCount())
                {setSelection(select.at(0).column()+1, select.at(0).row());}
                break;
            case Qt::Key_Up :
                if(select.at(0).row())
                {setSelection(select.at(0).column(), select.at(0).row()-1);}
                break;
            case Qt::Key_Down :
                if(select.at(0).row()<modele->rowCount())
                {setSelection(select.at(0).column(), select.at(0).row()+1);}
                break;
        }
    }

}
void TABLEAU::setSelection(int i, int j)
{
    int ti=-horizontalScrollBar()->value();
    int tj=-verticalScrollBar()->value();
    for(int di=0; di<i;di++)
    {
        ti+=columnWidth(di);
    }
    for(int dj=0; dj<j;dj++)
    {
        tj+=rowHeight(dj);
    }
    QTableView::setSelection(QRect(ti, tj,1, 1),QItemSelectionModel::SelectCurrent);
}
void TABLEAU::Ch_Nom_VAR(int id)
{
    id_courant=id;
    if(id_courant<this->modele->columnCount())
    {
        POP_EDITION_NOM *edition = new POP_EDITION_NOM(columnWidth(id),model()->headerData(id, Qt::Horizontal).toString(), this);

        int p=95;
        for(int i=0; i<id;i++)
        {
            p+=columnWidth(i);
        }
        edition->move(QPoint(p+QApplication::activeWindow()->x(), 60+QApplication::activeWindow()->y()));
        edition->show();

        QObject::connect(edition, SIGNAL(Ferme(QString)), this, SLOT(Ch_Nom_VAR(QString)));
    }
}
void TABLEAU::Ch_Nom_VAR(QString n)
{
    modele->setNomVar(id_courant, n);
}
void TABLEAU::ChValManq()
{    
    DIAL_VAL_MANQUANTES * fen = new DIAL_VAL_MANQUANTES(modele->AllModalites(id_courant),modele->AllAllow(id_courant),this);
    QObject::connect(fen, SIGNAL(Ferme(QBoolList)), this, SLOT(Ch_Valides(QBoolList)));
    fen->exec();
}
void TABLEAU::Ch_Valides(QBoolList v)
{
    int t=0;
    t+=modele->ValideValues(id_courant,modele->AllModalites(id_courant), v);
    QString ct;
    ct.setNum(t);
    QMessageBox::information(this, "Modification des valeurs valides", ct+" valeurs ont changé de validité !");
}
void TABLEAU::viewEnteteMenu(const QPoint &p)
{
    int t=0;
    int i=0;
    for(i=0; t<p.x() and i<modele->columnCount();i++)
    {
        t+=columnWidth(i);
    }
    id_courant = i-1;
    if(i<modele->columnCount())
    {
        QMenu menu (horizontalHeader());

        menu.addAction(actionCharger);
        menu.addAction(actionTrier);
        menu.addAction(actionChType);
        menu.addAction(actionSupprimer);
        menu.addAction(actionValManq);
        menu.addAction(actionGrouperVal);


        menu.exec(horizontalHeader()->mapToGlobal(p));
        //MENU_GRAPH menu( &actions, p);
        //menu.exec();
    }
}
void TABLEAU::SuppVar()
{
    modele->removeColumns(id_courant, 1);
}
void TABLEAU::ReactiveVal()
{

}

void TABLEAU::ChTypeVar()
{
    POP_EDITION_TYPE *edition = new POP_EDITION_TYPE(modele->Type(id_courant), this);
    int p=95;
    for(int i=0; i<id_courant;i++)
    {
        p+=columnWidth(i);
    }
    edition->move(QPoint(p+QApplication::activeWindow()->x(), 60+QApplication::activeWindow()->y()));
    edition->show();
     QObject::connect(edition, SIGNAL(Ferme(int)), this, SLOT(EditTypeVar(int)));
}
void TABLEAU::EditTypeVar(int i)
{
    QStringList mod(modele->Modalites(id_courant));
    if(i==TYPES::QUALITATIF_ORDINAL and mod.size())
    {
        DIAL_CONV_ORD * fen = new DIAL_CONV_ORD(mod, this);
        QObject::connect(fen, SIGNAL(Ferme(QStringList)), this, SLOT(EditTypeVarOrd(QStringList)));
        fen->exec();
    }
    else
    {
        if(i==TYPES::QUALITATIF_ORDINAL)
        {QMessageBox::critical(this, "Modification du type de variable", "La transformation en type ordinale n'est faisable qu'à partir d'une variable comportant déjà au moins une entrée valide");}
        else
        {
            if(i==TYPES::BINOMIAL)
            {
                DIAL_CONV_BIN * fen = new DIAL_CONV_BIN(this);
                QObject::connect(fen, SIGNAL(Ferme(QStringList)), this, SLOT(EditTypeVarBin(QStringList)) );
                fen->exec();
            }
            else
            {modele->setTypeVar(id_courant, i);}
            QMessageBox::information(this, "Modification du type de variable", modele->NbValideString(id_courant) +" entrées validées !");
        }
    }
}
void TABLEAU::EditTypeVarOrd(QStringList t)
{
    modele->setTypeVar(id_courant, TYPES::QUALITATIF_ORDINAL, t);
}
void TABLEAU::EditTypeVarBin(QStringList t)
{
    modele->setTypeVar(id_courant, TYPES::BINOMIAL, t);
}
void TABLEAU::GrouperVal()
{
    DIAL_REGROUPER_VAL * fen = new DIAL_REGROUPER_VAL(modele->Grouped_Values(id_courant),this);
    fen->exec();
}
void TABLEAU::Charger()
{
    QString chemin = QFileDialog::getOpenFileName(this,"Ouvrir un fichier csv", QString(), "*.csv");
    ifstream BDD(string(chemin.toStdString()).c_str(), ios::in | ios::binary);
    // GESTION DES ERREURS
    if(!BDD.is_open())
    {
        qDebug()<<"Fichier non ouvert !";
    }

    // Lecture
    else
    {
            QString t;
            bool test;
            char a=0;
            int j;
            for(int i=0;a!=EOF and i<this->modele->rowCount();i++)
            {
                t.clear();
                bool b=false;
                j=0;
                while(!b)
                {
                    BDD.read((char *)&a, sizeof(char));
                    b=(a=='\n' or a==EOF or a=='\t');
                    if(!b)
                    {
                        t+=a;
                    }
                }
                modele->setData(modele->createIndex(i, j,0), t);
                if(a=='\t')
                {
                    j++;
                }
            }
     }
}
