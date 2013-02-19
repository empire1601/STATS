#include "GRAPH.h"

 GRAPH::GRAPH(QDeclarativeItem *parent)
     : QDeclarativeItem(parent)
 {
     // need to disable this flag to draw inside a QDeclarativeItem
     setFlag(QGraphicsItem::ItemHasNoContents, false);
     this->setTitre("Graphique");
 }

 QString GRAPH::Titre() const
 {
     return m_Titre;
 }

 void GRAPH::setTitre(const QString &titre)
 {
     m_Titre = titre;
 }

 QColor GRAPH::color() const
 {
     return m_color;
 }

 void GRAPH::setColor(const QColor &color)
 {
     m_color = color;
 }

 void GRAPH::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
 {
     QPen pen(m_color, 2);
     painter->setPen(pen);
     painter->setRenderHints(QPainter::Antialiasing, true);
     painter->drawPie(boundingRect(), 90 * 16, 290 * 16);
     painter->drawPie(this->boundingRect(),90*16,120*16);
 }

