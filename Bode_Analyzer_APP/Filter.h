#ifndef FILTER_H
#define FILTER_H




class Filter
{

public:
    Filter(float* freq,float*mag,float* phase,unsigned char total_points);
    ~Filter();


private:

    float* freq;
    float* mag;
    float* phase;
    float* group_delay;
    unsigned char total_points;


};

#endif // FILTER_H
