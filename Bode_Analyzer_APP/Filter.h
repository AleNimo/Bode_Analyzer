#ifndef FILTER_H
#define FILTER_H

#include "qcustomplot.h"

#define MAX_POINTS 600

class Filter
{

public:
    Filter(float* freq,float*mag,float* mag_uc,float* phase,float* phase_uc, unsigned int total_points);
    ~Filter();

    QVector<QCPGraphData> mag;

    QVector<QCPGraphData> mag_sup;
    QVector<QCPGraphData> mag_inf;

    QVector<QCPGraphData> phase;
    QVector<QCPGraphData> phase_sup;
    QVector<QCPGraphData> phase_inf;

    unsigned char total_points;

private:

};

#endif // FILTER_H
