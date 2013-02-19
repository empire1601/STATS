#include "DialAssistant.h"
#include <QtDebug>

DIAL_ASSISTANT::DIAL_ASSISTANT(QWidget *p, bool pre, bool fin):QDialog(p)
{
    layoutBout = new QHBoxLayout;
    if(fin)
    {
        boutonSuiv = new QPushButton("Terminer");
    }
    else
    {
        boutonSuiv = new QPushButton("Suivant");
    }

    if(pre)
    {
        boutonPre = new QPushButton("Précédent");
    }
    else
    {
        boutonPre = new QPushButton("Annuler");
    }
    layoutBout->addWidget(boutonSuiv);
    layoutBout->addWidget(boutonPre);
    boutonSuiv->setEnabled(true);
    saisieTexte=0;
    chTexte=0;
    descTexte=0;
    radTexte=0;
    layout=0;
    elt=0;
    terminer=fin;
    elt=0;
    nbResult=0;
    setWindowModality(Qt::WindowModal);
}
void DIAL_ASSISTANT::setTitle(QString title)
{
    setWindowTitle(title);
}
void DIAL_ASSISTANT::show()
{
    if(layout)
    {}
    else
    {
        layout = new QVBoxLayout;

        if(elt)
        {for(int i=0;i<elt->nb();i++)
        {layout->addWidget(element(i+1));}}

        layout->addLayout(layoutBout);
        if(saisieTexte)
        {
            for(int i=0;i<saisieTexte->nb();i++)
            {
                QObject::connect(saisie(i+1), SIGNAL(textChanged(const QString)), this, SLOT(modif(const QString)));
            }

            QObject::connect(this, SIGNAL(renseignes(bool)), boutonSuiv, SLOT(setEnabled(bool)));
        }
        if(radTexte)
        {
            for(int i=0;i<radTexte->nb();i++)
            {
                QObject::connect(radio(i+1), SIGNAL(clicked(bool)), boutonSuiv, SLOT(setEnabled(bool)));
            }
        }
        QObject::connect(boutonPre, SIGNAL(clicked()), this, SLOT(bPre()));
        QObject::connect(boutonSuiv, SIGNAL(clicked()), this, SLOT(bSuiv()));
    }
    setLayout(layout);

    QDialog::show();
}
void DIAL_ASSISTANT::AdSaisieTexte(QString title, int mod)
{
    if (!saisieTexte)
    {
        saisieTexte = new LIS_QLineEdit(title,mod);
    }
    else
    {
        saisieTexte->AdQLineEdit(title,mod);
    }
     AdQWidget(titleSaisie(saisieTexte->nb()));
    AdQWidget(saisie(saisieTexte->nb()));
    if(boutonSuiv->isEnabled())
    {boutonSuiv->setEnabled(false);}
    nbResult++;
}
void DIAL_ASSISTANT::AdChTexte(QString title,QStringList liste)
{
    if (!chTexte)
    {
        chTexte = new LIS_QComboBox(title,liste);
    }
    else
    {
        chTexte->AdQComboBox(title,liste);
    }
    AdQWidget(titleChoix(saisieTexte->nb()));
    AdQWidget(choix(chTexte->nb()));
    nbResult++;
}
void DIAL_ASSISTANT::AdDescTexte(QString texte)
{
    if (!descTexte)
    {
        descTexte = new LIS_QLabel(texte);
    }
    else
    {
        descTexte->AdQLabel(texte);
    }
    AdQWidget(description(descTexte->nb()));
}
void DIAL_ASSISTANT::AdRadTexte(QString texte)
{
    if (!radTexte)
    {
        radTexte = new LIS_QRadioButton(texte);
        nbResult++;
    }
    else
    {
        radTexte->AdQRadioButton(texte);
    }
    AdQWidget(radio(radTexte->nb()));
    if(boutonSuiv->isEnabled())
    {boutonSuiv->setEnabled(false);}
}
void DIAL_ASSISTANT::AdQWidget(QWidget *b)
{
    if (!elt)
    {
        elt = new LIS_QWidget(b);
    }
    else
    {
        elt->AdQWidget(b);
    }
}
QString DIAL_ASSISTANT::textSaisie(int id)
{
    if(saisie(id))
    {
        return saisie(id)->text();
    }
    else
    {
        return "";
    }
}
QString DIAL_ASSISTANT::textChoix(int id)
{
    if(choix(id))
    {
        return choix(id)->currentText();
    }
    else
    {
        return "";
    }
}
QLabel *DIAL_ASSISTANT::titleSaisie(int id)
{
    if(saisieTexte)
    {
        return saisieTexte->RechTitle(id-1);
    }
    else
    {
        return 0;
    }
}
QLineEdit *DIAL_ASSISTANT::saisie(int id)
{
    if(saisieTexte)
    {
        return saisieTexte->RechLineEdit(id-1);
    }
    else
    {
        return 0;
    }
}
QLabel *DIAL_ASSISTANT::titleChoix(int id)
{
    if(chTexte)
    {
        return chTexte->RechTitle(id-1);
    }
    else
    {
        return 0;
    }
}
QComboBox *DIAL_ASSISTANT::choix(int id)
{
    if(chTexte)
    {
        return chTexte->RechComboBox(id-1);
    }
    else
    {
        return 0;
    }
}
QLabel *DIAL_ASSISTANT::description(int id)
{
    if(descTexte)
    {
        return descTexte->RechQLabel(id-1);
    }
    else
    {
        return 0;
    }
}
QRadioButton *DIAL_ASSISTANT::radio(int id)
{
    if(radTexte)
    {
        return radTexte->RechQRadioButton(id-1);
    }
    else
    {
        return 0;
    }
}
QString DIAL_ASSISTANT::textRadio()
{
    if(radTexte)
    {return radTexte->ct();}
    else
    {return 0;}
}
QWidget *DIAL_ASSISTANT::element(int id)
{
    if(elt)
    {
        return elt->RechQWidget(id-1);
    }
    else
    {
        return 0;
    }
}
QString DIAL_ASSISTANT::resultat(int id)
{
    int k = 0;
    if((saisieTexte) and (id<=k+saisieTexte->nb()))
    {return textSaisie(id);}
    else
    {
        if(saisieTexte)
        {k+=saisieTexte->nb();}
        k++;
        if((chTexte) and (id<=k+chTexte->nb()))
        {
            return textChoix(id-k+1);}
        else
        {
            if(chTexte)
            {k+=chTexte->nb();}
            k++;
            if((radTexte) and (id<=k))
            {return textRadio();}
            else
            {return 0;}
        }
    }
}

void DIAL_ASSISTANT::modif(const QString & t)
{
    bool change = true;
    for(int i=0;(i<saisieTexte->nb() & change) ;i++)
    {
        change =(textSaisie(i+1) != "");
    }
    emit renseignes(change);
}
void DIAL_ASSISTANT::bPre()
{
    emit precedent();
}
void DIAL_ASSISTANT::bSuiv()
{
    emit suivant();
}
DIAL_ASSISTANT::~DIAL_ASSISTANT()
{
   /* delete layout;
    delete layoutBout;
        delete boutonSuiv;
        delete boutonPre;

    delete saisieTexte;
    delete chTexte;
    delete descTexte;
    delete radTexte;

    delete elt;*/
}
