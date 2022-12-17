#ifndef FILTER_H
#define FILTER_H

#include "qcustomplot.h"

#define MAX_POINTS 600

class Filter
{

public:
    Filter(float* freq,float*mag,float* phase,unsigned int total_points);
    ~Filter();

    QVector<QCPGraphData> mag;
    QVector<QCPGraphData> phase; //Agregar retardo de grupo

    unsigned char total_points;

private:

};

#endif // FILTER_H
