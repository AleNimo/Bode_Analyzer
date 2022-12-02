#ifndef CONFIG_FREQPRESENTER_HPP
#define CONFIG_FREQPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Config_freqView;

class Config_freqPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Config_freqPresenter(Config_freqView& v);

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

    virtual ~Config_freqPresenter() {};

private:
    Config_freqPresenter();

    Config_freqView& view;
};

#endif // CONFIG_FREQPRESENTER_HPP
