#ifndef FREQ_CONFIGVIEW_HPP
#define FREQ_CONFIGVIEW_HPP

#include <gui_generated/freq_config_screen/Freq_ConfigViewBase.hpp>
#include <gui/freq_config_screen/Freq_ConfigPresenter.hpp>

class Freq_ConfigView : public Freq_ConfigViewBase
{
public:
    Freq_ConfigView();
    virtual ~Freq_ConfigView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();


    virtual void SliderSet_Freq_Min(int value);
    virtual void SliderSet_Freq_Max(int value);
    virtual void SliderSet_PointsDecade(int value);

    virtual void Enter_Freq();

    float freq_max;
	float freq_min;
	unsigned int points_decade;

protected:
};

#endif // FREQ_CONFIGVIEW_HPP
