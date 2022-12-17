#include "Filter.h"


Filter::Filter(float* freq,float*m,float* p,unsigned int total_points):
    mag(total_points), phase(total_points)
{
//    this->mag.reserve(total_points);
//    this->phase.reserve(total_points);

    for (unsigned int i=0; i<total_points; ++i)
    {
//      this->mag.append(QCPGraphData(freq[i],mag[i]));
//      this->phase.append(QCPGraphData(freq[i],phase[i]));
        mag[i].key = freq[i];
        mag[i].value = m[i];

        phase[i].key = freq[i];
        phase[i].value = p[i];
    }

    this->total_points = total_points;
}

Filter::~Filter()
{

}


