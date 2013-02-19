#ifndef GRAPH_TUYAU_H
#define GRAPH_TUYAU_H
#include "GRAPH.h"

class Barre : public QObject
{/*
    Q_OBJECT
    Q_PROPERTY(QString libelle READ libelle WRITE setLibelle)
    Q_PROPERTY(double value READ value WRITE setValue)

    public:*/
    Barre(QString lib, double val, QObject *parent);/*
    QString libelle() const;
    void setLibelle(const QString &libelle);
    double value() const;
    void setValue(const double &value);

    public:
    QString m_libelle;
    double m_value;*/

};


class GRAPH_TUYAU : public GRAPH
{
public:
    GRAPH_TUYAU(QDeclarativeItem *parent, int NbMod=0);
};

#endif // GRAPH_TUYAU_H
