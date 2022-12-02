#ifndef FREQ_CONFIGPRESENTER_HPP
#define FREQ_CONFIGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Freq_ConfigView;

class Freq_ConfigPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Freq_ConfigPresenter(Freq_ConfigView& v);

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

    virtual ~Freq_ConfigPresenter() {};

    virtual void Freq_Config_Presenter(float freq_min, float freq_max, unsigned int points_decade);

private:
    Freq_ConfigPresenter();

    Freq_ConfigView& view;
};

#endif // FREQ_CONFIGPRESENTER_HPP
