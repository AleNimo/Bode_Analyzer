#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    void Freq_Config(float freq_min, float freq_max, unsigned int points_decade);

protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
