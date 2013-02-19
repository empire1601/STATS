#include "DOCK_GraphDistrib.h"

#include "qdebug.h"
/*
GRAPH_DISTRIB::GRAPH_DISTRIB(TAP *mod, QWidget *parent)
{
    qDebug()<<"Création d'un graph";
    this->model=mod;

    setTitle("Distribution de");
    setCanvasBackground( QColor( Qt::white ) );
    plotLayout()->setAlignCanvasToScales( true );

    setAxisTitle( QwtPlot::yLeft, "Frequences" );
    setAxisTitle( QwtPlot::xBottom, "Modalites" );

    QwtLegend *legend = new QwtLegend;
    legend->setItemMode( QwtLegend::CheckableItem );
    insertLegend( legend, QwtPlot::RightLegend );

    connect( this, SIGNAL( legendChecked( QwtPlotItem *, bool ) ),
        SLOT( showItem( QwtPlotItem *, bool ) ) );

    replot(); // creating the legend items

    QwtPlotItemList items = itemList( QwtPlotItem::Rtti_PlotHistogram );
    for ( int i = 0; i < items.size(); i++ )
    {
        if ( i == 0 )
        {
            QwtLegendItem *legendItem =
                qobject_cast<QwtLegendItem *>( legend->find( items[i] ) );
            if ( legendItem )
                legendItem->setChecked( true );

            items[i]->setVisible( true );
        }
        else
            items[i]->setVisible( false );
    }

    setAutoReplot( true );
}
void GRAPH_DISTRIB::populate()
{
    qDebug()<<"MAJ";
    this->setTitle(QwtText("Distribution de "+this->model->Nom()));
    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableX( false );
    grid->enableY( true );
    grid->enableXMin( false );
    grid->enableYMin( false );
    grid->setMajPen( QPen( Qt::black, 0, Qt::DotLine ) );
    grid->attach( this );

    if(model->TypeVar()==TYPES::QUANTITATIF_CONTINU_PURE)
    {
        qDebug()<<"Dans le if";
        QStringList modalites = this->model->Table(0).Modalites();
        QDoubleList modDouble(modalites);
        //const double juneValues[] = { 7, 19, 24, 32, 10, 5, 3 };
        //const double novemberValues[] = { 4, 15, 22, 34, 13, 8, 4 };

        Histogram *histogramJune = new Histogram( this->model->Nom(), Qt::blue );
        histogramJune->setValues(modDouble);
        histogramJune->attach( this );

        /*Histogram *histogramNovember = new Histogram( "Winter", Qt::red );
        histogramNovember->setValues(
            sizeof( novemberValues ) / sizeof( double ), novemberValues );
        histogramNovember->attach( this );
    }
}
void GRAPH_DISTRIB::showItem( QwtPlotItem *item, bool on )
{
    item->setVisible(on);
}

DOCK_GRAPHDISTRIB::DOCK_GRAPHDISTRIB(POPULATION *pop, QWidget *parent) : QDockWidget("Distribution", parent)
{
    qDebug()<<"Création du graphique de distribution";
    model = new TAP(pop);
    graph = new GRAPH_DISTRIB(model,parent);
    setWidget(graph);
    //graph->setModel(model);
    setFixedSize(450,300);
}
void DOCK_GRAPHDISTRIB::Ch_Var(QVar var)
{
    qDebug()<<"Changement de la variable affichée";
    if(var.NbValide())
    {
        model->setVar(var);
        qDebug()<<"Mise   jour des informations";
        graph->populate();
    }
}*/
/*

QwtPlot *w;

w = new QwtPlot(QwtText("Two Graphs"), this);

QwtPlotCurve *curve1 = new QwtPlotCurve("Curve 1");
QwtPlotCurve *curve2 = new QwtPlotCurve("Curve 2");

QPolygonF points;
for(unsigned int i = 0; i < 300; i++)
{
  points << QPointF(i*100, i*200);
}
curve1->setSamples(points);

curve1->attach(w);
w->replot();*/

DOCK_GRAPHDISTRIB::DOCK_GRAPHDISTRIB(RESUME *res, QWidget *parent) : QDockWidget("Distribution",parent)
{
    qDebug()<<"Creation d'un dock de graph";
    resume=res;
    graph=new BarChart(res,this);
}
void DOCK_GRAPHDISTRIB::Ch_Var(QIntList var)
{
    this->resume->tap->Distribution(distribution);

}
