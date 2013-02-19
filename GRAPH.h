#ifndef GRAPH_H
#define GRAPH_H

#include <QtGui>
#include "System/Maths.h"
#include <QDeclarativeItem>
#include <qdeclarative.h>
#include <QDeclarativeView>
 #include "piechart.h"
#include <QColor>

class GRAPH : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QString Titre READ Titre WRITE setTitre)
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    GRAPH(QDeclarativeItem *parent = 0);

    QString Titre() const;
    void setTitre(const QString &titre);

    QColor color() const;
    void setColor(const QColor &color);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    QString m_Titre;
    QColor m_color;
};

#endif // GRAPH_H
