#ifndef VAL_GROUP_H
#define VAL_GROUP_H

#include <QtGui>


/*//////////////////////////////////////////////////////////////////VAL_GROUP\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
-------------------------------------------------------  Liste hiérarchique de valeurs      --------------------------------------------------
-------------------------------------------------------  groupées                           ---------------------------------------------------
-------------------------------------------------------  ->V 2.0                            ----------------------------------------------------
-------------------------------------------------------  ->Modèle                           ---------------------------------------------------------------------------------------
-------------------------------------------------------  ->Ordonne                          ----------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------*/




class VAL_GROUP : public QStandardItemModel
{
    public:
        //Cstr
        VAL_GROUP(QStringList mod)
        {
            for(int i=0;i<mod.size();i++)
            {
                stdItem+=new QStandardItem(mod.value(i));
                this->setItem(i,stdItem[i]);
            }
            emit dataChanged(QModelIndex(), QModelIndex());
        }
        VAL_GROUP()
        {
        }
        QVariant data(const QModelIndex &index, int role) const
        {
            return QStandardItemModel::data(index,role);
        }
        int rowCount(const QModelIndex &parent=QModelIndex()) const
        {
            return QStandardItemModel::rowCount(parent);
        }

        //Evalue->Retourne le libelle correspondant
        QString Evalue(QString val)
        {
                 QList<QStandardItem*> items = findItems(val,Qt::MatchExactly | Qt::MatchRecursive,0);
                 if(!items.isEmpty())
                 {

                     QStandardItem *parentItem=items[0];
                     for(;parentItem->parent();)
                     {parentItem=parentItem->parent();}
                     return parentItem->text();
                 }
                 else
                 {
                     return val;
                 }

        }
        //Group->Grouper des valeurs
        void Group(QString base, QString val)
        {
            //On vérifie que les valeurs ne sont pas égales
            if(base==val)
            {
            }
            else
            {
                QStandardItem *ItmBase=this->Add(base);
                QList<QStandardItem*> ItmVal = this->findItems(val,Qt::MatchExactly | Qt::MatchRecursive,0);
                if(ItmVal.isEmpty())
                {
                    qDebug()<<"Erreur Valeur non trouvée !!";
                    qDebug()<<val;
                }
                else
                {
                    int r=ItmVal[0]->row();
                    QStandardItem *prt =ItmVal[0]->parent();

                    if(prt)
                    {
                        prt->takeChild(r,ItmVal[0]->column());
                        prt->removeRow(r);
                    }
                    else
                    {
                        this->takeItem(r,ItmVal[0]->column());
                        this->removeRow(r);
                    }
                    ItmBase->setChild(ItmBase->rowCount(),ItmVal[0]);
                    emit dataChanged(QModelIndex(), QModelIndex());
                }
            }

        }
        //Add->Ajouter une valeur si non existante
        QStandardItem * Add(QString val)
        {
            QList<QStandardItem*> Itm = this->findItems(val,Qt::MatchExactly | Qt::MatchRecursive,0);
            if(Itm.isEmpty())
            {
                stdItem+=new QStandardItem(val);
                this->setRowCount(this->rowCount()+1);
                this->setItem(this->rowCount()-1,stdItem[stdItem.size()-1]);
                emit dataChanged(QModelIndex(), QModelIndex());
                return this->item(this->rowCount()-1);
            }
            else
            {
                return Itm[0];
            }
        }
        //Trie->Trie les valeurs dans l'ordre donné
        void Trie(QStringList ord)
        {
            for(int i=0;i<ord.size();i++)
            {
                QList<QStandardItem*> Itm = this->findItems(ord[i],Qt::MatchExactly | Qt::MatchRecursive,0);
                if(Itm.isEmpty())
                {
                    qDebug()<<"Erreur de compatibilité entre le tri et les valeurs possibles";
                }
                else
                {
                    if(Itm[0]->row()!=i)
                    {
                        QStandardItem *old = this->item(i,0);
                        this->takeItem(i,0);
                        int po=Itm[0]->row();
                        this->takeItem(Itm[0]->row(),Itm[0]->column());
                        this->setItem(po, old);
                        this->setItem(i,Itm[0]);
                    }
                }
            }
        }
        bool Contains(QString val)
        {
            QList<QStandardItem*> items = findItems(val,Qt::MatchExactly | Qt::MatchRecursive,0);
            return !(items.isEmpty());
        }
        void Remplace(QStringList vals)
        {
            QStandardItem* itm;
            int i=0;
            for(i;i<vals.size();i++)
            {
                qDebug()<<vals[i];
                itm = this->Add(vals[i]);
                this->takeItem(i,0);
                this->setItem(i,itm);
            }
            if(i<this->rowCount())
            {
                this->removeRows(i+1, this->rowCount()-i);
            }

            emit dataChanged(QModelIndex(), QModelIndex());
        }

        QStandardItem * clone(QStandardItem *root)
        {
            if (!root)
                return 0;
            QStandardItem *clonedRoot = root->clone();
            for(int i=0, rowCount = root->rowCount(); i < rowCount; ++i)
            {
                for(int j=0, columnCount = root->columnCount(); j < columnCount; ++j)
                {
                    QStandardItem *clonedChild = clone(root->child(i,j));
                    if (clonedChild)
                    {
                        clonedRoot->setChild(i, j, clonedChild);
                    }
                }
            }
            return clonedRoot;
        }


    private:
        QList<QStandardItem*> stdItem;
};

#endif // VAL_GROUP_H
