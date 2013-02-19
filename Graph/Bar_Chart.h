#ifndef BAR_CHART_H
#define BAR_CHART_H

#include <qwt_plot_renderer.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_multi_barchart.h>
#include <qwt_column_symbol.h>
#include <qwt_plot_layout.h>
#include <qwt_legend.h>
#include <qwt_scale_draw.h>

#include "Resume/Resume.h"

class QwtPlotMultiBarChart;

class BarChart: public QwtPlot
{
    Q_OBJECT

public:
    BarChart(RESUME *,QWidget * = NULL );

public Q_SLOTS:
    void setMode( int);
    void setOrientation( int );
    void exportChart();
    void ch_Var(int);

private:
    void populate();

    QwtPlotMultiBarChart *d_barChartItem;
};

#endif // BAR_CHART_H
