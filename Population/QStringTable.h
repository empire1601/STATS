#ifndef QVar_H
#define QVar_H

/*
  *
  *
  *
  *                 QStringTable.h
  *
  *                 -> Gestion brûte des données de STATS
  *
  *
  *********************************************************************************************/

//->Inclusion du système de valeurs groupées
#include "VAL_GROUP.h"
//->Inclusion des types de variables
#include "TYPES.h"
//->Inclusion de classes de résumés des variables
#include "ResumMulti.h"


/*////////////////////////////////////////////////////////////////////QVar\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
-------------------------------------------------------  Classe générale pour les variables--------------------------------------------------
-------------------------------------------------------  ->V 2.6                           -----------------------------------------------------
-------------------------------------------------------  ->Lecture                         -------------------------------------------------------
-------------------------------------------------------     ->Mise à jour minimales        --------------------------------------------------------
-------------------------------------------------------  ->Gestion des données brûtes      ----------------------------------------------------
-------------------------------------------------------     ->Valeurs interdites           --------------------------------------------------------
-------------------------------------------------------     ->Valeurs ordonnées            --------------------------------------------------------
-------------------------------------------------------     ->Valeurs regroupées           ----------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------*/

class QVar
{
    public:
        //Cstr
            //->Cstr par défaut
            QVar();
            //->Cstr de taille et de type donnés
            QVar(int s, int t);
            //->Cstr de copie
            QVar(const QVar & var);
        //---
        //Ajouts/Suppressions d'entrées
            //Ajout
            void AdRows (int n=1);
            //Suppression
            void SupRow(int id);
        //---

        void setRow(int i, QString value);
        //Edition de la variable
            //Edition du type
                void setType(int t);//Edition du type générale
                void setType(int t, QStringList trie);//Edition du type en ordinal
            void setNom(QString n);//Edition du nom
            void setTaille(int t);//Edition de la taille maximale
            // ---
        // ---

        //Lecture des valeurs
            //->Lecture simple
            QString Row (int i) const;
            //->Lecture d'un nombre entier
            int RechRowInt(int i);
            //->Lecture d'un nombre quelconque
            double RechRowDouble(int i);
            //->Lecture sans filtre
            QString Value (int i) const;
        //---

        //Modalites
            //->Liste des modalités valides
            QStringList  Modalites();
            //->Liste de toutes les modalites
            QStringList AllModalites();
            //->Validité de toutes les modalites
            QBoolList AllAllow();
        //---

        //Nombre d'entrées valides
        int NbValide();
        //Taille des observations
        int NbVal() const;
        //Type de la variable (cf TYPES.h)
        int Type() const;
        //Nom de la variable
        QString Nom() const;

        //Indicateurs numériques
            double Moyenne();
            double Variance();
            double Max();
            double Min();
            double Somme();
        // ---


        bool isValide(int i) const;//Valeur i valide
        int Ch_Valide_Values(QStringList val, QBoolList v);

        void MAJ_valide();
        //Rendre une valeurs valide ou non
        void ModifVarInter(QString val, bool inter);

        //Libelles et valeures groupées
            void Group_value(QString base, QString val);
        // ---

        //Variable ordonnée
            bool Ordonnee();
            QStringList Ordre();
        // ---
            VAL_GROUP * Val_Group();

    private:
        bool TypeValide(QString v);
        void Conv_Bornee(QStringList bornes);
        //Valeurs
            VAL_GROUP *val_group;//Valeurs groupées et triées
            QStringList val_inter;//valeurs interdites
        // ---

        int type;
        QString nom;

        QIntList co_lib;
        //Observations
            QStringList elt;
            QBoolList valide;
        // ---
};

class QDonnees : public QList<QVar>
{
    public:        
        //Cstr
        QDonnees(int tMax = 0);

        //Dimensions
        int Taille() const; //Taille de la population
        int NbVar() const; //Nombre de variables total
        void setTaille(int t); //Changer la taille ?

        //Lecture
        QString RechRow(int i, int j) const; //Lire une valeur
        QString Value(int i, int j) const; //Lire une valeur sans filtre

            //Ajout/Suppression de variable/entrées
            void AdVar(int type=TYPES::INCONNU); //Ajouter une nouvelle variable vide
            void AdVar(QVar var); // Copier une variable déjà existente
            QDonnees& operator+=(QVar const& var);
            void SupVar(int position); // Supprimer une variable
            void AdRows(int rows); // Ajouter des lignes vides
            void SupRow(int position); // Supprimer une entrée
            QVar *Variable(int id);
            //Calculs
            ResumMulti * Resum(QIntList id);

            void MAJ_VAL_VAR(int p);

        private:
            //Indicateurs de lien
            double Khi2(int a, int b); //Khi² de Pearson
            double R2(int a, int b); //Coefficient de corrélation
            double Eta2(int a, int b);
            double TauxB(int a, int b); //Taux-B de Kendall
            //Résumés numériques
            double Covariance(int a, int b);
            //Décomposition de la variance
            double VarIntra(int a, int b);
                double SCfac(int a, int b);
            double VarInter(int a, int b);

            //Attributs
            int taille;

};

#endif // QVar_H
