#include "MENU_GRAPH.h"
#include "qdebug.h"


PART_CIRC::PART_CIRC(int i, QRect pos, QColor colFont, double angDeb, double angTaille, QGraphicsScene *s, QString n)
{
    scene=s;
    id=i;
    setBrush(QBrush(colFont));
    setRect(pos);
    setStartAngle((angDeb)*16);
    setSpanAngle(angTaille*16);
    if(n!="")
    {
        nom=n;
        nomGraph = new QGraphicsTextItem(nom,this);
        nomGraph->setPos(0, pos.height()/2);
        nomGraph->setTransformOriginPoint(pos.width()/4,pos.height()/4);
        scene->addItem(this);
        nomGraph->setRotation(360-(int(angDeb+angTaille/2+180)%360));
        nomGraph->setPos(pos.width()/4,pos.height()/4);
    }
}
int PART_CIRC::ID()
{
    return id;
}

DESSIN_MENU::DESSIN_MENU(QActionList *act, QGraphicsScene *scene, QWidget *parent) : QGraphicsView (scene,parent)
{
    //setWindowFlags (Qt::FramelessWindowHint);
    setStyleSheet("background: transparent");
    setFixedSize(200,200);
    select =0;
    nbAction = act->count();
    int deg = (360)/nbAction;
    int col = 220/nbAction;
    part = new PART_CIRC *[nbAction];
    for(int i=0;i<nbAction;i++)
    {
        part[i]=new PART_CIRC(i,QRect(0,0,150,150),QColor(0, col*i+35, col*i+35),i*deg+deg*(nbAction/4),deg,scene,act->operator [](i)->text());
        /*part[i] = new QGraphicsEllipseItem();
        part[i]->setBrush(QBrush(QColor(0,col*i+35,col*i+35)));
        part[i]->setRect(100,100,150,150);
        part[i]->setStartAngle(i*deg+deg*((nbAction)/4));
        part[i]->setSpanAngle(deg);*/
    }

    setMouseTracking(true);
}
void DESSIN_MENU::mouseMoveEvent(QMouseEvent *event)
{
    int i=nbAction-1;
    for(i;i>=0;i--)
    {
        if(part[i]->isUnderMouse())
        {break;}
    }
    qDebug()<<i+1;
}

MENU_GRAPH::MENU_GRAPH(QActionList *act, QPoint pos, QWidget *parent) : QDialog(parent,Qt::Popup)
{
    QPoint posC(pos.x()-32,pos.y()+5);
    move(posC);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags( Qt::FramelessWindowHint|Qt::WindowSystemMenuHint|Qt::WindowStaysOnTopHint ) ;
    QHBoxLayout *layout = new QHBoxLayout;
    scene = new QGraphicsScene;
    graph = new DESSIN_MENU(act,scene);
    layout->addWidget(graph);
    QRegion reg(0,0,300,300);
    setMask(reg - QRegion(95,80,30,30,QRegion::Ellipse ));
    setLayout(layout);
}
