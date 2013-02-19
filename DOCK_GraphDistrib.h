#ifndef DOCK_GRAPHDISTRIB_H
#define DOCK_GRAPHDISTRIB_H

#include "Population/POPULATION.h"
#include "Graph/Histogram.h"
#include "Graph/Bar_Chart.h"
#include "Resume/Resume.h"

/*class GRAPH_DISTRIB : public QwtPlot
{
    Q_OBJECT
    public:
        GRAPH_DISTRIB(TAP *mod,QWidget *parent=0);
        void populate();
    private Q_SLOTS:
        void showItem( QwtPlotItem *, bool on );
    private:
        TAP *model;

};*/

class DOCK_GRAPHDISTRIB : public QDockWidget
{
    Q_OBJECT
    public:
        DOCK_GRAPHDISTRIB(RESUME *res, QWidget *parent=0);
    public slots:
        void Ch_Var(QIntList var);
    private:
        BarChart *graph;
        RESUME *resume;
};
#endif // DOCK_GRAPHDISTRIB_H
