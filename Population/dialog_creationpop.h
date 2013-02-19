#ifndef DIALOG_CREATIONPOP_H
#define DIALOG_CREATIONPOP_H

/*
  *
  *
  *
  *                 dialog_creationpop.h
  *
  *                 -> Saisie des paramètres d'une nouvelle population
  *                 -> Retour par le signal Fermer
  *                 -> Bornes :
  *                             50 variables max
  *                             1000 individus
  *
  *********************************************************************************************/

#include <QDialog>
#include "System/QIntList.h"

namespace Ui {
class Dialog_CreationPop;
}

class Dialog_CreationPop : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog_CreationPop(QWidget *parent = 0);
    ~Dialog_CreationPop();
public slots :
    void fermeture();
signals:
    void Fermer(QIntList *res);
private:
    Ui::Dialog_CreationPop *ui;
    QIntList *resu;
};

#endif // DIALOG_CREATIONPOP_H
