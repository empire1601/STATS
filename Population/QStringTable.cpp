#include "QStringTable.h"
#include "qdebug.h"

/*////////////////////////////////////////////////////////////////////QDonnees\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
-------------------------------------------------------  Liste des variables               --------------------------------------------------
-------------------------------------------------------  ->V 2.0                           ---------------------------------------------------
-------------------------------------------------------  ->Héritage de QList               ----------------------------------------------------
-------------------------------------------------------  ->Lecture des valeurs en fonction -------------------------------------------------------
-------------------------------------------------------     du type                        -------------------------------------------------------
-------------------------------------------------------  ->Edition des dimensions          ------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------*/

//->Cstr : Crée une nouvelle table avec un nombre d'entrée maximum
QDonnees::QDonnees(int tMax)
{
    taille=tMax;
}
//->Lecture
    //->Taille : nombre d'entrées possibles dans la table
    int QDonnees::Taille() const
    {
        return taille;
    }
    //->NbVar : nombre de variables/colonnes dans la table
    int QDonnees::NbVar() const
    {
        return size();
    }
    //->RechRow : valeur observée sur la colonne i et la ligne j
    QString QDonnees::RechRow(int i, int j) const
    {
        return this->operator [](i).Row(j);
    }
    QString QDonnees::Value(int i, int j) const
    {
        return this->operator [](i).Value(j);
    }
    QVar *QDonnees::Variable(int id)
    {
        return &this->operator [](id);
    }

//->Ecriture
    //->Modification des dimensions
        //->setTaille : Editer le nombre maximum d'entrées
        void QDonnees::setTaille(int t)
        {
            taille=t;
        }
        //->AdVar : Ajouter une variable vide / copier une variable déjà existente
        void QDonnees::AdVar(int type)
        {
            append(QVar());
            this->operator [](this->size()-1).setType(type);
            this->operator [](this->size()-1).setTaille(taille);
        }
        void QDonnees::AdVar(QVar var)
        {
            qDebug()<<"Une variable copiée";
            append(var);
        }
        QDonnees& QDonnees::operator+=(const QVar &var)
        {
            if(var.NbVal()>this->Taille())
            {
                this->setTaille(var.NbVal());
            }
            AdVar(var);

            return *this;
        }
        //->SupVar : Supprimer une variable à une certaine position
        void QDonnees::SupVar(int position)
        {
            removeAt(position);
        }
        //->AdRow : Ajouter des entrées vides
        void QDonnees::AdRows(int rows)
        {
            taille+=rows;
            for(int i=0; i<size() ; i++)
            {
                this->operator [](i).AdRows(rows);
            }
        }
        //->SupRow : Suprimer une entrée à une certaine position
        void QDonnees::SupRow(int position)
        {
            taille--;
        }
//->Calcul
    //->Liens : Calcul des résumés statistiques entre les variables sélectionnées
        ResumMulti * QDonnees::Resum(QIntList id)
        {
            ResumMulti * resum = new ResumMulti;
            int qual=0;
            int cont=0;
            int disc=0;
            int ord=0;
            for(int i=0;i<id.count();i++)
            {
                resum->Ad("Nombre de valeurs valides", this->operator [](id.at(i)).NbValide());
                switch(this->operator [](id.at(i)).Type())
                {
                    case TYPES::QUALITATIF_ORDINAL:
                        ord++;
                        break;
                    case TYPES::QUANTITATIF_DISCRET:
                        resum->Ad("Moyenne",this->operator [](id.at(i)).Moyenne());
                        resum->Ad("Variance",this->operator [](id.at(i)).Variance());
                        resum->Ad("Minimum",this->operator [](id.at(i)).Min());
                        resum->Ad("Maximum",this->operator [](id.at(i)).Max());
                        disc++;
                        break;
                    case TYPES::QUANTITATIF_CONTINU_PURE:
                        resum->Ad("Moyenne",this->operator [](id.at(i)).Moyenne());
                        resum->Ad("Variance",this->operator [](id.at(i)).Variance());
                        resum->Ad("Minimum",this->operator [](id.at(i)).Min());
                        resum->Ad("Maximum",this->operator [](id.at(i)).Max());
                        cont++;
                        break;
                    case TYPES::QUALITATIF_PURE:
                        qual++;
                        break;
                }
            }
            if(id.count()==2)
            {
                if(qual==2)
                {
                    double Kh=this->Khi2(id.at(0),id.at(1));
                    resum->Ad("Khi²", Kh);
                    //Calcul de la p-valeur
                    SYSTEM sys;
                    int nbA=this->operator [](id.at(0)).Modalites().size()-1;
                    int nbB=this->operator [](id.at(1)).Modalites().size()-1;
                    double i=0;
                    for(i;sys.KHI(nbA*nbB,i/1000)<Kh and i<999;i++)
                    {};
                    if(i){i--;};
                    resum->Ad("p-valeur",1-i/1000 );
                }
                if(disc+cont==2)
                {
                    resum->Ad("Covariance", this->Covariance(id.at(0),id.at(1)));
                    resum->Ad("R²", this->R2(id.at(0),id.at(1)));
                }
                if(qual==1 and (disc+cont)==1)
                {
                    resum->Ad("Variance Intra",this->VarIntra(id.at(0),id.at(1)));
                    resum->Ad("Variance Inter",this->VarInter(id.at(0),id.at(1)));
                    resum->Ad("Eta²",this->Eta2(id.at(0),id.at(1)));
                }
            }


            return resum;
        }
        //->Khi2
        double QDonnees::Khi2(int a, int b)
        {
            qDebug()<<a<<"'n"<<b;
            QStringList moda(this->operator [](a).Modalites());
            QStringList modb(this->operator [](b).Modalites());
            qDebug()<<moda[0];
            qDebug()<<modb[0];
            int *** Eij;
            int ** Ta;
            int ** Tb;
            Eij=new int **[moda.size()];
                for(int i=0;i<moda.size();i++)
                {
                    Eij[i]=new int *[modb.size()];
                    for(int j=0; j<modb.size();j++)
                    {
                        Eij[i][j]=new int;
                        *Eij[i][j]=0;
                    }
                }
                    for(int k=0;k<this->Taille();k++)
                    {
                        QString ma=this->RechRow(a,k);
                        QString mb=this->RechRow(b,k);

                        if(moda.contains(ma) and modb.contains(mb))
                        {
                            int i,j;
                            for(i = 0;i<moda.size();i++)
                            {if(moda[i]==ma){break;}}
                            for(j=0;j<modb.size();j++)
                            {if(modb[j]==mb){break;}}
                            if(i<moda.size() and j<modb.size())
                            {
                                *Eij[i][j]=*Eij[i][j]+1;
                            }
                        }
                    }

            Ta=new int *[moda.size()];
            Tb=new int *[modb.size()];
            int Totn=0;
            for(int i=0;i<moda.size();i++)
            {
                int Tot=0;
                for(int j=0; j<modb.size();j++)
                {
                    Tot+=*Eij[i][j];
                    Totn+=*Eij[i][j];
                }
                Ta[i]=new int;
                *Ta[i]=Tot;
            }
            for(int j=0;j<modb.size();j++)
            {
                int Tot=0;
                for(int i=0; i<moda.size();i++)
                {
                    Tot+=*Eij[i][j];
                }
                Tb[j]=new int;
                *Tb[j]=Tot;
            }
            double K=0;
            double T;
            for(int j=0;j<modb.size();j++)
            {
                for(int i=0; i<moda.size();i++)
                {
                    T=((*Ta[i])*(*Tb[j]))/Totn;
                    qDebug()<<"T = "<<T;
                    if(T)
                    {K+=Carre(*Eij[i][j]-T)/T;}
                }
            }
            //Destruction
            for(int i=0;i<moda.size();i++)
            {
                for(int j=0;j<modb.size();j++)
                {
                    delete Eij[i][j];
                }
                delete Eij[i];
            }
            delete Ta;
            delete Tb;
            delete Eij;
            return K;
        }
        //->Covariance
        double QDonnees::Covariance(int a, int b)
        {
            double sum=0;
            double moya=this->operator [](a).Moyenne();
            double moyb=this->operator [](b).Moyenne();
            for(int i=0;i<this->Taille();i++)
            {
                if(this->operator [](a).isValide(i) and this->operator [](b).isValide(i))
                {
                    sum+=(this->RechRow(a,i).toDouble()-moya)*(this->RechRow(b,i).toDouble()-moyb);
                }
            }
            return sum/Min(this->operator [](a).NbValide(), this->operator [](b).NbValide());
        }
        //->R²
        double QDonnees::R2(int a, int b)
        {
            double cov=this->Covariance(a,b);
            double eta=sqrt(this->operator [](a).Variance());
            double etb=sqrt(this->operator [](b).Variance());
            return cov/(eta*etb);
        }
        //->Eta²
        double QDonnees::Eta2(int a, int b)
        {
            if(this->operator [](b).Type()==TYPES::QUALITATIF_PURE || this->operator [](a).Type()==TYPES::QUALITATIF_ORDINAL)
            {
                return this->Eta2(b,a);
            }
            else
            {
                return this->VarIntra(a,b)/this->operator [](b).Variance();
            }

        }

        //->Taux-B
        double QDonnees::TauxB(int a, int b)
        {

        }
        //->Décomposition de la variance
            //->Var intra
            double QDonnees::VarIntra(int a, int b)
            {
                int n = Min(this->operator [](a).NbValide(),this->operator [](b).NbValide());
                return this->SCfac(a,b)/n;
            }
            //Somme des Carrés des facteurs
            double QDonnees::SCfac(int a, int b)
            {

                double resul=0;
                if(this->operator [](b).Type()==TYPES::QUALITATIF_PURE || this->operator [](a).Type()==TYPES::QUALITATIF_ORDINAL)
                {
                    resul=this->SCfac(b,a);
                }
                else
                {
                    QStringList moda(this->operator [](a).Modalites());
                    int r=0;
                    double **eff;
                    double **sSimp;
                    double **sCarr;
                    eff=new double*[moda.size()];
                    sSimp=new double*[moda.size()];
                    sCarr=new double*[moda.size()];
                    for(int i=0;i<moda.size();i++)
                    {
                        eff[i]=new double;
                        *eff[i]=0;
                        sSimp[i]=new double;
                        *sSimp[i]=0;
                        sCarr[i]=new double;
                        *sCarr[i]=0;
                    }
                    for(int i=0;i<this->operator [](b).NbVal() and r<this->operator [](b).NbValide();i++)
                    {
                        if(this->operator [](b).isValide(i))
                        {
                            r++;
                            QString va = this->RechRow(a,i);
                            double vb = this->operator [](b).RechRowDouble(i);
                            int j=0;
                            for(j;j<moda.size();j++)
                            {
                                if(moda[j]==va)
                                {
                                   break;
                                }
                            }
                            if(j<moda.size())
                            {
                                *eff[j]+=1;
                                *sSimp[j]+=vb;
                                *sCarr[j]+=Carre(vb);
                            }
                        }
                    }
                    for(int i=0;i<moda.size();i++)
                    {
                        resul+= *sCarr[i]-(Carre(*sSimp[i]))/ (*eff[i]);
                    }

                }
                return resul;
            }
            //->Var inter
            double QDonnees::VarInter(int a, int b)
            {
                if(this->operator [](b).Type()==TYPES::QUALITATIF_PURE || this->operator [](a).Type()==TYPES::QUALITATIF_ORDINAL)
                {
                    return this->VarInter(b,a);
                }
                else
                {
                    return this->operator [](b).Variance()-this->VarIntra(a,b);
                }
            }
 //SLOTS
            void QDonnees::MAJ_VAL_VAR(int p)
            {
                this->operator [](p).MAJ_valide();
            }


/*////////////////////////////////////////////////////////////////////QVar\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
-------------------------------------------------------  Classe générale pour les variables--------------------------------------------------
-------------------------------------------------------  ->V 2.0                           ---------------------------------------------------
-------------------------------------------------------  ->Non méthode<->type              ----------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------*/
//->Cstr
QVar::QVar()
{
    this->nom="Variable";
    this->val_group=new VAL_GROUP();
}
QVar::QVar(int s, int t)
{
    for(int i=0;i<s;i++)
    {
        this->elt+="";//Cases vides
        this->valide+=false;//Données non valides car vides
        this->co_lib+=0;//Initialisation des libellés
    }
    this->type=t;
    this->nom="Variable";
    this->val_group=new VAL_GROUP();
}
QVar::QVar(const QVar &var)
{
    for(int i=0;i<var.NbVal();i++)
    {
        this->elt+=var.Row(i);
        this->valide+=var.isValide(i);
        this->co_lib+=0;
    }
    type=var.Type();
    nom="Variable";
    this->val_group=new VAL_GROUP();
}

QString QVar::Row(int i) const
{
    if(val_group)
    {
        return this->val_group->Evalue(this->elt.at(i));
    }
    else
    {
        return elt.at(i);
    }
}
QString QVar::Value(int i) const
{
    return elt.at(i);
}
int QVar ::RechRowInt(int i)
{
    return Row(i).toInt();
}
double QVar ::RechRowDouble(int i)
{
    return Row(i).toDouble();
}
void QVar::SupRow(int id)
{
    if(id<elt.size())
    {
        elt.removeAt(id);
        valide.removeAt(id);
    }
}

void QVar::AdRows(int n)
{

    for(int i=0;i<n;i++)
    {
        elt+="";
        valide+=false ;
    }
}
void QVar::setRow(int i, QString value)
{
        elt.replace(i,value);
        bool ok=false;
        if(!val_inter.contains(elt.at(i)))
        {
            switch(Type())
            {
                case TYPES::INCONNU :
                            valide.replace(i, false);
                            break;
                case TYPES::BINOMIAL :
                            valide.replace(i,this->val_group->Contains(elt.at(i)));
                            break;
                case TYPES::QUALITATIF_ORDINAL :
                            valide.replace(i,this-val_group->Contains(elt.at(i)));
                            break;
                case TYPES::QUALITATIF_PURE :
                            valide.replace(i, this->Row(i)!="");
                            break;
                case TYPES::QUANTITATIF_DISCRET :
                            Row(i).toInt(&ok);
                                valide.replace(i, ok);
                            break;
                case TYPES::QUANTITATIF_CONTINU_PURE :
                            Row(i).toDouble(&ok);
                                valide.replace(i, ok);
                            break;
                case TYPES::QUANTITATIF_CONTINU_BORNE :

                            break;
                }
        }
        else
        {
            valide.replace(i, false);
        }
}
int QVar::Type() const
{
    return type;
}
void QVar::setTaille(int t)
{
    qDebug()<<t;
    if(t<elt.size())
    {
    }
    else
    {
        for(int i=elt.size();i<t;i++)
        {
            elt+="";
            valide+=false ;
        }
    }
}

int QVar::NbVal() const
{
    return elt.size();
}
void QVar::setType(int t)
{
    type=t;
    if(val_group)
    {val_group=new VAL_GROUP();}
    MAJ_valide();
}
void QVar::Conv_Bornee(QStringList bornes)
{
    delete val_group;
    this->val_group= new VAL_GROUP();
    for(int i=0;i<bornes.size();i++)
    {val_group->Add(bornes[i]);}
}

void QVar::setType(int t, QStringList trie)
{
    type=t;

    val_group->Remplace(trie);

    MAJ_valide();
}
VAL_GROUP *QVar::Val_Group()
{
    return this->val_group;
}

QString QVar::Nom() const
{
    return nom;
}
bool QVar::isValide(int i) const
{
    return valide.at(i);
}

void QVar::setNom(QString n)
{
    nom=n;
}
void QVar::MAJ_valide()
{
    bool ok;
    for(int i=0;i<valide.size();i++)
    {
        if(!val_inter.contains(elt.at(i)))
        {
            switch(Type())
            {
                case TYPES::INCONNU :
                            valide.replace(i, false);
                            break;
                case TYPES::BINOMIAL :
                            valide.replace(i,val_group->Contains(elt.at(i)));
                            break;
                case TYPES::QUALITATIF_ORDINAL :
    
                            break;
                case TYPES::QUALITATIF_PURE :
                            valide.replace(i, Row(i)!="");
                            break;
                case TYPES::QUANTITATIF_DISCRET :
                            Row(i).toInt(&ok);
                                valide.replace(i, ok);
                            break;
                case TYPES::QUANTITATIF_CONTINU_PURE :
                            Row(i).toDouble(&ok);
                                valide.replace(i, ok);
                            break;
                case TYPES::QUANTITATIF_CONTINU_BORNE :
    
                            break;
    

            }
            if(valide.at(i))
            {
                if(!val_group->Contains(elt.at(i)))
                {
                    val_group->Add(elt.at(i));
                }
            }
            else
            {
                //supprimer une valeur;
            }
        }
        else
        {
            valide.replace(i,false);
        }
    }
}
bool QVar::TypeValide(QString v)
{
    bool ok;
    switch(Type())
    {
        case TYPES::INCONNU :
                    return false;
                    break;
        case TYPES::BINOMIAL :
                    return val_group->Contains(v);
                    break;
        case TYPES::QUALITATIF_ORDINAL :

                    break;
        case TYPES::QUALITATIF_PURE :
                    return v!="";
                    break;
        case TYPES::QUANTITATIF_DISCRET :
                    v.toInt(&ok);
                        return ok;
                    break;
        case TYPES::QUANTITATIF_CONTINU_PURE :
                    v.toDouble(&ok);
                        return ok;
                    break;
        case TYPES::QUANTITATIF_CONTINU_BORNE :

                    break;


    }
}

int QVar::NbValide()
{
    return valide.NbTrue();
}
double QVar::Somme()
{
    double s=0;
        for(int j=0;j<valide.size();j++)
        {
            if(isValide(j))
            {
                s+=RechRowDouble(j);
            }
        }
        return s;

}
double QVar::Moyenne()
{
        int n=NbValide();
        double s=Somme();
        return double(s/n);
}
double QVar::Variance()
{
        double m=Moyenne();
        int n=NbValide();
        double sm=0;
        for(int j=0;j<elt.size();j++)
        {
            if(isValide(j))
            {sm+=Carre(RechRowDouble(j)-m);}
        }
        return sm/n;
}
double QVar::Min()
{
        int j=0;
        double m;
        for(j;j<elt.size();j++)
        {
            if(isValide(j))
            {m=RechRowDouble(j);break;}
        }
        for(j;j<elt.size();j++)
        {
            if(isValide(j) and RechRowDouble(j)<m)
            {m=RechRowDouble(j);}
        }
        return m;
}
double QVar::Max()
{
        int j=0;
        double m;
        for(j;j<elt.size();j++)
        {
            if(isValide(j))
            {m=RechRowDouble(j);break;}
        }
        for(j;j<elt.size();j++)
        {
            if(isValide(j) and RechRowDouble(j)>m)
            {m=RechRowDouble(j);}
        }
        return m;
}
bool QVar::Ordonnee()
{
    return this->type>=TYPES::QUALITATIF_ORDINAL;
}
QStringList QVar::Ordre()
{
    QStringList ord;
    for(int i=0;i<this->val_group->rowCount();i++)
    {
        ord+=this->val_group->item(i,0)->text();
    }
    return ord;
}

void QVar::ModifVarInter(QString val, bool inter)
{
    int i;
    for(i=0;i<val_inter.size() and val_inter[i]!=val;i++)
    {}
    if(i==val_inter.size())
    {
        if(!inter)
        {val_inter+=val;}
    }
    else
    {
        if(inter)
        {val_inter.removeAt(i);}
    }
}

QStringList QVar::Modalites()
{
    QStringList modalites;
    for(int i=0;i<elt.size();i++)
    {
        if(valide[i])
        {
                if(!modalites.contains(elt[i]))
                {
                    modalites+=elt[i];
                }
        }
    }
    return modalites;
}
QStringList QVar::AllModalites()
{
    QStringList modalites;
    for(int i=0;i<elt.size();i++)
    {
        if(elt[i]!="")
        {
                if(!modalites.contains(elt[i]))
                {
                    modalites+=elt[i];
                }
        }
    }
    return modalites;
}
QBoolList QVar::AllAllow()
{
    QBoolList val;
    QStringList modalites=this->AllModalites();
    for(int i=0;i<modalites.size();i++)
    {
        val+=!(val_inter.contains(modalites.at(i)));
    }
    return val;
}

/*int QVar::Ch_Valide_Val(QString val, bool v)
{
    int t=0;
    for(int i=0; i<elt.size();i++)
    {
        if(elt.at(i)==val)
        {   t++;
            valide.replace(i, v);
        }
    }
    return t;
}*/

int QVar::Ch_Valide_Values(QStringList val, QBoolList v)
{
    int t=0;
    //MAJ des valeurs interdites
    for(int i=0;i<val.size();i++)
    {
        if(val_inter.contains(val.at(i)))
        {
            if(v.at(i))
            {
                int j;
                for(j=0;val_inter.at(j)!=val.at(i);j++){};
                val_inter.removeAt(j);
            }
        }
        else
        {
            if(!v.at(i))
            {
                val_inter+=val.at(i);
            }
        }
    }

    for(int i=0; i<elt.size();i++)
    {
        bool b=(!val_inter.contains(elt.at(i)) and this->TypeValide(elt.at(i)));
        if( b!=valide.at(i))
        {
           t++;
           valide.replace(i,b);
        }
    }
    return t;
}
void QVar::Group_value(QString base, QString val)
{
    this->val_group->Group(base,val);
}
