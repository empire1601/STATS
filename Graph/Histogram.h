#ifndef HISTOGRAM_H
#define HISTOGRAM_H

/*
#include <stdlib.h>
#include <qpen.h>
#include <qwt_plot_layout.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_histogram.h>
#include <qwt_column_symbol.h>
#include <qwt_series_data.h>
#include "System/QIntList.h"

class Histogram: public QwtPlotHistogram
{
public:
    Histogram( const QString &, const QColor & );

    void setColor( const QColor & );
    void setValues( uint numValues, const double * );
    void setValues(QDoubleList val);
};
*/
#include <qwt.h>
#include <qwt_plot.h>

#include <qwt_plot_curve.h>

class MyPlot : public QwtPlot
{
public:
  MyPlot( QWidget *parent=0, char *name=0 ) : QwtPlot(QwtText(name), parent )
  {
  }
};
class Data : public QwtSeriesData<int>
{
public:
    Data()
    {
    }
};

#endif // HISTOGRAM_H
