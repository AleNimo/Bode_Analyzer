#include "Filter.h"


Filter::Filter(float* freq,float*m, float* mag_uc, float* p, float* phase_uc, unsigned int total_points):
    mag(total_points), mag_sup(total_points), mag_inf(total_points), phase(total_points), phase_sup(total_points), phase_inf(total_points)
{
//    this->mag.reserve(total_points);
//    this->phase.reserve(total_points);

    for (unsigned int i=0; i<total_points; ++i)
    {
//      this->mag.append(QCPGraphData(freq[i],mag[i]));
//      this->phase.append(QCPGraphData(freq[i],phase[i]));
        mag[i].key = freq[i];
        mag[i].value = m[i];

        mag_inf[i].key = freq[i];
        mag_inf[i].value = m[i] - mag_uc[i];

        mag_sup[i].key = freq[i];
        mag_sup[i].value = m[i] + mag_uc[i];

        phase[i].key = freq[i];
        phase[i].value = p[i];

        phase_inf[i].key = freq[i];
        phase_inf[i].value = p[i] - phase_uc[i];

        phase_sup[i].key = freq[i];
        phase_sup[i].value = p[i] + phase_uc[i];
    }

    this->total_points = total_points;
}

Filter::~Filter()
{

}


