#ifndef GRAFICOPRESENTER_HPP
#define GRAFICOPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class GraficoView;

class GraficoPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    GraficoPresenter(GraficoView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~GraficoPresenter() {};

    virtual void write(float* freq,float*mag,float*phase,unsigned int num_points);
    virtual void Freq_Config_Presenter(float freq_min, float freq_max, unsigned int points_decade);


private:
    GraficoPresenter();

    GraficoView& view;
};

#endif // GRAFICOPRESENTER_HPP
