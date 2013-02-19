#ifndef ASSISTANT_H
#define ASSISTANT_H

#include "DialAssistant.h"
#include <iostream>
#include <vector>

class LIS_DIAL_ASSISTANT
{
public:
    LIS_DIAL_ASSISTANT(QWidget *p, QString title,bool pre=false, bool fin=false);
    void AdQDial (QString t,bool fin = false);
    DIAL_ASSISTANT *RechDial(int id);
    LIS_DIAL_ASSISTANT *pNext;

    int nb(int n=1);

private:
    DIAL_ASSISTANT *elt;
    QWidget *parent;
};
class ASSISTANT:public QObject
{
    Q_OBJECT
public:
    ASSISTANT(QString title,QWidget *p, std::vector<QString> *result);
    void AdPage(QString title="",bool fin=false);
    QString saisie(int id=1);
    QString choix(int id=1);
    QString radio(int id=1);

    void AdSaisie(QString t, int mod=0, int id=0);
    void AdChoix(QString t, QStringList l,int id =0);
    void AdDesc(QString t, int id=0);
    void AdRad(QString t, int id=0);

    DIAL_ASSISTANT *page(int id=1);
    int lect;
    ~ASSISTANT();
signals:
    void Fin();
public slots:
    void PageSuiv();
    void PagePre();
    void Ouvrir();
    void Fermer();
private:
    LIS_DIAL_ASSISTANT *liste;
    QString nom;
    QWidget *parent;
    std::vector<QString> *res;
};



#endif // ASSISTANT_H
