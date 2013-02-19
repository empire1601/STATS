#include "TAP_Donnes.h"
#include "qdebug.h"


TAP_DONNEES::TAP_DONNEES()
{

}

QStringList TAP_DONNEES::Modalites()
{
    return modalites;
}
QStringList TAP_DONNEES::Effectifs()
{
    return effectifs;
}
QStringList TAP_DONNEES::Frequences()
{
    return frequences;
}
QStringList TAP_DONNEES::FrequencesCumulees()
{
    return frequencesCumulees;
}
QStringList TAP_DONNEES::Mode()
{
    QStringList mode;
    int effmax=0;
    int i = 0;
    for(i=0;i<modalites.size();i++)
    {
        if(effmax<effectifs.at(i).toInt())
        {effmax=effectifs.at(i).toInt();}
    }
    for(i=0; i<modalites.size();i++)
    {
        if(effmax==effectifs.at(i).toInt())
        {
            mode+=modalites.at(i);
        }
    }
    return mode;
}

void TAP_DONNEES::Charger(QVar *variable)
{
    QIntList eff;
    modalites.clear();
    if(variable->Ordonnee())
    {
        modalites=variable->Ordre();
        int teff;
        for(int i=0;i<modalites.size();i++)
        {
            teff=0;
            for(int j=0;j<variable->NbVal();j++)
            {
                if(modalites.at(i)==variable->Row(j))
                {
                    teff++;
                }
            }
            eff+=teff;
        }
    }
    else
    {
        for(int i=0;i<variable->NbVal();i++)
        {
            if(variable->isValide(i))
            {
                    if(!modalites.contains(variable->Row(i)))
                    {
                        modalites+=variable->Row(i);
                        eff+=1;
                    }
                    else
                    {
                        int j=0;
                        for(j; j<modalites.size() and modalites.at(j)!=variable->Row(i);j++)
                        {}
                        eff.replace(j, eff.at(j)+1);
                    }
            }
        }
    }
    if(variable->Type()>=TYPES::QUANTITATIF_DISCRET)
    {
        if(modalites.size()>1)
        {Trier(&eff);}
    }
    double fcum=0;
    for(int i=0; i<eff.size();i++)
    {
        effectifs+=QString().number(eff.at(i),'f', 0);
         frequences+=QString().number(double(double(eff.at(i))/double(variable->NbValide())),'f', 3);
         if(variable->Type()>=TYPES::QUALITATIF_ORDINAL)
         {
             fcum+=double(eff.at(i))/double(variable->NbValide());
             frequencesCumulees+=QString().number(fcum, 'f', 3);
         }
     }
}
void TAP_DONNEES::Trier(QIntList *eff, QStringList *ordre)
{
    int i=0;

        if(modalites.size()>1)
        {
            while(i<modalites.size()-1)
            {

                if(QString(modalites.at(i)).toDouble()>QString(modalites.at(i+1)).toDouble())
                {

                    QString t(modalites.at(i));

                    modalites.replace(i, modalites.at(i+1));

                    modalites.replace(i+1, t);

                    int tn(eff->at(i));

                    eff->replace(i, eff->at(i+1));
                    eff->replace(i+1, tn);
                    if(i)
                    {i--;}
                    else
                    {i++;}
                }
                else
                {i++;}

            }
        }
}
void TAP_DONNEES::Supprimer()
{
    modalites.clear();
    effectifs.clear();
    frequences.clear();
    frequencesCumulees.clear();;
}
