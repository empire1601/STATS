#ifndef MENU_GRAPH_H
#define MENU_GRAPH_H

#include <QtGui>
#include "System/Maths.h"
#include "QActionList.h"

class PART_CIRC : public QGraphicsEllipseItem
{
    public:
        PART_CIRC(int i, QRect pos, QColor colFont, double angDeb, double angTaille, QGraphicsScene *s, QString n="");
        void setCouleur(int r, int g , int b);
        void setCouleur(QColor c);
        int ID();
    private:
        QString nom;
        QGraphicsTextItem* nomGraph;
        QGraphicsScene *scene;
        int id;

};

class DESSIN_MENU : public QGraphicsView
{
    public :
            DESSIN_MENU(QActionList *act, QGraphicsScene *scene, QWidget *parent=0);
    private:
        QGraphicsItemGroup *groupe;
        void mouseMoveEvent(QMouseEvent *event);

        int select;
        int nbAction;
        PART_CIRC **part;

};
class MENU_GRAPH : public QDialog
{
    public:
        MENU_GRAPH(QActionList *act, QPoint pos, QWidget *parent=0);

    private:
        QGraphicsScene *scene;
        DESSIN_MENU *graph;
};

#endif // MENU_GRAPH_H
