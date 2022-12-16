#include "Filter.h"


Filter::Filter(float* freq,float*mag,float* phase,unsigned char total_points)
{
    this->freq = freq;
    this->phase = phase;
    this->mag = mag;
    this->total_points = total_points;



}

Filter::~Filter()
{

}


