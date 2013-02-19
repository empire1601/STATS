#ifndef POPULATION_H
#define POPULATION_H

#include "QStringTable.h"
#include "Population/dialog_creationpop.h"
/* A RANGER D'URGENCE*/

class POPULATION : public QStandardItemModel
{
    Q_OBJECT
    public:
        POPULATION(QWidget *parent=0, int nbVar=0, int tpop=50);
        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        int columnCount(const QModelIndex &parent = QModelIndex()) const;
        int columnType(const int id) const;
        QVariant data(const QModelIndex &index, int role) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
        Qt::ItemFlags flags(const QModelIndex &index) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
        bool setData(const int x, const int y, const QVariant &value, int role = Qt::EditRole);
        void addRows(int rows=1,const QModelIndex &index = QModelIndex());
        bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
        bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
        bool addColumn();
        bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex());
        int ValideValues(int id_var, QStringList val, QBoolList b);
        QModelIndex createIndex(int row, int column, int id) const;

        QVar & Table(int id);
        QStringList Modalites(int id);
        QStringList AllModalites(int id);
        QBoolList AllAllow(int id);

        QVar Var(int id);
        QVar *pVar(int id);

        QString Nom();
        void setNom(QString n);
        int Taille();
        int Type(int i);
        int NbValide(int i);
        QString NbValideString(int i);
        double Somme(int i);
        double Moyenne(int i);
        double Variance(int i);
        double Max(int i);
        double Min(int i);
        VAL_GROUP *Grouped_Values(int id);

        //Resumés
        ResumMulti *Resumes(QIntList id);

    public slots :
            void setNomVar(int id, QString n);
            void setTypeVar(int id, int v);
            void setTypeVar(int id, int v, QStringList m);
            void init_Pop(QIntList *parametre);

    protected:
            QDonnees table;

    private :
            QStringList string_list;
            QString nom;
            SYSTEM *system;

};

#endif // POPULATION_H
