#ifndef GRAFICOVIEW_HPP
#define GRAFICOVIEW_HPP

#include <gui_generated/grafico_screen/GraficoViewBase.hpp>
#include <gui/grafico_screen/GraficoPresenter.hpp>

#define MAG		0
#define PHASE	1

class GraficoView : public GraficoViewBase
{
public:
    GraficoView();
    virtual ~GraficoView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void Enter_Freq();

    virtual void DataDisplay(float* freq,float*mag,float*phase,unsigned int num_points);

    virtual void Toggle_Mag_Phase();
private:
    float range_min;
    float range_max;

protected:

};

#endif // GRAFICOVIEW_HPP
