#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}
void Screen1Presenter::write(float* freq,float*mag,float*phase,unsigned int num_points)
{
	view.DataDisplay(freq,mag,phase,num_points);
}
