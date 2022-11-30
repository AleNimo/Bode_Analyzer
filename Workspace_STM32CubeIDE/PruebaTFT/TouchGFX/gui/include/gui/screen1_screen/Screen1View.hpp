#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#define MAG 1
#define PHASE 0
class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void DataDisplay(float* freq,float*mag,float*phase,unsigned int num_points);

    virtual void Toggle_Mag_Phase();
protected:
};

#endif // SCREEN1VIEW_HPP
