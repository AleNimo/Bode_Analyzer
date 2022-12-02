	#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    virtual void write(float* freq,float*mag,float*phase,unsigned int num_points){};
    virtual void Freq_Config(float freq_min, float freq_max, unsigned int points_decade){};

    void bind(Model* m)
    {
        model = m;
    }
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
