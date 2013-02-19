#ifndef DIAL_VAL_MANQUANTES_H
#define DIAL_VAL_MANQUANTES_H

#include "Population/POPULATION.h"

class CHECK_ID : public QCheckBox
{
    Q_OBJECT
    public:
        CHECK_ID(int i, QString nom, QWidget *parent);
    public slots :
        void t_select(bool b);
    signals :
        void select(int id, bool b);
    private:
        int id;
};

class LIST_CHECK_MOD : public QListWidget
{
    Q_OBJECT
    public:
        LIST_CHECK_MOD(QStringList mod, QBoolList valide);
    public slots:
        void t_select(int id, bool b);
    signals:
        void select(int id, bool b);

    private:
        QListWidgetItem **items;
};

class DIAL_VAL_MANQUANTES : public QDialog
{
    Q_OBJECT
    public:
        DIAL_VAL_MANQUANTES(QStringList mod, QBoolList valide, QWidget *parent);
        void show();
    public slots:
        void Valid_OK();
        void Select_Check(int id, bool b);
    signals:
        void Ferme(QBoolList b);
    private:
        LIST_CHECK_MOD *liste;
        QVBoxLayout * layout;
        QLabel * legende;
        QPushButton * OK;

        QBoolList data;
};




#endif // DIAL_VAL_MANQUANTES_H
