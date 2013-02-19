#include "Assistant.h"

ASSISTANT::ASSISTANT(QString title, QWidget *p, std::vector<QString> *result)
{
    liste=0;
    lect=1;
    parent=p;
    nom=title;
    res=result;
}
void ASSISTANT::AdPage(QString title, bool fin)
{
    if(title=="")
    {title=nom;}
    if(liste)
    {liste->AdQDial(title,fin);}
    else
    {liste = new LIS_DIAL_ASSISTANT(parent,title,false,fin);}
}
void ASSISTANT::AdSaisie(QString t, int mod, int id)
{
    if(!id)
    {id=liste->nb();}
    page(id)->AdSaisieTexte(t,mod);
}
void ASSISTANT::AdDesc(QString t, int id)
{
    if(!id)
    {id=liste->nb();}
    page(id)->AdDescTexte(t);
}
void ASSISTANT::AdRad(QString t, int id)
{
    if(!id)
    {id=liste->nb();}
    page(id)->AdRadTexte(t);
}
DIAL_ASSISTANT *ASSISTANT::page(int id)
{
    return liste->RechDial(id-1);
}
void ASSISTANT::AdChoix(QString t, QStringList l, int id)
{
    if(!id)
    {id=lect+1;}
    page(id)->AdChTexte(t,l);
}
QString ASSISTANT::saisie(int id)
{
    return page(lect)->textSaisie(id);
}
QString ASSISTANT::choix(int id)
{
    return page(lect)->textChoix(id);
}
void ASSISTANT::PageSuiv()
{
    qDebug() << "Dans PageSuiv";
    page(lect)->close();
    disconnect(page(lect),0,0,0);
    if(page(lect)->terminer)
    {
        QObject::connect(page(lect), SIGNAL(suivant()), this, SLOT(Fermer()));}
    else
    {lect++;
        QObject::connect(page(lect+1), SIGNAL(precedent()), this, SLOT(PagePre()));
        QObject::connect(page(lect+1), SIGNAL(suivant()), this, SLOT(PageSuiv()));
    page(lect)->show();
    }

}
void ASSISTANT::PagePre()
{
    qDebug() << "Dans PagePre";
    if(liste)
    {
        disconnect(this);
        disconnect(page(lect),0,0,0);
        page(lect)->close();
        qDebug() << "Lect = " <<lect;
        if(lect-1)
        {
            disconnect(this,0,0,0);
            disconnect(page(lect),0,0,0);
            lect--;
            QObject::connect(page(lect), SIGNAL(precedent()), this, SLOT(PagePre()));
            qDebug() << "Connexion Suivant, il est " << QTime::currentTime().toString("HH:mm::ss");
            QObject::connect(page(lect), SIGNAL(suivant()), this, SLOT(PageSuiv()));
            page(lect)->show();
        }
        else
        {
            disconnect(this,0,0,0);
            QObject::connect(page(lect), SIGNAL(precedent()), this, SLOT(Fermer()));
            qDebug() << "Connexion Suivant, il est " << QTime::currentTime().toString("HH:mm::ss");
            QObject::connect(page(lect), SIGNAL(suivant()), this, SLOT(PageSuiv()));
            qDebug() << "Show";
            page(lect)->show();
            qDebug() << "Après Show";
        }
    }
}
void ASSISTANT::Ouvrir()
{
    qDebug() << "Dans Ouvrir";
    qDebug() << "Lect = " <<lect;
    if(liste)
    {
        QObject::connect(page(lect), SIGNAL(precedent()), this, SLOT(Fermer()));
        if(page(lect)->terminer)
        {
            QObject::connect(page(lect), SIGNAL(suivant()), this, SLOT(Fermer()));}
        else
        {
            QObject::connect(page(lect), SIGNAL(suivant()), this, SLOT(PageSuiv()));
        }
        page(lect)->show();
    }
}
void ASSISTANT::Fermer()
{
    if(liste)
    {
        if(page(lect)->terminer)
        {
            int k = 1;
            while(res->size())
            {res->pop_back();}
            for(int i=1; i<=liste->nb();i++)
            {
                for(int j=1; j<=page(i)->nbResult;j++)
                {
                    res->push_back(page(i)->resultat(j));
                    k++;
                }
            }
            emit Fin();
        }

       page(lect)->close();
    }
    delete this;
}
ASSISTANT::~ASSISTANT()
{

}



LIS_DIAL_ASSISTANT::LIS_DIAL_ASSISTANT(QWidget *p, QString title, bool pre, bool fin)
{
    elt = new DIAL_ASSISTANT(p, pre,fin);
          elt->setTitle(title);
    pNext=0;
    parent=p;
}
void LIS_DIAL_ASSISTANT::AdQDial(QString t,bool fin)
{
    if(!pNext)
    {
        pNext = new LIS_DIAL_ASSISTANT(parent,t,true,fin);
    }
    else
    {
        pNext->AdQDial(t,fin);
    }
}
DIAL_ASSISTANT *LIS_DIAL_ASSISTANT::RechDial(int id)
{
    if(!id)
    {return elt;}
    else
    {
       if(pNext)
       {
          return pNext->RechDial(id-1) ;
       }
       else
       {
           return 0;
       }
    }
}
int LIS_DIAL_ASSISTANT::nb(int n)
{
    if(pNext)
    {return pNext->nb(n+1);}
    else
    {return n;}
}

