#include "Histogram.h"
/*
Histogram::Histogram( const QString &title, const QColor &symbolColor ):
    QwtPlotHistogram( title )
{
    setStyle( QwtPlotHistogram::Columns );

    setColor( symbolColor );
}

void Histogram::setColor( const QColor &symbolColor )
{
    QColor color = symbolColor;
    color.setAlpha( 180 );

    setPen( QPen( Qt::black ) );
    setBrush( QBrush( color ) );

    QwtColumnSymbol *symbol = new QwtColumnSymbol( QwtColumnSymbol::Box );
    symbol->setFrameStyle( QwtColumnSymbol::Raised );
    symbol->setLineWidth( 2 );
    symbol->setPalette( QPalette( color ) );
    setSymbol( symbol );
}

void Histogram::setValues( uint numValues, const double *values )
{
    QVector<QwtIntervalSample> samples( numValues );
    for ( uint i = 0; i < numValues; i++ )
    {
        QwtInterval interval( double( i ), i + 1.0 );
        interval.setBorderFlags( QwtInterval::ExcludeMaximum );

        samples[i] = QwtIntervalSample( values[i], interval );
    }

    setData( new QwtIntervalSeriesData( samples ) );
}
//->Fct perso
void Histogram::setValues(QDoubleList val)
{
    QVector<QwtIntervalSample> samples( val.size() );
    for ( uint i = 0; i < val.size(); i++ )
    {
        QwtInterval interval( double( i ), i + 1.0 );
        interval.setBorderFlags( QwtInterval::ExcludeMaximum );

        samples[i] = QwtIntervalSample( val[i], interval );
    }

    setData( new QwtIntervalSeriesData( samples ) );
}*/
